#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include </usr/include/opencv4/opencv2/opencv.hpp>
#include </usr/include/opencv4/opencv2/highgui/highgui_c.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <tesseract/capi.h>
#include <leptonica/allheaders.h>

#define trigger 4
#define sensorA 5
#define sensorB 6
#define controle 1


int foto();
void configuraPinos();
int telegramBot();
float distancia(int ECHO);
void acionaPortao();
void enviaNotificacao();
bool reconheceVeiculo();
int tesseract();


char placaNotificada[8]; 
int main(void){

	configuraPinos();
	acionaPortao();	
	int estadoAtual = 0;
	int proximoEstado = 0;
	float ultrassom1, ultrassom2;
	bool liberar = false;	
		//int pid = fork();
		
		//if(pid == 0){
			//Bot Telegram 
			//system("./echobot");
			//while(1);
		//}else{
			while(1){
				//Reconhecimento de veículo
								
				ultrassom1 = distancia(sensorA);
				ultrassom2 = distancia(sensorB);
				printf("Estado Atual: %d ", estadoAtual);
				printf("Ultrassom 1 = %.2f, Ultrassom 2 = %.2f\n", ultrassom1, ultrassom2);
				delay(1000);

				switch(estadoAtual){
					case 0:
						if(ultrassom1 < 10 && ultrassom2 > 10){
							proximoEstado = 1;
						}else{
							proximoEstado = 0;
						}
						break;
						
					case 1:
						if(ultrassom1 < 10 && ultrassom2 < 10){
							proximoEstado = 2;
						}else if(ultrassom1 < 10){
							proximoEstado = 1;
						}else{
							proximoEstado = 0;
						}
						break;
						
					case 2:
						
						if(foto() < 0){
							printf("Falha na captura da imagem");
						}else{
						
							if(reconheceVeiculo()){
								acionaPortao();
								enviaNotificacao();
								
							}else{
								printf("Placa não reconhecida\n");
							}
						
						}
						if(ultrassom1 < 10 && ultrassom2 < 10){
							proximoEstado = 0;
						}
						break;
					default:
						break;
				}
				
				estadoAtual = proximoEstado;
								
			}
		//}
			return 0;
}

void configuraPinos(){

	wiringPiSetup();
	pinMode(controle, OUTPUT);
	pinMode(trigger, OUTPUT);
	pinMode(sensorA, INPUT);
	pinMode(sensorB, INPUT);

	digitalWrite(controle, LOW);
	digitalWrite(trigger, LOW);
	printf("\n\nPinos configurados\n\n");
}

int foto(){
	cv::VideoCapture cap(0); // Abre a webcam (0 representa a câmera padrão)
	
	if (!cap.isOpened()) {
	std::cerr << "Erro ao abrir a webcam." << std::endl;
	return -1;
	}

	cap.set(cv::CAP_PROP_AUTOFOCUS, 1);
	cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 1);
	
	cv::Mat frame;
	sleep(2);
	cap >> frame; // Captura um quadro da webcam

	if (frame.empty()) {
	std::cerr << "Quadro vazio." << std::endl;
	return -1;
	}
	
	cv::imwrite("foto_webcam.jpg", frame); // Salva a imagem como "foto_webcam.jpg"
	
	cap.release(); // Libera a webcam

	//std::cout << "Foto tirada com sucesso!" << std::endl;

	return 0;
}

float distancia(int ECHO) {
    digitalWrite(trigger, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigger, LOW);
    while (digitalRead(ECHO) == LOW);

    long startTime = micros();
    while (digitalRead(ECHO) == HIGH);
    long travelTime = micros() - startTime;

    // Distância em centímetros
    float distance = travelTime / 58.0;

    return distance;
}

bool reconheceVeiculo(){

	bool liberar = false;

	system("./call_yolo.out foto.jpg | tr -cd '[:alpha:]' > yoloResultado");
	
	FILE *yolo = fopen("yoloResultado", "r");
	char palavra[10];
	bool carroEncontrado;
	
	while(fscanf(yolo, "%s", palavra) != EOF){
		if(strcmp(palavra, "car") == 0){
			carroEncontrado = true;
		}
	}	
	fclose(yolo);
	
	if(carroEncontrado){
		printf("Achei um carro!\n");
		
		if(tesseract() == 0){
			
			FILE *placas = fopen("placas.lp", "r");
			
			if(placas == 0){
				printf("Erro ao abrir arquivo de placas!\n");
				liberar = false;
			}else{
				FILE *tesseract = fopen("tessResultado", "r");
				
				if(tesseract == 0){
					printf("Erro ao abrir leitura do Tesseract\n");
					liberar = false;
				}else{
					char placaLida[8];
					int tamanhoArquivo = 500; //system("du -b tessResultado | grep -Eo '[0-9]{1,4}'")+1;
					char linha[500];
					while(fscanf(placas, "%s", placaLida)!=EOF){
						fread(&linha, sizeof(char), tamanhoArquivo, tesseract);

						if(strstr(linha, placaLida) != NULL){
							strcpy(placaNotificada, placaLida);
							printf("%s\n", placaLida);
							fclose(placas);
							fclose(tesseract);
							liberar = true;
						}
					}
				}
			}
			
		}else{
		
			printf("Erro ao ler caracteres\n\n");
			liberar = false;
		}	
	}else{
		liberar = false;
	}
	return liberar;
}

int tesseract(){

	const char *path = "foto.jpg"; // Altere o caminho para sua imagem
	PIX *image = pixRead(path);
	if (image == NULL) {
		fprintf(stderr, "Erro ao carregar a imagem!\n");
		return 1;
	}

	TessBaseAPI *api = TessBaseAPICreate();
		if (TessBaseAPIInit3(api, NULL, "eng")) { // Escolha o idioma correto para o reconhecimento
		fprintf(stderr, "Erro ao iniciar o Tesseract!\n");
		return 2;
	}

	TessBaseAPISetVariable(api, "tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	TessBaseAPISetImage2(api, image);
	TessBaseAPIRecognize(api, NULL);

	char *text = TessBaseAPIGetUTF8Text(api);
	
	FILE *saida = fopen("tessResultado", "w");
	
	if(saida == 0){
		printf("Erro ao abrir arquivo de resultado.\n");
	}else{
		int i = 0;
		while(text[i] != '\0'){
			fputc(toupper(text[i]), saida);
			i++;
		}
		//fprintf(saida, "%s", text);
		fclose(saida);
	}

	TessDeleteText(text);
	TessBaseAPIEnd(api);
	pixDestroy(&image);

	return 0;
}

void acionaPortao(){
	digitalWrite(controle, HIGH);
	printf("Acionado\n");
	delay(1000);
	digitalWrite(controle, LOW);
	printf("Não acionado\n");
}

void enviaNotificacao(){

	FILE *notificados = fopen("notificados.nf", "r");
	char id[11];
	while(fscanf(notificados, "%s", id) != EOF){
		char comando[200];	
		snprintf(comando, sizeof(comando), "curl -s -X POST https://api.telegram.org/bot6531776112:AAFcAkoG_kiLs6M2mfwp-FGTGti6rMG5S50/sendMessage -d chat_id=%s -d text=\"O veículo de placa %s acessou o condomínio\"", id, placaNotificada);
		system(comando);	
	
	}
	

}

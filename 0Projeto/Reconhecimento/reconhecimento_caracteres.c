#include <stdio.h>
#include <stdlib.h>
#include <tesseract/capi.h>
#include <leptonica/allheaders.h>

int main() {
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
	
	FILE *saida = fopen("resultado_tesseract.txt", "w");
	
	if(saida == 0){
		printf("Erro ao abrir arquivo de resultado.\n");
	}else{
	
		fprintf(saida, "%s", text);
		printf("%s", text);
	}

	TessDeleteText(text);
	TessBaseAPIEnd(api);
	pixDestroy(&image);

	return 0;
}
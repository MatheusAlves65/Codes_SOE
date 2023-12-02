#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <telebot.h>

#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))



void removerLinhaArquivo(char *nomeArquivo, const char *linhaParaRemover, int tamanhoLinha) {
    // Abre o arquivo original para leitura
    FILE *fpOriginal = fopen(nomeArquivo, "r");
    if (fpOriginal == NULL) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return;
    }
	//printf("%s %s\n", nomeArquivo, linhaParaRemover);
    // Abre um arquivo temporário para escrita
    FILE *fpTemp = fopen("temporario.tmp", "w");
    if (fpTemp == NULL) {
        printf("Erro ao criar arquivo temporário\n");
        fclose(fpOriginal);
        return;
    }
    

    char linha[tamanhoLinha];  // Ajuste o tamanho conforme necessário
	
    // Lê cada linha do arquivo original
    while (fgets(linha, sizeof(linha), fpOriginal) != NULL) {
        // Verifica se a linha é a que queremos remover
        printf("%s\n",linha);
        if (strcmp(linha, linhaParaRemover) != 0) {
            // Se não for, escreve no arquivo temporário
            fprintf(fpTemp, "%s", linha);
        }
    }

    // Fecha os arquivos
    fclose(fpOriginal);
    fclose(fpTemp);

    // Remove o arquivo original
    remove(nomeArquivo);

    // Renomeia o arquivo temporário para o nome original
    rename("temporario.tmp", nomeArquivo);
}


 void adicionarinfo(char *nomeArquivo,  char *linhaParaAdicionar) {
 
		        FILE *fpOriginal = fopen(nomeArquivo, "a");
    			if (fpOriginal == NULL) {
        		printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        		return;
    						}		        
		         if((fwrite(linhaParaAdicionar, 1, strlen(linhaParaAdicionar), fpOriginal) < strlen(linhaParaAdicionar))){
		            printf("Erro ao adicionar info");
		        }
		        fwrite("\n", 1, strlen("\n"), fpOriginal);
		        fclose(fpOriginal);
		        
 
 
 }




int main(int argc, char *argv[])
{
	int funcao = 0;
	printf("Iniciando BOT\n");

	FILE *fp = fopen(".token", "r");
	if (fp == NULL)
	{
	printf("Falha ao abrir arquivo .token\n");
	return -1;
	}

	char token[1024];
	if (fscanf(fp, "%s", token) == 0)
	{
	printf("Falha na leitura de .token\n");
	fclose(fp);
	return -1;
	}
	//printf("Token: %s\n", token);
	fclose(fp);

	telebot_handler_t handle;
	if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
	{
	printf("Falha ao Iniciar o BOT\n");
	return -1;
	}

	telebot_user_t me;
	if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
	{
	printf("Falha ao obter informação\n");
	telebot_destroy(handle);
	return -1;
	}

	printf("ID: %d\n", me.id);
	printf("Nome: %s\n", me.first_name);
	printf("Nome de usuário: %s\n", me.username);

	telebot_put_me(&me);

	int index, count, offset = -1;
	telebot_error_e ret;
	telebot_message_t message;
	telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};

	while (1)
	{
	telebot_update_t *updates;
	ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates, &count);
	if (ret != TELEBOT_ERROR_NONE)
	    continue;
	//printf("Number of updates: %d\n", count);
	for (index = 0; index < count; index++)
	{
	    message = updates[index].message;
	    if (message.text)
	    {
		printf("%s: %s \n", message.from->first_name, message.text);
		char str[4096];
		
		switch(funcao){
		
		case 1:
		    	//Inclusão de nova placa
			if(strlen(message.text) == 7){
		        
		        char placa[8];
		        strcpy(placa, message.text);
		        
		        //Converte para letras maiúsculas
		        for(int i = 0; i < 7; i++){
		            if(placa[i] >= 97 && placa[i] <= 122){
		                placa[i] = placa[i] - 32;
		            }
		        }

		        adicionarinfo("placas.lp", placa);
		        snprintf(str, SIZE_OF_ARRAY(str), "Placa %s adicionada", placa);
		        funcao = 0;
				}else{
					snprintf(str, SIZE_OF_ARRAY(str), "Erro! Insira os 7 dígitos da placa, apenas letras e números");
				}
		    	break;
		case 2: 
			sleep(1);
			char placa[8];
			snprintf(placa, SIZE_OF_ARRAY(placa), "%s\n", message.text);
			
			//Converte todas as letras para maiúsculo
			for(int i = 0; i < 7; i++){
		            if(placa[i] >= 97 && placa[i] <= 122){
		                placa[i] = placa[i] - 32;
		            }
		        }            		
			removerLinhaArquivo("placas.lp", placa, 8);
			snprintf(str, SIZE_OF_ARRAY(str), "Placa %s removida com sucesso", placa);
			break;
		case 3: 
            	    sleep(1);
		    if(strstr(message.text, "/Sim")){
		        char usuario[11];
		        sprintf(usuario, "%lld\n", message.chat->id);		        
		         adicionarinfo("notificados.nf", usuario);	        
		        snprintf(str, SIZE_OF_ARRAY(str), "Usuário %s adicionado aos notificados", message.chat->username);
		        
		    }else if(strstr(message.text, "/Nao")){
		    	char usuario[11];
		        sprintf(usuario, "%lld\n", message.chat->id);
		    	removerLinhaArquivo("notificados.nf", usuario, 12);
			snprintf(str, SIZE_OF_ARRAY(str), "Usuario %s removido da lista de notificados",message.chat->username); 
				 funcao = 0;		
			}
		    
		    else{
		    	snprintf(str, SIZE_OF_ARRAY(str), "Deseja receber notificações? \n /Sim \n /Não");
		    }
		    break;		
		default:
			if (strstr(message.text, "/Adicionar")){
				snprintf(str, SIZE_OF_ARRAY(str), "Digite a placa sem traços");
				funcao = 1;
			}else if(strstr(message.text, "/Remover")){
		        snprintf(str, SIZE_OF_ARRAY(str), "Digite a placa sem traços");
                		funcao = 2;
            		}else if(strstr(message.text, "/Notificacao")){
		        	snprintf(str, SIZE_OF_ARRAY(str), "Deseja receber notificações? \n /Sim \n /Nao");
		        	funcao = 3;
		    	}else{
		        	snprintf(str, SIZE_OF_ARRAY(str), "COMANDOS: \n /Adicionar\n /Remover \n /Notificacao \n");
		    	}
			}
		
		ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, updates[index].message.message_id, "");

		if (ret != TELEBOT_ERROR_NONE){
			printf("Falha ao enviar mensagem: %d \n", ret);
		}
	    }
	    offset = updates[index].update_id + 1;
	}
	telebot_put_updates(updates, count);

	sleep(1);
	}

	telebot_destroy(handle);

	return 0;
}


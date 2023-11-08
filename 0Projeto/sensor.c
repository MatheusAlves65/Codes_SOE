#include<wiringPi.h>
#include<stdlib.h>
#include<stdio.h>


#define sensorPin 5
int main(void){
	
	wiringPiSetup();
	pinMode(sensorPin,INPUT);
	
	while(1){
		
		if(digitalRead(sensorPin)){
			fputs("Ativo\n", stderr);
		}else{
			fputs("Inativo\n", stderr);
			}
		delay(250);
	}
}

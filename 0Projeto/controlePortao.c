#include<wiringPi.h>
#include<stdlib.h>
#include<stdio.h>


#define controlePin 6
int main(void){
	
	wiringPiSetup();
	pinMode(controlePin,OUTPUT);
	
	digitalWrite(controlePin, HIGH);
	sleep(1);
	digitalWrite(controlePin, LOW);
	}

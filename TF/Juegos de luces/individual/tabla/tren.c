#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "kbhit.h"
#include <pcf8591.h>

#define Adress 0x48
#define BASE 64
#define A0 BASE+0	//dirección potenciometro ADC

#define N 8		// numero de gpio a usar
#define v 10	 	// tiempo base en mseg

void dec_bin(int dec, int *bin);

int main (){
	
	if(wiringPiSetup() == -1)	exit(1);
	pcf8591Setup(BASE,Adress);
	
	int i,j,flag=0;
	int const gpio[N]= {25,29,28,27,26,6,5,4};	//lista de GPIO disponibles en la placa(se trunca con N)
	int valor_gpio[N]={0};
	int tabla[10]={1,3,7,14,28,56,112,224,193,131};
				
	nonblock(NB_ENABLE);
	
	for(i=0; i<N; i++){
		pinMode(gpio[i],OUTPUT);
		digitalWrite(gpio[i],0);
	}
		
	while( !kbhit() ){
		for(i=flag; i<10; i++){
			dec_bin(tabla[i], valor_gpio);
			for (j=0; j<N; j++) digitalWrite( gpio[j], valor_gpio[j]);
			delay(v*(0.5*analogRead(A0)+1));		//variación de velocidad en función del pot del ADC
			if(tabla[i]==131)	flag=2;	//una vez recorrida tabla por primera vez evita la "entrada" del tren
		}
	};
	
	for(i=0; i<N; i++)	digitalWrite(gpio[i],0);
	
	return 0;
}

void dec_bin(int dec, int *bin ){

	int i;

	for (i=0; i<N; i++){
		if(dec!=0)	*(bin+7-i) = dec%2;
		else	*(bin+7-i) =0;	//rellena con ceros
		dec/=2;
	}
	
}	

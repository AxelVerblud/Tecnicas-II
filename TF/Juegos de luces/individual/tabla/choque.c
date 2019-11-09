#include <stdio.h>
#include <wiringPi.h>
#include "kbhit.h"

#define N 8		// numero de gpio a usar
#define v 0.1*1000 	// retardo en seg*cte usleep

void dec_bin(int dec, int *bin);

int main (){
	
	wiringPiSetup();
	
	int i,j;
	int const gpio[N]= {25,29,28,27,26,6,5,4};	//lista de GPIO disponibles en la placa(se trunca con N)
	int valor_gpio[N]={0};
	int tabla[7]={129,66,36,24,36,66,129};
				
	nonblock(NB_ENABLE);
	
	for(i=0; i<N; i++){
		pinMode(gpio[i],OUTPUT);
		digitalWrite(gpio[i],0);
	}
		
	while( !kbhit() ){
		for(i=0; i<7; i++){
			dec_bin(tabla[i], valor_gpio);
			for (j=0; j<N; j++) digitalWrite( gpio[j], valor_gpio[j]);
			delay(v);			
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

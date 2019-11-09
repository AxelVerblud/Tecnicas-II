#include <stdio.h>
#include <wiringPi.h>
#include "kbhit.h"

#define N 8		// numero de gpio a usar
#define v 0.4*1000 	// retardo en seg*cte usleep

void dec_bin(int dec, int *bin);

int main (){
	
	wiringPiSetup();
	
	int i,j;
	int const gpio[N]= {25,29,28,27,26,6,5,4};	//lista de GPIO disponibles en la placa(se trunca con N)
	int valor_gpio[N]={0};
	int tabla[]={1,2,4,8,16,17,18,36,40,80,96,128,0};
				
	nonblock(NB_ENABLE);
	
	for(i=0; i<N; i++){
		pinMode(gpio[i],OUTPUT);
		digitalWrite(gpio[i],0);
	}
		
	while( !kbhit() ){
		for(i=0; i<14; i++){
			dec_bin(tabla[i], valor_gpio);
			for (j=0; j<N; j++) digitalWrite( gpio[j], valor_gpio[j]);
			if(tabla[i]<=4)	delay(v);
			else	delay(v/2);
		}
		
	};
	
	for(i=0; i<N; i++)	digitalWrite(gpio[i],0);
	
	return 0;
}

void dec_bin(int dec, int *bin ){

	int i;

	if(!dec){
		for (i=0; i<8;i++)	*(bin+i)=0;
		return;
	}

	for (i=0; dec!=0; i++){
		*(bin+7-i) = dec%2;
		dec/=2;
	}
	
}	

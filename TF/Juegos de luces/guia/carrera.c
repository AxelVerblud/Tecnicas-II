#include <stdio.h>
#include "easypio.h"
#include "kbhit.h"

#define N 8		// numero de gpio a usar
#define v 0.4*1000000 	// retardo en seg*cte usleep

void dec_bin(int dec, int *bin);
void set(int const*gpio, int *valor);

int main (){
	
	pioInit();
	
	int i;
	int const gpio[N]={26,21,20,16,12,25,24,23};
	int valor_gpio[N]={0};
	int tabla[]={1,2,4,8,16,17,18,36,40,80,96,128,0};
				
	nonblock(NB_ENABLE);
	
	for(i=0; i<N; i++)	pinMode(gpio[i],OUTPUT);
		
	while( !kbhit() ){
		for(i=0; i<14; i++){
			dec_bin(tabla[i], valor_gpio);
			set( gpio, valor_gpio);
			if(tabla[i]<=4)	usleep(v);
			else	usleep(v/2);
		}
		
	};
	
	for(i=0; i<N; i++)	digitalWrite(gpio[i],0);
	
	return 0;
}

void dec_bin(int dec, int *bin ){

	int i;

	if(!dec){
		*bin=0;
		//usleep(v/2);
		return;
	}

	for (i=0; dec!=0; i++){
		*(bin+7-i) = dec%2;
		dec/=2;
	}
	
}
		 
void set(int const *gpio, int *valor){
	int i;
	for (i=0; i<N; i++) digitalWrite( *(gpio+i), *(valor+i));
}
	

#include <wiringPi.h>
#include <stdio.h>
#include "kbhit.h"

#define N 8		//Numero de GPIO a emplear
#define t_base	250	//mseg


int main(){
	int i,j,k=0;
	int const gpio[N]= {25,29,28,27,26,6,5,4};	//lista de GPIO disponibles en la placa(se trunca con N)

	wiringPiSetup();				//inicialización wiringpi

	for (i=0; i<N; i++){
		pinMode(gpio[i], OUTPUT);		//declaración de salidas
		digitalWrite(gpio[i],0);		///blanking
	}

	nonblock(NB_ENABLE);

	digitalWrite(gpio[0], 1);
	delay (t_base);
	digitalWrite(gpio[1],1);


	while( !kbhit() ){
		
		for(j=2;j<8;j++){
			if(k!=3)	delay(t_base); 
			for(k=j; k>(j-3); k--)	digitalWrite(gpio[k], 1);
			k=0;
			if((j-3)>=0)	digitalWrite(gpio[j-3],0);	
		}

		for(j=4;j>=0;j--){
			delay(t_base);		//variación de velocidad				
			for(k=j; k<(j+3)&& k<7; k++)	digitalWrite(gpio[j], 1);
			if((j+3)<8)	digitalWrite(gpio[j+3],0);	
		}		
	}

	for(i=0; i<N;i++)	digitalWrite(gpio[i],0);
	return 0;
}

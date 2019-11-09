#include <wiringPi.h>
#include <stdio.h>
#include "kbhit.h"

#define N 8		//Numero de GPIO a emplear
#define t_base	3000	//mseg
#define pasos 	1000	//variaciones de velocidad. decrementos del 100%

void desagotar(int const *gpio);

int main(){
	int i,j;
	int const gpio[N]= {25,29,28,27,26,6,5,4};	//lista de GPIO disponibles en la placa(se trunca con N)

	wiringPiSetup();				//inicialización wiringpi

	for (i=0; i<N; i++){
		pinMode(gpio[i], OUTPUT);		//declaración de salidas
		digitalWrite(gpio[i],0);		///blanking
	}

	nonblock(NB_ENABLE);

	while( !kbhit() ){
		for(i=0; i<pasos; i++){
			for(j=0;j<8;j++)	digitalWrite(gpio[j], !digitalRead(gpio[j]));
			delay(t_base/(i+1));		//variación de velocidad
		}
		desagotar(gpio);
	}

	for(i=0; i<N;i++)	digitalWrite(gpio[i],0);
	return 0;
}

void desagotar(int const *gpio){
	nonblock(NB_ENABLE);

	while( !kbhit() ){	
		if(!digitalRead( *(gpio)))	// si los leds estan apagados los enciende
			for(int j=0; j<N; j++)	digitalWrite( *(gpio+j), 1 );
		for(int i=0;i<N;i++){
			digitalWrite( *(gpio+i), 0);
			delay(t_base/(10*(i+1)));
		}
		return;
	}
}

#include <stdio.h>
#include <wiringPi.h>
#include "kbhit.h"

#define N 8

int main (){
	
	wiringPiSetup();
     
    	int i;
	int gpio[N]= {25,29,28,27,26,6,5,4};	//lista de GPIO disponibles en la placa(se trunca con N)
	
    nonblock(NB_ENABLE);
     
    for(i=0; i<N; i++)
    {   pinMode(gpio[i],1);
        digitalWrite(gpio[i],0);
    }
         
    while( !kbhit() ){
        for(i=0; i<N; i++){
            digitalWrite(gpio[i], 1);
            if(i>0)
                digitalWrite(gpio[i-1],0);
            usleep(200000);
        }
         
        for(i=N-2; i>=0; i--){   
            digitalWrite(gpio[i+1],0);
            if(i!=0){
                digitalWrite(gpio[i],1);
                usleep(200000);
            }
        }
    }; //cierre del while
     
    for(i=0; i<N; i++)	digitalWrite(gpio[i],0);
    return 0;
}
	

#include <stdio.h>
#include "easypio.h"
#include "kbhit.h"

#define N 8

int main (){
	
	pioInit();
     
    int i;
    int gpio[8]={26,21,20,16,12,25,24,23};
     
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
     
   clear(gpio, sizeof(gpio));
 
    return 0;
}
	

#include "dhtHeaderFile.h"

void DHT11Start(){
    a3DataMode = 0;
    a3DataOut = 0;
    __delay_ms(18);
    a3DataOut = 1;
    __delay_us(40);
    a3DataMode = 1;
}

short DHT11CheckResponse(){
    short status = 0;
    if(a3DataIn == 0){
        __delay_us(80);
        if(a3DataIn == 1){
            __delay_us(80);
            status = 1;
        }
    }
    return status;
}

char DHT11ReadData(){
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(a3DataIn & 1));      /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(a3DataIn & 1)             /* check whether data is 1 or 0 */    
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(a3DataIn & 1);
    }
  return data;
}
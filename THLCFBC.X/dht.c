/*
 * File:   dht.c
 * Author: juan0
 *
 * Created on 23 de febrero de 2022, 11:54 PM
 */

#include "DHTHeaderFile.h"
#include <xc.h>
#define _XTAL_FREQ 8000000

void DHT11Start()
{
    dataMode = 0;
    dataOut = 0;
    __delay_ms(18);
    dataOut = 1;
    __delay_us(40);
    dataMode = 1;
}

short DHT11CheckResponse()
{
    short status = 0;
    if(dataIn == 0){
        __delay_us(80);
        if(dataIn == 1){
            __delay_us(80);
            status = 1;
        }
    }
    return status;
}

char DHT11ReadData()
{
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(dataIn & 1));      /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(dataIn & 1)             /* check whether data is 1 or 0 */    
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(dataIn & 1);
    }
  return data;
}
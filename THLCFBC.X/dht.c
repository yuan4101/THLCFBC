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
    if(dataIn == 0)
    {
        __delay_us(80);
        if(dataIn == 1)
        {
            __delay_us(80);
            status = 1;
        } 
    }
    return status;
}

/*
void DHT11_Start()
{    
    Data_Dir = 0;       // set as output port
    Data_Out = 0;       // send low pulse of min. 18 ms width
    __delay_ms(18);
    Data_Out = 1;       // pull data bus high
    __delay_us(40);
    Data_Dir = 1;       // set as input port   
}

void DHT11_CheckResponse()
{
    while(Data_In & 1);     // wait till bus is High    
    while(!(Data_In & 1));  // wait till bus is Low
    while(Data_In & 1);     // wait till bus is High
}

char DHT11_ReadData()
{
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(Data_In & 1));      // wait till 0 pulse, this is start of data pulse
        __delay_us(30);         
        if(Data_In & 1)             // check whether data is 1 or 0   
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(Data_In & 1);
    }
  return data;
}
*/
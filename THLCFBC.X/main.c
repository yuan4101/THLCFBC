/*
 * File:   main.c
 * Author: juan0
 *
 * Created on 23 de febrero de 2022, 11:22 PM
 */

#include "configPICHeaderFile.h"
#include "LCD16x2HeaderFile.h"
#include "DHTHeaderFile.h"
#include "functions.h"
#include <stdio.h>
#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) {
    char humidityInt, humidityDec, temperatureInt, temperatureDec, checksum, humidity[10], temperature[10];
    
    OSCCON=0x72;                         // Use Internal Oscillator with Frequency 8MHZ
    ADCON1=0x0F;
    
    LCD_Init();
    
    while(1)
    {
        LCD_Clear();
        
        DHT11Start();
        
        if(DHT11CheckResponse())
        {
            // read 40-bit data from DHT11 module
            humidityInt = DHT11ReadData();          // read Relative Humidity's integral value
            humidityDec = DHT11ReadData();          // read Relative Humidity's decimal value
            temperatureInt = DHT11ReadData();       // read Temperature's integral value
            temperatureDec = DHT11ReadData();       // read Relative Temperature's decimal value
            checksum = DHT11ReadData();             // read 8-bit checksum value
            
            // convert humidity value to ascii and send it to display
            //sprintf(buf, "T: %02d C H: %02d%%  ", tb, hb);
            sprintf(humidity,"H: %02d%%",humidityInt);
            LCD_String_xy(0,0,humidity);
    
            /* convert temperature value to ascii and send it to display*/
            sprintf(temperature,"T: %02d C",temperatureInt);
            LCD_String_xy(2,0,temperature);
    
            /* check addition of humidity and temperature value equals to checksum */
            if(checksum != (humidityInt + humidityDec + temperatureInt + temperatureDec))
                LCD_String_xy(0,8,"Error");
            else
                LCD_String_xy(0,8,"No Error");
        }
        else
        {
            LCD_String_xy(0,0,"No response!");
        }
        
        msDelay(1000);
    }
}

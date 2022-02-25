/*
 * File:   main.c
 * Author: juan0
 *
 * Created on 23 de febrero de 2022, 11:22 PM
 */

#include "configPICHeaderFile.h"
#include "LCD16x2HeaderFile.h"
//#include "DHTHeaderFile.h"
#include "functions.h"
#include <stdio.h>
#include <xc.h>
#define _XTAL_FREQ 8000000
#include "DHTLib.h"

void main(void) {
    uint8_t tb = 0, hb = 0;
    char value[20];
    OSCCON=0x72;                         // Use Internal Oscillator with Frequency 8MHZ
    ADCON1=0x0F;
    LCD_Init();
    dhtlib_init();
    
    LCD_String_xy(0,0,"Starting...");
    msDelay(2000);
    LCD_Clear();
    
    while(1)
    {
        enum dht_status result = dhtlib_read11(&tb, &hb);
        if (result == E_DHTLIB_OK)
			sprintf(value, "T: %02d C H: %02d%%  ", tb, hb);
		else
			sprintf(value, "Sensor error: %02d    ", result);
        LCD_String_xy(0,0,value);
        msDelay(5000);
        LCD_Clear();
        
        //DHT11Start();
        /*
        if(DHT11CheckResponse())
        {
            LCD_String_xy(0,0,"Success");
            msDelay(1000);
            LCD_Clear();
        }
        else
        {
            LCD_String_xy(0,0,"No response!");
            msDelay(1000);
            LCD_Clear();
        }
        */
        
        /*
        MSdelay(1000);
        
        LCD_String_xy(0,0,"Hola!");
        MSdelay(500);
    
        DHT11_Start();
        //DHT11_CheckResponse();          // wait for response from DHT11 module
        
        LCD_String_xy(0,0,"Start");
        MSdelay(500);
            
        // read 40-bit data from DHT11 module
        RH_Integral = DHT11_ReadData(); // read Relative Humidity's integral value
        RH_Decimal = DHT11_ReadData();  // read Relative Humidity's decimal value
        T_Integral = DHT11_ReadData();  // read Temperature's integral value
        T_Decimal = DHT11_ReadData();   // read Relative Temperature's decimal value
        Checksum = DHT11_ReadData();    // read 8-bit checksum value
            
        // convert temperature value to ascii and send it to display
        sprintf(value,"%d",RH_Integral);
        LCD_String_xy(0,0,value);
        MSdelay(2000);
        sprintf(value,".%d ",RH_Decimal);
        LCD_String(value);
        MSdelay(2000);
        LCD_Char('%');
        MSdelay(2000);
            
        // convert temperature value to ascii and send it to display
        sprintf(value,"%d",T_Integral);
        LCD_String_xy(1,0,value);
        MSdelay(2000);
        sprintf(value,".%d",T_Decimal);
        LCD_String(value);
        MSdelay(2000);
        LCD_Char(0xdf);
        MSdelay(2000);
        LCD_Char('C');
        MSdelay(2000);
    
        sprintf(value,"%d  ",Checksum);
        LCD_String_xy(1,8,value);
        MSdelay(2000);
            
        // check addition of humidity and temperature value equals to checksum
        if(Checksum != (RH_Integral + RH_Decimal + T_Integral + T_Decimal))
        {
            LCD_String_xy(0,8,"Error");
            MSdelay(2000);
        }
        else
        {
            LCD_String_xy(0,8,"No Error");
            MSdelay(2000);
        }
    
        MSdelay(500);
        
        LCD_String_xy(0,0,"Read");
        MSdelay(1000);
        LCD_Clear();
        */
    }
}

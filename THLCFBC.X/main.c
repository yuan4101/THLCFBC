
#define _XTAL_FREQ 8000000
#include "configPICHeaderFile.h"
#include "lcdHeaderFile.h"
#include "dhtHeaderFile.h"
#include "functionsHeaderFile.h"
#include "ldrHeaderFile.h"
#include <xc.h>
#include <stdio.h>

void main(void) {
    char light, humidityInt, humidityDec, temperatureInt, temperatureDec, checksum;
    char error = 0, check = 1, value[10];
    int health;
    
    lcdInit();
    configLeds();
    lcdClear();
    msDelay(10);
    lcdDirCustomChar(0, chError);
    lcdDirCustomChar(1, chCheck);
    
    OSCCON=0x72;
    ADCON1bits.PCFG=0b1100;
    
    configADC();
    
    while(1){
        
        DHT11Start();
        
        if(DHT11CheckResponse()){
            humidityInt = DHT11ReadData();
            humidityDec = DHT11ReadData();
            temperatureInt = DHT11ReadData();
            temperatureDec = DHT11ReadData();
            checksum = DHT11ReadData();
            
            lcdStringXY(0, 0, "T:");
            lcdStringXY(10, 0, "H:");
          
            sprintf(value, "%02dC", temperatureInt);
            lcdStringXY(3, 0, value);
            
            sprintf(value, "%02d%%", humidityInt);
            lcdStringXY(13, 0, value);
            
            if(checksum != (humidityInt + humidityDec + temperatureInt + temperatureDec))
                lcdCustomCharXY(15, 2, error);
            else
                lcdCustomCharXY(15, 2, check);
        }
        else{
            lcdClear();
            lcdStringXY(2, 0, "No response!");
            lcdCustomCharXY(15, 2, error);
        }
        light = ldrPercentValue();
        lcdStringXY(0, 2, "lx:");
        sprintf(value, "%3u%%", light);
        lcdStringXY(4, 2, value);
        
        health = humidityInt * temperatureInt;
        
        if((humidityInt <= 35) || (humidityInt >= 55) || (temperatureInt <= 18) || (temperatureInt >= 21))
            setRedLed();
        else if((health <= 810) || (health >= 945))
            setYellowLed();
        else
            setGreenLed();
            
        
        msDelay(1000);
    }
}
#define minHumidity 35
#define maxHumidity 55
#define minTemp 18
#define maxTemp 21
#define minLight 30
#define maxLight 70
#define minHealth 810
#define maxHealth 945

#include "configPICHeaderFile.h"
#include "functionsHeaderFile.h"
#include "lcdHeaderFile.h"
#include <stdio.h>

char error = 0, check = 1, value[10];
int health;

void main(void) {
    
    configInit();
    
    configADC();
    
    I2CInit(100000);
    
    lcdInit();
    lcdDirCustomChar(0, chError);
    lcdDirCustomChar(1, chCheck);
    
    configLeds();
    
    while(1){
        
        DHT11Start();
        
        if(DHT11CheckResponse()){
            humidityInt = DHT11ReadData();
            humidityDec = DHT11ReadData();
            temperatureInt = DHT11ReadData();
            temperatureDec = DHT11ReadData();
            checksum = DHT11ReadData();
            light = ldrPercentValue();
            
            lcdStringXY(0, 0, "T:");
            lcdStringXY(10, 0, "H:");
            lcdStringXY(0, 2, "lx:");
          
            sprintf(value, "%02dC", temperatureInt);
            lcdStringXY(3, 0, value);
            
            sprintf(value, "%02d%%", humidityInt);
            lcdStringXY(13, 0, value);
            
            sprintf(value, "%3u%%", light);
            lcdStringXY(4, 2, value);
            
            if(checksum != (humidityInt + humidityDec + temperatureInt + temperatureDec))
                lcdCustomCharXY(15, 2, error);
            else
                lcdCustomCharXY(15, 2, check);
        }
        else {
            lcdClear();
            lcdStringXY(2, 0, "No response!");
            lcdCustomCharXY(15, 2, error);
            msDelay(1000);
            lcdClear();
        }
        
        health = humidityInt * temperatureInt;
        
        if((humidityInt <= minHumidity) || (humidityInt >= maxHumidity) || (temperatureInt <= minTemp) || (temperatureInt >= maxTemp) || (light >= maxLight))
            setRedLed();
        else if((health <= minHealth) || (health >= maxHealth) || ((light >= minLight) && (light < maxLight)))
            setYellowLed();
        else
            setGreenLed();
        
        readTime();
        
        createCSV();

        msDelay(1000);
    }
}
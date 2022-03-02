
#define _XTAL_FREQ 8000000
#include "configPICHeaderFile.h"
#include "lcdHeaderFile.h"
#include "dhtHeaderFile.h"
#include "functionsHeaderFile.h"
#include "ldrHeaderFile.h"
#include "I2CHeaderFile.h"                   // Incluimos la librería I2C.
#include <xc.h>
#include <stdio.h>

uint8_t hours;                             // Variable de 8 bits para las horas.
uint8_t minutes;                           // Variable de 8 bits para los minutos.
uint8_t seconds;                           // Variable de 8 bits para los segundos.
uint8_t year;                              // Variable de 8 bits para los año.
uint8_t month;                             // Variable de 8 bits para el mes.
uint8_t day;                               // Variable de 8 bits para el dia.
uint8_t i;                                 // Variable de 8 bits.

char light, humidityInt, humidityDec, temperatureInt, temperatureDec, checksum;
char error = 0, check = 1, value[10];
int health;

char buffer_TX[] = "Humidity(%):xx, Temperature(C):xx, Light(%):xxx, Date:dd/mm/20aa hh:mm:ss\r";

uint8_t Decimal_a_BCD (uint8_t numero);    // Función que convierte un número decimal a BCD. 
uint8_t BCD_a_Decimal (uint8_t numero);    // Función que convierte un número BCD a decimal.
void Reloj_Calendario (void);              // Función de visualización de HORA Y FECHA.

uint8_t BCD_a_Decimal (uint8_t numero)            // Función que convierte un número BCD a decimal.
{
  return ((numero >> 4) * 10 + (numero & 0x0F));  // Retornamos la variable "numero" desplazado 4 posiciones a la izquierda, multiplicado por 10 más "numero" &&  1111.
}

uint8_t Decimal_a_BCD (uint8_t numero)            // Función que convierte un número decimal a BCD. 
{
    return (((numero / 10) << 4) + (numero % 10));// Retornamos la decena de la variable "numero" desplazado 4 bits a la derecha y las unidades de la variable "numero" en el nibble menos significativo
}

void Reloj_Calendario (void)                //Función de visualización de HORA Y FECHA.
{
    static char Time[] = "TIME: 00:00:00";  // Arreglo estático char "Time". 
    static char Date[] = "DATE: 00/00/2000";// Arreglo estático char "Date".
  
    seconds = BCD_a_Decimal(seconds);       // Llamamos a la función de conversión de BCD a Decimal.
    minutes = BCD_a_Decimal(minutes);       // Llamamos a la función de conversión de BCD a Decimal.
    hours   = BCD_a_Decimal(hours);         // Llamamos a la función de conversión de BCD a Decimal.
    day     = BCD_a_Decimal(day);           // Llamamos a la función de conversión de BCD a Decimal.
    month   = BCD_a_Decimal(month);         // Llamamos a la función de conversión de BCD a Decimal.
    year    = BCD_a_Decimal(year);          // Llamamos a la función de conversión de BCD a Decimal.
    
    Time[6] =  hours   / 10 + '0';          // Guardamos las decenas de la variable "hours" en la posición 6 del arreglo "Time".
    Time[7] =  hours   % 10 + '0';          // Guardamos las unidades de la variable "hours" en la posición 7 del arreglo "Time".
    Time[9] =  minutes / 10 + '0';          // Guardamos las decenas de la variable "minutes" en la posición 9 del arreglo "Time".
    Time[10]=  minutes % 10 + '0';          // Guardamos las unidades de la variable "minutes" en la posición 10 del arreglo "Time".
    Time[12]=  seconds / 10 + '0';          // Guardamos las decenas de la variable "seconds" en la posición 12 del arreglo "Time".
    Time[13]=  seconds % 10 + '0';          // Guardamos las unidades de la variable "secods" en la posición 13 del arreglo "Time".
    
    Date[6] =  day     / 10 + '0';          // Guardamos las decenas de la variable "day" en la posición 6 del arreglo "Date".
    Date[7] =  day     % 10 + '0';          // Guardamos las unidades de la variable "day" en la posición 7 del arreglo "Date".
    Date[9] =  month   / 10 + '0';          // Guardamos las decenas de la variable "month" en la posición 9 del arreglo "Date".
    Date[10]=  month   % 10 + '0';          // Guardamos las unidades de la variable "month" en la posición 10 del arreglo "Date".
    Date[14]=  year    / 10 + '0';          // Guardamos las decenas de la variable "year" en la posición 14 del arreglo "Date".
    Date[15]=  year    % 10 + '0';          // Guardamos las unidades de la variable "year" en la posición 15 del arreglo "Date".
    
    buffer_TX[54] = Date[6];
    buffer_TX[55] = Date[7];
    buffer_TX[57] = Date[9];
    buffer_TX[58] = Date[10];
    buffer_TX[62] = Date[14];
    buffer_TX[63] = Date[15];
    buffer_TX[65] = Time[6];
    buffer_TX[66] = Time[7];
    buffer_TX[68] = Time[9];
    buffer_TX[69] = Time[10];
    buffer_TX[71] = Time[12];
    buffer_TX[72] = Time[13];
    
    //lcdStringXY(0, 0, Time);
    //lcdStringXY(0, 2, Date);
}

void main(void) {
    
    OSCCON=0x72;
    ADCON1bits.PCFG=0b1100;
    
    configADC();
    
    I2CInit(100000);                       // Inicializamos la comunicación I2C con una frecuencia de 100KHz. para el DS1307.
    lcdInit();
    configLeds();
    lcdClear();
    lcdDirCustomChar(0, chError);
    lcdDirCustomChar(1, chCheck);
    
    while(1){
        
        I2CStart();                        // Llamamos a la función Start.
        I2CWrite(0xD0);                    // Escribimos en SSPBUF la dirección de DS1307 1101000 + 0 de escritura.
        I2CWrite(0);                       // Dirección de segundos.
        I2CReStart();                      // Llamamos a la función ReStart.
        I2CWrite(0xD1);                    // Escribimos en SSPBUF la dirección de DS1307 1101000 +1 de lectura.
        seconds=I2CRead();                 // Cargamos la variable "seconds" con el valor de SSPBUF.
        I2CAck();                          // ACK.
        minutes=I2CRead();                 // Cargamos la variable "minutes" con el valor de SSPBUF.
        I2CAck();                          // ACK.
        hours=I2CRead();                   // Cargamos la variable "hours" con el valor de SSPBUF.
        I2CAck();                          // ACK.
        I2CRead();                         // Valor no leido.
        I2CAck();                          // ACK.
        day=I2CRead();                     // Cargamos la variable "day" con el valor de SSPBUF.
        I2CAck();                          // ACK.
        month=I2CRead();                   // Cargamos la variable "month" con el valor de SSPBUF.
        I2CAck();                          // ACK.
        year=I2CRead();                    // Cargamos la variable "year" con el valor de SSPBUF.
        I2CNoAck();                       // NO ACK.
        I2CStop();                         // Llamamos a la función Stop.
        
        Reloj_Calendario();                 // Llamamos a la función Reloj_Calendario().
        
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
        
        buffer_TX[12] = humidityInt / 10 + '0';
        buffer_TX[13] = humidityInt % 10 + '0';
        buffer_TX[31] = temperatureInt / 10 + '0';
        buffer_TX[32] = temperatureInt % 10 + '0';
        if(light == 100)
        {
            buffer_TX[44] = '1';
            buffer_TX[45] = '0';
            buffer_TX[46] = '0';
        } 
        else{
            buffer_TX[44] = '0';
            buffer_TX[45] = light / 10 + '0';
            buffer_TX[46] = light % 10 + '0';
        }
        
        
        health = humidityInt * temperatureInt;
        
        if((humidityInt <= 35) || (humidityInt >= 55) || (temperatureInt <= 18) || (temperatureInt >= 21) || (light >= 70))
            setRedLed();
        else if((health <= 810) || (health >= 945) || ((light >= 35) && (light < 70)))
            setYellowLed();
        else
            setGreenLed();
        
        //Configura UART a 9600 baudios
        TRISCbits.RC6 = 0; //  Pin RC6 como salida digital para TX.
        TXSTAbits.TX9 = 0; //  Modo-8bits.
        TXSTAbits.TXEN = 1; //  Habilita Transmisión.
        TXSTAbits.SYNC = 0; //  Modo-Asíncrono.
        TXSTAbits.BRGH = 0; //  Modo-Baja Velocidad de Baudios.
        BAUDCONbits.BRG16 = 0; //  Baudios modo-8bits.
        RCSTAbits.SPEN = 1; //  Hbilita el Módulo SSP como UART.
        SPBRG = (unsigned char) (((_XTAL_FREQ / 9600) / 64) - 1); //baudios  = 9600
        //Inicia el proceso de transmisión TX.
        for (int i = 0; i < 74; i++) {
            //  espera a que el registro de transmisión este disponible o vacio.
            while (!TXSTAbits.TRMT) {
            }
            //  escribe el dato que se enviará a través de TX.
            TXREG = buffer_TX[i];
        }

        msDelay(1000);
    }
}
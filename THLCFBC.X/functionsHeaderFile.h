#define _XTAL_FREQ 8000000
#define dirRed TRISBbits.TRISB2
#define dirYellow TRISBbits.TRISB3
#define dirGreen TRISBbits.TRISB4
#define setRed LATBbits.LATB2
#define setYellow LATBbits.LATB3
#define setGreen LATBbits.LATB4
#include "dhtHeaderFile.h"
#include "ldrHeaderFile.h"
#include "rtcHeader.h"
#include <xc.h>

int csvTitle = 0;
char ledState;
char columns[] = "Fecha,Hora,HumedadRelativa(%),Temperatura(C),Luz(%),Advertencia\r";
char bufferTX[] = "DD/MM/20AA,HH:MM,HH,TT,LLL,S\r";

void msDelay(unsigned int val);
void configInit();
void configADC();
void createCSV();
void uart();
void uartColumns();
void configLeds();
void setRedLed();
void setYellowLed();
void setGreenLed();
void setOffLeds();
void setOnLeds();
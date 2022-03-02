#include "functionsHeaderFile.h"
#include <xc.h>

/*********************************Delay Function********************************/
void msDelay(unsigned int val)
{
    unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);      //This count Provide delay of 1 ms for 8MHz Frequency
}

void configADC(){
    //Configuramos Modulo ADC
    ADCON1bits.VCFG=0b00;      //Tensiones de referencia +5v y 0v
    ADCON2bits.ADCS=0b001;     //Reloj de conversion 8*Tosc >>> TAD=1us > 0.7us
    ADCON2bits.ACQT=0b010;     //4TAD=4us > 2.45us 
    ADCON2bits.ADFM=1;         //Justificacion a la derecha.
    ADCON0bits.ADON=1;         //Conversor Analogico Digital Habilitado.
    ADCON0bits.CHS=0b0000;     //Habilitamos el canal AN0.
}

void configLeds(){
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
}

void setRedLed(){
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 0;
    LATBbits.LATB4 = 0;
}

void setYellowLed(){
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 1;
    LATBbits.LATB4 = 0;
}

void setGreenLed(){
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    LATBbits.LATB4 = 1;
}

void setOffLeds(){
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    LATBbits.LATB4 = 0;
}

void setOnLeds(){
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 1;
    LATBbits.LATB4 = 1;
}
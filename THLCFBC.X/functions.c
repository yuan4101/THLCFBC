#include "functionsHeaderFile.h"

void msDelay(unsigned int val){
    unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);     //This count Provide delay of 1 ms for 8MHz Frequency
}

void configInit(){
    ADCON1bits.PCFG=0b1100;     //Set RA2 as analogic AN2
}

void configADC(){
    ADCON1bits.VCFG=0b00;      //Tensiones de referencia +5v y 0v
    ADCON2bits.ADCS=0b001;     //Reloj de conversion 8*Tosc >>> TAD=1us > 0.7us
    ADCON2bits.ACQT=0b010;     //4TAD=4us > 2.45us 
    ADCON2bits.ADFM=1;         //Justificacion a la derecha.
    ADCON0bits.ADON=1;         //Conversor Analogico Digital Habilitado.
    ADCON0bits.CHS=0b0000;     //Habilitamos el canal AN0.
}

void createCSV(){
    if(csvTitle == 0){
        uartColumns();
        csvTitle++;
    }
    
    bufferTX[0] = Date[6];      //Tens  day
    bufferTX[1] = Date[7];      //Units day
    bufferTX[3] = Date[9];      //Tens  Month
    bufferTX[4] = Date[10];     //Units Month
    bufferTX[8] = Date[14];     //Tens  year
    bufferTX[9] = Date[15];     //Units year
    bufferTX[11] = Time[6];     //Tens  hour
    bufferTX[12] = Time[7];     //Units hour
    bufferTX[14] = Time[9];     //Tens  minutes
    bufferTX[15] = Time[10];    //Units minutes
    
    bufferTX[17] = humidityInt / 10 + '0';      //Tens  humidity
    bufferTX[18] = humidityInt % 10 + '0';      //Units humidity
    bufferTX[20] = temperatureInt / 10 + '0';   //Tens  temperature
    bufferTX[21] = temperatureInt % 10 + '0';   //Units temperature
    
    if(light == 100) {  //Light value when 100        
        bufferTX[23] = '1';
        bufferTX[24] = '0';
        bufferTX[25] = '0';
    } 
    else {  //Light value different 100
        bufferTX[23] = '0';
        bufferTX[24] = light / 10 + '0';
        bufferTX[25] = light % 10 + '0';
    }
    
    bufferTX[27] = ledState;  //Led state
    
    uart(); //Communication
}

void uart(){
    //Configura UART a 9600 baudios
    TRISCbits.RC6 = 0;      //Pin RC6 como salida digital para TX.
    TXSTAbits.TX9 = 0;      //Modo-8bits.
    TXSTAbits.TXEN = 1;     //Habilita Transmisión.
    TXSTAbits.SYNC = 0;     //Modo-Asíncrono.
    TXSTAbits.BRGH = 0;     //Modo-Baja Velocidad de Baudios.
    BAUDCONbits.BRG16 = 0;  //Baudios modo-8bits.
    RCSTAbits.SPEN = 1;     //Habilita el Módulo SSP como UART.
    SPBRG = (unsigned char) (((_XTAL_FREQ / 9600) / 64) - 1);   //baudios  = 9600
    
    //Inicia el proceso de transmisión TX.
    for (int i = 0; i < 29; i++) {
        
        //Espera a que el registro de transmisión este disponible o vacio.
        while (!TXSTAbits.TRMT);
        
        //Escribe el dato que se enviará a través de TX.
        TXREG = bufferTX[i];
    }
}

void uartColumns(){
    //Configura UART a 9600 baudios
    TRISCbits.RC6 = 0;      //Pin RC6 como salida digital para TX.
    TXSTAbits.TX9 = 0;      //Modo-8bits.
    TXSTAbits.TXEN = 1;     //Habilita Transmisión.
    TXSTAbits.SYNC = 0;     //Modo-Asíncrono.
    TXSTAbits.BRGH = 0;     //Modo-Baja Velocidad de Baudios.
    BAUDCONbits.BRG16 = 0;  //Baudios modo-8bits.
    RCSTAbits.SPEN = 1;     //Habilita el Módulo SSP como UART.
    SPBRG = (unsigned char) (((_XTAL_FREQ / 9600) / 64) - 1);   //baudios  = 9600
    
    //Inicia el proceso de transmisión TX.
    for (int i = 0; i < 64; i++) {
        
        //Espera a que el registro de transmisión este disponible o vacio.
        while (!TXSTAbits.TRMT);
        
        //Escribe el dato que se enviará a través de TX.
        TXREG = columns[i];
    }
}

void configLeds(){
    dirRed = 0;
    dirYellow = 0;
    dirGreen = 0;
    ledState = 'N';
}

void setRedLed(){
    setRed = 1;
    setYellow = 0;
    setGreen = 0;
    ledState = 'R';
}

void setYellowLed(){
    setRed = 0;
    setYellow = 1;
    setGreen = 0;
    ledState = 'Y';
}

void setGreenLed(){
    setRed = 0;
    setYellow = 0;
    setGreen = 1;
    ledState = 'G';
}

void setOffLeds(){
    setRed = 0;
    setYellow = 0;
    setGreen = 0;
    ledState = 'N';
}

void setOnLeds(){
    setRed = 1;
    setYellow = 1;
    setGreen = 1;
    ledState = 'T';
}
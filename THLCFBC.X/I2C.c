#include "I2CHeaderFile.h"
#define _XTAL_FREQ 8000000
#include <xc.h>                // include processor files - each processor file is guarded.

/*==========================================================================================================
 ===========================================================================================================*/
void I2CInit (uint32_t frecuencia)//Función de inicialización del periferico I2C.    
{
    TRISB|=(1<<0);           // Configuramos como entrada digital el pin RB0 (SDA) debido a las resistencias Pull Up.
    TRISB|=(1<<1);           // Configuramos como entrada digital el pin RB1 (SCL) debido a las resistencias Pull Up.
    
    SSPSTATbits.CKE=0;       // Registro SSPSTAT MSSP STATUS REGISTER.
                             // CKE (bit 6) SMBus Select bit.
                             // CKE=0 >> SMbus deshabilitado entradas específicas.
                             // CKE=1 >> SMbus habilitado entradas específicas.
    
    SSPSTATbits.SMP=1;       // Registro SSPSTAT MSSP STATUS REGISTER.
                             // SMP (bit 7) Slew Rate Control bit
                             // SMP=0 >> modo velocidad standard 100KHz.
                             // SMP=1 >> modo alta velocidad 400KHz.
    
    SSPCON1bits.SSPEN=1;     // Registro SSPCON1 MSSP CONTROL REGISTER 1 (MODO I2C).
                             // SSPEN (bit 5) Master Synchronous Serial Port Enable bit
                             // SSPEN=0 >> Deshabilita el puerto serie y los pines RB0 y RB1 son configurados como I/O digitales.
                             // SSPEN=1 >> Habilita el puerto serie y los pines RB0 y RB1 son establecidos como SDA y SCL respectivamente.
    
    SSPCON1bits.SSPM=0b1000; // Registro SSPCON1 MSSP CONTROL REGISTER (MODO I2C).
                             // SSPM3-SSPM0 Master Synchronous Serial Port Mode Select bits.
                             // 1111 >> I2C modo esclavo, dirección 10 bits, con bits Start Stop, Interrupción habilitada.
                             // 1110 >> I2C modo esclavo, dirección 7 bits, con bits Start Stop, Interrupción habilitada.
                             // 1011 >> Firmware controlado por el maestro (esclavo deshabilitado).
                             // 1000 >> Modo Maestro, clock=Fosc/(4*(SSPADD+1)).
                             // 0111 >> Modo esclavo, direccion 10 bits.
                             // 0110 >> Modo esclavo, direccion 7 bits.
    
    SSPCON2=0x00;            // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C).
    
    SSPADD = ((_XTAL_FREQ/(4*frecuencia))-1); // clock=Fosc/(4*(SSPADD+1)).                               
}

/*==========================================================================================================
 ===========================================================================================================*/
void I2CStart (void)       // Función que inicia la comunicación I2C.
{
    SSPCON2bits.SEN=1;      // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C)
                            // SEN (bit 0) Start Condition Enable/Stretch Enable bit.
                            // SEN=0 >> Condición Start a la espera.
                            // SEN=1 >> Condición Start habilitada para SDA y SCL, SEN se pone a 0 automaticamente por hardware.
    while(SSPCON2bits.SEN); // Esperamos hasta que se termine de establecer la condición de inicio.
}

/*==========================================================================================================
 ===========================================================================================================*/
void I2CReStart (void)     // Función que reinicia la comuncación I2C.
{
    SSPCON2bits.RSEN=1;     // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C)
                            // RSEN (bit 1) Repeated Start Condition Enable bit.
                            // RSEN=0 >> Condición Restart a la espera.
                            // RSEN=1 >> Condición Restart habilitada para SDA y SCL, SEN se pone a 0 automaticamente por hardware.
    while(SSPCON2bits.RSEN); // Esperamos hasta que se termine de establecer la condición de inicio.
}

/*==========================================================================================================
 ===========================================================================================================*/
void I2CStop (void)        // Función que detiene la comunicación I2c.
{
    SSPCON2bits.PEN=1;      // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C).
                            // PEN (bit 2) Stop Condition Enable bit.
                            // PEN=0 >> Condición de Stop a la espera.
                            // PEN=1 >> Condición Stop habilitada para SDA y SCL, PEN se pone a 0 automaticamente por hardware.
    while(SSPCON2bits.PEN); // Esperamos hasta que se termine de establecer la condición de parada.
}

/*==========================================================================================================
 ===========================================================================================================*/
void I2CAck (void)         // Función para transmitir Acknowledge.
{
    PIR1bits.SSPIF=0;       // Master Synchronous Serial Port Interrupt Flag bit
                            // SSPIF=0 >> A la espera de la transmisión o recepción 
                            // SSPIF=1 >> La transmisión o recepción ha sido completada, este bit se limpia por hardware.
            
    SSPCON2bits.ACKDT=0;    // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C).
                            // ACKDT (bit 5) Acknowledge Data bit
                            // ACKDT=0 >> Acknowledge
                            // ACKDT=1 >> NO Acknowledge.
    
    SSPCON2bits.ACKEN=1;    // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C). 
                            // ACKEN (bit 4) Acknowledge Sequence Enable bit.
                            // ACKEN=0 >> Secuencia Acknowledge a la espera.
                            // ACKEN=1 >> Inicia la secuencia Acknowledge, este bit se limpia automaticamente por hardware.
    
    while(PIR1bits.SSPIF==0);//Esperamos hasta que se complete la transmisión/recepción.
}

/*==========================================================================================================
 ===========================================================================================================*/
void I2CNoAck (void)      // Función para transmitir NO Acknowledge.
{
    PIR1bits.SSPIF=0;       // Master Synchronous Serial Port Interrupt Flag bit
                            // SSPIF=0 >> A la espera de la transmisión o recepción 
                            // SSPIF=1 >> La transmisión o recepción ha sido completada, este bit se limpia por hardware.
            
    SSPCON2bits.ACKDT=1;    // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C).
                            // ACKDT (bit 5) Acknowledge Data bit
                            // ACKDT=0 >> Acknowledge
                            // ACKDT=1 >> NO Acknowledge.
    
    SSPCON2bits.ACKEN=1;    // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C). 
                            // ACKEN (bit 4) Acknowledge Sequence Enable bit.
                            // ACKEN=0 >> Secuencia Acknowledge a la espera.
                            // ACKEN=1 >> Inicia la secuencia Acknowledge, este bit se limpia automaticamente por hardware.
    
    while(PIR1bits.SSPIF==0);//Esperamos hasta que se complete la transmisión/recepción.
}

/*==========================================================================================================
 ===========================================================================================================*/
void I2CWrite (uint8_t data)// Función para escribir el SSPBUF.
{
    PIR1bits.SSPIF=0;        // Master Synchronous Serial Port Interrupt Flag bit
                             // SSPIF=0 >> A la espera de la transmisión o recepción.
                             // SSPIF=1 >> La transmisión o recepción ha sido completada, este bit se limpia por hardware.
    
    SSPBUF=data;             // Cargamos el registro SSPBUF con los valores de la variable "data".
    
    while(PIR1bits.SSPIF==0);//Esperamos hasta que se complete la transmisión.
}

/*==========================================================================================================
 ===========================================================================================================*/
uint8_t I2CRead (void)      // Función para leer el SSPBUF.
{
    PIR1bits.SSPIF=0;        // Master Synchronous Serial Port Interrupt Flag bit
                             // SSPIF=0 >> A la espera de la transmisión o recepción.
                             // SSPIF=1 >> La transmisión o recepción ha sido completada, este bit se limpia por hardware.
    
    SSPCON2bits.RCEN=1;      // Registro SSPCON2 MSSP CONTROL REGISTER 2 (modo I2C).
                             // RCEN (bit 3) Receive Enable bit (Master Receive mode only).
                             // RCEN=0 >> recepción a la espera.
                             // RCEN=1 >> recepción habilitada.
    
    while(PIR1bits.SSPIF==0);// Esperamos hasta que se complete la recepción.
    
    return SSPBUF;           // Retornamos el valor de SSPBUF en una variable entera de 8 bits.
}
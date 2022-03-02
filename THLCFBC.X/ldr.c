
#include "ldrHeaderFile.h"
#include <xc.h>

unsigned int ldrValue(){
    unsigned int lightValue=0;          //Registro de proposito General entero 16 bits "Radc" Resolucion del voltaje LDR
    ADCON0bits.CHS = 2;
    ADCON0bits.GO_DONE=1;               //Inicializamos la conversion AD
    while(ADCON0bits.GO_DONE==1);       //Esperamos ha que termine la conversion AD.
    lightValue=ADRESH;                  //Cargamos Radc con los 8 bits del registro ADRESH
    lightValue=lightValue<<8;           //Desplazamos 8 bits del registro Radc a la izquierda.
    lightValue|=ADRESL;                 //Realizamos una operacion logica OR entre Radc y ADRESL el resultado se almacena en Radc
    return lightValue;
}

unsigned int ldrPercentValue(){
    unsigned int value = ldrValue();
    long percent = value;
    if(value<=49)
        return 100;
    if(value>=1013)
        return 0;
    percent = (((percent*100)/1013)-100)*(-1);
    return percent;
}
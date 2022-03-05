#define _XTAL_FREQ 8000000
#define a3DataMode TRISAbits.TRISA3
#define a3DataOut LATAbits.LATA3
#define a3DataIn PORTAbits.RA3
#include <xc.h>

char light, humidityInt, humidityDec, temperatureInt, temperatureDec, checksum;

void DHT11Start();
short DHT11CheckResponse();
char DHT11ReadData();
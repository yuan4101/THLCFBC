
#define a3DataMode TRISAbits.TRISA3
#define a3DataOut LATAbits.LATA3
#define a3DataIn PORTAbits.RA3

void DHT11Start();
short DHT11CheckResponse();
char DHT11ReadData();
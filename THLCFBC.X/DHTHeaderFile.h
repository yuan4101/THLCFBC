/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#define _XTAL_FREQ 8000000                  // define _XTAL_FREQ for using internal delay
#define dataMode TRISAbits.TRISA0
#define dataOut LATAbits.LATA0
#define dataIn PORTAbits.RA0

void DHT11Start();
short DHT11CheckResponse();
char DHT11ReadData();
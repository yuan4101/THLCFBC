/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

/*
#define Data_Out LATAbits.LA0            // assign Port pin for data
#define Data_In PORTAbits.RA0               // read data from Port pin
#define Data_Dir TRISAbits.RA0              // Port direction 
*/

#define _XTAL_FREQ 8000000                  // define _XTAL_FREQ for using internal delay
#define dataMode TRISAbits.TRISA0
#define dataOut LATAbits.LATA0
#define dataIn PORTAbits.RA0

void DHT11Start();
short DHT11CheckResponse();

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();
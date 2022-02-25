/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#define RS LATD0                    /*PORTD 0 pin is used for Register Select*/
#define EN LATD1                    /*PORTD 1 pin is used for Enable*/
#define ldata LATB                  /*PORTB is used for transmitting data to LCD*/

void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);
void LCD_Clear();
void LCD_Custom_Char(unsigned char,unsigned char*);

unsigned char character1[8] = {0x00, 0x1f, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x00}; /* Value for Pi */
unsigned char character2[8] = {0x11, 0x19, 0x1d, 0x1f, 0x1d, 0x19, 0x11, 0x00}; /* Value for Diode */
unsigned char character3[8] = {0x12, 0x14, 0x18, 0x10, 0x18, 0x15, 0x13, 0x17}; /* Value for Transistor */
unsigned char character4[8] = {0x0a, 0x0a, 0x0a, 0x1b, 0x0a, 0x0a, 0x0a,0x00};  /* Value for Capacitor */
unsigned char character5[8] = {0x00, 0x0e, 0x011, 0x11, 0x11, 0x0a, 0x1B, 0x00};/* Value for Ohm */

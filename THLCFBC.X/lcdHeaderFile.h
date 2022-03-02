
#define RS LATE0                    /*PORTE 0 pin is used for Register Select*/
#define EN LATE1                    /*PORTE 1 pin is used for Enable*/
#define ldata LATD                  /*PORTD is used for transmitting data to LCD*/

void lcdInit();
void lcdCommand(char );
void lcdChar(char x);
void lcdString(const char *);
void lcdStringXY(char ,char ,const char*);
void lcdClear();
void lcdDirCustomChar(unsigned char,unsigned char*);
void lcdCustomCharXY(char, char, char);

unsigned char chPi[8] = {0x00, 0x1f, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x00};           //Value for Pi
unsigned char chDiode[8] = {0x11, 0x19, 0x1d, 0x1f, 0x1d, 0x19, 0x11, 0x00};        //Value for Diode
unsigned char chTransistor[8] = {0x12, 0x14, 0x18, 0x10, 0x18, 0x15, 0x13, 0x17};   //Value for Transistor
unsigned char chCapacitor[8] = {0x0a, 0x0a, 0x0a, 0x1b, 0x0a, 0x0a, 0x0a,0x00};     //Value for Capacitor
unsigned char chOhm[8] = {0x00, 0x0e, 0x011, 0x11, 0x11, 0x0a, 0x1B, 0x00};         //Value for Ohm
unsigned char chCheck[8] = {0x00, 0x01, 0x03, 0x16, 0x1C, 0x08, 0x00, 0x00};        //Check
unsigned char chError[8] = {0x11, 0x1B, 0x0E, 0x04, 0x04, 0x0E, 0x1B, 0x11};        //Fail
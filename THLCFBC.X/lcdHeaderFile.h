#define RS LATE0                    /*PORTE 0 pin is used for Register Select*/
#define EN LATE1                    /*PORTE 1 pin is used for Enable*/
#define ldata LATD                  /*PORTD is used for transmitting data to LCD*/

unsigned char chCheck[8] = {0x00, 0x01, 0x03, 0x16, 0x1C, 0x08, 0x00, 0x00};        //Check
unsigned char chError[8] = {0x11, 0x1B, 0x0E, 0x04, 0x04, 0x0E, 0x1B, 0x11};        //Fail

void lcdInit();
void lcdCommand(char );
void lcdChar(char x);
void lcdString(const char *);
void lcdStringXY(char ,char ,const char*);
void lcdClear();
void lcdDirCustomChar(unsigned char,unsigned char*);
void lcdCustomCharXY(char, char, char);

#include "lcdHeaderFile.h"
#include "functionsHeaderFile.h"
#include <xc.h> // include processor files - each processor file is guarded.

void lcdInit(){
    msDelay(15);           /*15ms,16x2 LCD Power on delay*/
   	TRISD = 0x00;          /*Set PORTD as output PORT for LCD data(D0-D7) pins*/
    TRISE = 0x00;          /*Set PORTD as output PORT LCD Control(RS,EN) Pins*/
	lcdCommand(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    lcdCommand(0x0c);     /*display on cursor off*/
    lcdCommand(0x06);     /*increment cursor (shift cursor to right)*/
	lcdCommand(0x01);     /*clear display screen*/
}

void lcdClear(){
    lcdCommand(0x01);     /*clear display screen*/
}

void lcdStringXY(char pos, char row, const char *msg){
    char location=0;
    if(row<=1)
    {
        location=(0x80) | (pos & 0x0f);      /*Print message on 1st row and desired location*/
        lcdCommand(location);
    }
    else
    {
        location=(0xC0) | (pos & 0x0f);      /*Print message on 2nd row and desired location*/
        lcdCommand(location);    
    }  
    lcdString(msg);
}

void lcdCustomCharXY(char prmPos, char prmRow, char prmValue){
    if(prmRow<1)
        lcdCommand(0x80 | (prmPos & 0x0f));
    else
        lcdCommand(0xC0 | (prmPos & 0x0f));
    lcdChar(prmValue);
}

void lcdCommand(char cmd ){
	ldata= cmd;            /*Send data to PORT as a command for LCD*/   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	msDelay(3);	
}

void lcdChar(char dat){
	ldata= dat;            /*Send data to LCD*/  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	NOP();
	EN=0;
    msDelay(1);
}

void lcdString(const char *msg){
	while((*msg)!=0)
	{		
	  lcdChar(*msg);
	  msg++;	
    }	
}

void lcdDirCustomChar(unsigned char loc, unsigned char *msg){
    unsigned char i;
    if(loc<8)
    {
     lcdCommand(0x40+(loc*8));     /* Command 0x40 and onwards forces the device to point CGRAM address */
       for(i=0;i<8;i++)             /* Write 8 byte for generation of 1 character */
           lcdChar(msg[i]);
    }   
}
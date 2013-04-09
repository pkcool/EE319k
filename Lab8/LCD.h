#ifndef __LCD_H__
#define __LCD_H__
 
#define LCD_PIN_RS   0x00000010
#define LCD_PIN_E    0x00000020

typedef struct command
{
	unsigned char data;		// data
	unsigned char mode;		// 0 for 4-bit, 1 for 8-bit
	unsigned short time;	// microseconds
}command;

void LCDInit(void);
void LCDOutNibble(unsigned char packet);
void LCDOutByte(unsigned char packet);
void LCDCommandPacket(unsigned char packet);
void LCDDataPacket(unsigned int packet);
void LCDOutString(unsigned char str[]);
void LCDClear(void);
void LCDCursor(unsigned int location);
void LCDOutFix(unsigned int number);

#endif // __LCD_H__

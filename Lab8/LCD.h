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

extern void LCDInit(void);
extern void LCDOutNibble(unsigned char packet);
extern void LCDOutByte(unsigned char packet);
extern void LCDCommandPacket(unsigned char packet, unsigned char mode);
extern void LCDDataPacket(unsigned int packet);
extern void LCDOutString(unsigned char str[]);
extern void LCDClear(void);
extern void LCDCursor(unsigned int location);
extern void LCDOutFix(unsigned int number);

#endif // __LCD_H__
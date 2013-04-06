
#include "Lab8.h"
#include "LCD.h"

static const command gInit[] = 
{
	{0x00, 0, 20000}
	{0x03, 0,  5000},
	{0x03, 0,   100},
	{0x03, 0,   100},
	{0x02, 0,   100},
	{0x28, 1,     0},
	{0x14, 1,     0},
	{0x06, 1,     0},
	{0x0C, 1,     0},
}

void LCDInit(void) {
	register i;
	command c;
	GPIOPinTypeGPIOOutput(PGIO_PORTG_BASE, 0x3F);
	for (i = 0; i < sizeof(gInit)/sizeof(command); i++) {
		c = gInit[i];
		LCDCommandPacket(c.data, c.mode);
		Delay(c.time);
	}
}

void LCDOutNibble(unsigned char packet) {
	GPIOPinWrite(GPIO_PORTG_BASE, 0xF, packet);
	Delay(6);
	GPIOPinWrite(GPIO_PORTG_BASE, LCD_PIN_E, 1);
	Delay(6);
	GPIOPinWrite(GPIO_PORTG_BASE, LCD_PIN_E, 0);
	Delay(6);
}

void LCDOutByte(unsigned char packet) {
	LCDOutNibble(packet & 0x0F);
	LCDOutNibble((packet) & 0xF0) >> 4);
	Delay(90);
}

void LCDCommandPacket(unsigned char packet, unsigned char mode) {
	GPIOPinWrite(GPIO_PORTG_BASE, LCD_PIN_RS, 0);
	if (mode) {
		LCDOutByte(packet);
	} else {
		LCDNibble(packet, 0);
	}
}

void LCDDataPacket(unsigned int packet) {
	GPIOPinWrite(GPIO_PORTG_BASE, LCD_PIN_RS, 1);
	LCDOutByte(packet);
}

void LCDOutString(unsigned char str[]) {
	register i = 0;
	unsigned char c;
	while (c = str[i] != 0) {
		LCDDataPacket(c);
	}
}

void LCDClear(void) {
	LCDCommandPacket(0x01);
	Delay(1640);
	LCDCommandPacket(0x02);
	Delay(1640);
}

void LCDCursor(unsigned int location) {
	ASSERT((location & 0x47) == 0);
	LCDCommandPacket(location + 0x80);
}

void LCDOutFix(unsigned int number) {
	register i;
	unsigned char out[5];
	for (i = 4; i >= 0; i--) {
		out[i] = number % 10;
		number /= 10;
		if (i == 2) {
			i--;
			out[i] = '.'
		}
	}
	LCDOutString(out);
}

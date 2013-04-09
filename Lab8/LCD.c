
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/lm3s1968.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "Lab8.h"
#include "LCD.h"
#include "globals.h"

static const command gInit[8] = 
{
	{0x03, 0,  500},
	{0x03, 0,   10},
	{0x03, 0,   10},
	{0x02, 0,   10},
	{0x28, 1,     0},
	{0x14, 1,     0},
	{0x06, 1,     0},
	{0x0C, 1,     0},
};

void LCDInit(void) { int nop;
	register char i;
	command c;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	nop = 0;
	nop += 1;
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x3F);
	Delay(2000);
	for (i = 0; i < 8; i++) {
		c = gInit[i];
		if (c.mode == 0) {
			GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_RS, 0);
			LCDOutNibble(c.data);
		} else {
			LCDCommandPacket(c.data);
		}
		Delay(c.time);
	}
}

void LCDOutNibble(unsigned char packet) {
	GPIOPinWrite(GPIO_PORTF_BASE, 0xF, packet);
	Delay(1);
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_E, LCD_PIN_E);
	Delay(1);
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_E, 0);
	Delay(1);
}

void LCDOutByte(unsigned char packet) {
	LCDOutNibble(packet & 0x0F);
	LCDOutNibble((packet & 0xF0) >> 4);
	Delay(9);
}

void LCDCommandPacket(unsigned char packet) {
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_RS, 0);
	LCDOutByte(packet);
}

void LCDDataPacket(unsigned int packet) {
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_RS, LCD_PIN_RS);
	LCDOutByte(packet);
}

void LCDOutString(unsigned char str[]) {
	register char i = 0;
	unsigned char c;
	while (c != 0) {
		c = str[i++];
		LCDDataPacket(c);
	}
}

void LCDClear(void) {
	LCDCommandPacket(0x01);
	Delay(164);
	LCDCommandPacket(0x02);
	Delay(164);
}

void LCDCursor(unsigned int location) {
	if ((location & 0x47) == 0) {
		LCDCommandPacket(location + 0x80);
	}
}

void LCDOutFix(unsigned int number) {
	register char i;
	unsigned char out[5];
	for (i = 4; i >= 0; i--) {
		out[i] = '0' + number % 10;
		number /= 10;
		if (i == 2) {
			i--;
			out[i] = '.';
		}
	}
	LCDOutString(out);
}


#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "Lab8.h"
#include "LCD.h"

static const command gInit[] = 
{
	{0x00, 0, 20000},
	{0x03, 0,  5000},
	{0x03, 0,   100},
	{0x03, 0,   100},
	{0x02, 0,   100},
	{0x28, 1,     0},
	{0x14, 1,     0},
	{0x06, 1,     0},
	{0x0C, 1,     0},
};

void LCDInit(void) {
	register char i;
	command c;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x3F);
	for (i = 0; i < sizeof(gInit)/sizeof(command); i++) {
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
	Delay(6);
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_E, LCD_PIN_E);
	Delay(6);
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_PIN_E, 0);
	Delay(6);
}

void LCDOutByte(unsigned char packet) {
	LCDOutNibble(packet & 0x0F);
	LCDOutNibble((packet & 0xF0) >> 4);
	Delay(90);
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
	Delay(1640);
	LCDCommandPacket(0x02);
	Delay(1640);
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

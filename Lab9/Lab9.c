
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"

#include "driverlib/systick.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "Lab9.h"
#include "ADCDriver.h"
#include "globals.h"
#include "SysTick.h"
#include "ADC.h"
#include "PLL.h"

unsigned long gFlags;
unsigned long gSystemClockFrequency;
unsigned long Data;
char msg[6] = "      ";

unsigned long min = 88;
unsigned long max = 1022;

int main(void){
	PLL_Init();
	LCD_Open();
	LCD_Clear();
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	SysTickInit(2000000);
	while(1) {
		// wait for mailbox flag ADCStatus to be true
		while (HWREGBITW(&gFlags, FLAG_ADC_VALUE) == 0) { }
		// read the 10-bit ADC sample from the mailbox ADCMail
		Data = ADCvalue;
		// clear the mailbox flag ADCStatus to signify the mailbox is now empty
		HWREGBITW(&gFlags, FLAG_ADC_VALUE) = 0;
		// convert the sample into a fixed point number
		Convert(Data);
		// output the fixed point number on the LCD with units
		LCD_GoTo(0);
		LCD_OutString(msg);
		LCD_OutString("cm");
	}
}

//Converts raw data taken in by the ADC into a centimeter value
void Convert(int Data){
	register char i;
	int ConvertedData;
		
	if ((GPIO_PORTG_DATA_R & 0x10) == 0) {
		min = Data;
	}
	if ((GPIO_PORTG_DATA_R & 0x08) == 0) {
		max = Data;
	}
	Data = (Data - min);
	if (Data < 0) {
		Data = 0;
	}
	ConvertedData = Data*LENGTH/(max-min);
	msg[5] = ' ';
	for (i = 4; i >= 0; i--) {
		msg[i] = '0' + ConvertedData % 10;
		ConvertedData /= 10;
		if (i == 2) {
			i--;
			msg[i] = '.';
		}
	}
}

void Delay(unsigned long count) {
	count = (count * 50) >> 2;
	while(count--) { }
}

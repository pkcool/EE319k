
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"

#include "driverlib/systick.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include <stdio.h>

#include "Lab9.h"
#include "ADCDriver.h"
#include "globals.h"
#include "SysTick.h"
#include "ADC.h"
#include "PLL.h"
#include "Output.h"
#include "UART.h"

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
	Output_Init();
	Output_Color(5);

	JobSelect();
	
	if (HWREGBITW(&gFlags, FLAG_JOB) == 1) {
		Transmitter();
	} else {
		Receiver();
	}
}

void Transmitter(void) {
	UART_Init();	
	while(1) {
		// pass
	}
}

void Receiver(void) {
	UART_Init();
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

void JobSelect(void) {
	HWREGBITW(&gFlags, FLAG_SELECT) = 0;
	while (HWREGBITW(&gFlags, FLAG_SELECT) == 0) {
		if (((GPIO_PORTG_DATA_R & 0x20) == 0) && (HWREGBITW(&gFlags, FLAG_JOB) == 0)) {
			HWREGBITW(&gFlags, FLAG_JOB) = 1;
			printf("Transmitter (y/n)%c", NEWLINE);
		}
		if (((GPIO_PORTG_DATA_R & 0x40) == 0) && (HWREGBITW(&gFlags, FLAG_JOB) == 1)) {
			HWREGBITW(&gFlags, FLAG_JOB) = 0;
			printf("Receiver (y/n)%c", NEWLINE);
		}
		if ((GPIO_PORTG_DATA_R & 0x80) == 0) {
			HWREGBITW(&gFlags, FLAG_SELECT) = 1;
			printf("Selection confirmed%c", NEWLINE);
		}
	}
}

//Converts raw data taken in by the ADC into a centimeter value
void Convert(int Data){
	register char i;
	int ConvertedData;

	if ((GPIO_PORTG_DATA_R & 0x08) == 0) {
		max = Data;
	}
	if ((GPIO_PORTG_DATA_R & 0x10) == 0) {
		min = Data;
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

void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}

void Delay(unsigned long count) {
	count = (count * 50) >> 2;
	while(count--) { }
}

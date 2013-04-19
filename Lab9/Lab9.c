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
#include "FIFO.h"

unsigned long gFlags;
unsigned long gErrors;
unsigned long Data;
char msg[8];

unsigned long min = 88;
unsigned long max = 1022;

int main(void){
	PLL_Init();
	SysTickInit(2000000);
	Output_Init();
	Output_Color(15);
	
	JobSelect();
	
	if (HWREGBITW(&gFlags, FLAG_JOB) == 1) {
		Transmitter();
	} else {
		Receiver();
	}
}

void Transmitter(void) {
	ADC_InitSWTriggerSeq3(2);
	UART_Init();
	SysTickIntEnable();
	while(1) {
		// pass
	}
}

char FIFO_data[8];
char *FIFO_raw;
char FIFO_temp = 0;
char FIFO_byte = 0;
char FIFO_input = 0;
char j; 

void Receiver(void) {
	char output[6] = "      ";
	(FIFO_raw) = &FIFO_temp;
  Fifo_Init(); 
	LCD_Open();
	LCD_Clear();
	UART_Init();
	UART_IntEnable();
		//ADC_InitSWTriggerSeq3(2);
		//SysTickIntEnable();
	EnableInterrupts();
	while(1) {
		while(Fifo_Get(FIFO_raw) == 0) {}
		FIFO_data[FIFO_byte] = *FIFO_raw;
		if ((*FIFO_raw) == 2) {
			FIFO_input = 1;
		} else if ((*FIFO_raw) == 3) { 							// If stop codon...
			FIFO_input = 0;														// Switch off reading mode
			FIFO_byte = 0;														// Return pointer to start of array
			for (j = 1; j < 7; j++) {
				output[j-1] = FIFO_data[j];
			}
			//printf(output);
			//printf("%c",NEWLINE);
			LCD_GoTo(0);
			LCD_OutString(output);
			LCD_OutString("cm");
		}
		if (FIFO_input == 1) {
			FIFO_byte++;
		}
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
	for (i = 5; i >= 1; i--) {
		msg[i] = '0' + ConvertedData % 10;
		ConvertedData /= 10;
		if (i == 3) {
			i--;
			msg[i] = '.';
		}
	}
	msg[0] = 0x2;
	msg[6] = ' ';
	msg[7] = 0x3;
}

void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}

void Delay(unsigned long count) {
	count = (count * 50) >> 2;
	while(count--) { }
}


#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "Lab8.h"
#include "LCD.h"
#include "ADCDriver.h"
#include "globals.h"
#include "SysTick.h"
#include "ADC.h"

unsigned long gFlags;
unsigned long gSystemClockFrequency;
unsigned long Data;
char msg[6] = "      ";

unsigned long min = 88;
unsigned long max = 1022;

//Tests for ADC to ensure it is inputting data properly
int main1(void) { 
	init();
	ADC_InitSWTriggerSeq3(2);
	SysTickInit();
	while(1) {
		Data = ADC_In();
	}
}

//Tests the LCD to see if it is outputting properly
unsigned long Data;
#define N 256
int main2(void){
	int i;
	unsigned long sum;
	init(); // Bus clock is 50 MHz
	LCDInit(); 
	LCDClear();
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	SysTickInit();
	while(1){
		sum = 0;
		for(i=0; i<N; i++){ // take N samples and perform the average
			sum = sum+ADC_In(); // sample 10-bit channel 2
		}
		Data = sum/N; // noise reducing filter
		LCDCursor(0);
		LCDOutFix(Data);
		LCDOutString(" cm");
	}
}


//Tests to see if all steps to output to LCD work 
unsigned long Data; // 10-bit ADC 
unsigned long Position; // 16-bit fixed-point 0.001 cm 
#define N 256 
int main3(void){ 
	int i;
	unsigned long sum;
	init(); // Bus clock is 50 MHz 
	LCDInit(); 
	LCDClear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	SysTickInit();
	while(1){
		sum = 0;
		for(i=0; i<N; i++){ // take N samples and perform the average 
			sum = sum+ADC_In(); // sample 10-bit channel 2 
		} 
		Data = sum/N; // noise reducing filter 
		Convert(Data); // you write this function 
		LCDCursor(0);
		LCDOutString(msg);
		LCDOutString("cm");
	}
}

int main(void){
	init(); // Bus clock is 50 MHz 
	LCDInit();
	LCDClear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	SysTickInit();
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
		LCDCursor(0);
		LCDOutString(msg);
		LCDOutString("cm");
	}
}

//Converts raw data taken in by the ADC into a centimeter value
void Convert(int Data){
	register char i;
	int ConvertedData;
	if (GPIOPinRead(GPIO_PORTG_BASE, GPIO_PIN_4) == 0) {
		min = Data;
	}
	if (GPIOPinRead(GPIO_PORTG_BASE, GPIO_PIN_3) == 0) {
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

void init(void) { int nop;
	gSystemClockFrequency = SysCtlClockGet();

	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	nop = 0;
	nop += 1;
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
						(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
					(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
					GPIO_STRENGTH_2MA,
					GPIO_PIN_TYPE_STD_WPU);
}

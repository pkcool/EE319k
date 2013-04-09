
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "Lab8.h"
#include "LCD.h"
#include "ADCDriver.h"
#include "globals.h"

#include "ADC.h"

unsigned long gFlags;
unsigned long gSystemClockFrequency;
unsigned long Data;

//Tests for ADC to ensure it is inputting data properly
int main1(void) { 
	init();
	ADC_InitSWTriggerSeq3(2);
	while(1) {
		Data = ADC_In();
	}
}

int main_Anthony(void) {
	unsigned char welcome[] = "Welcome to 319k!";
	init();
	LCDInit();
	ADC_Init();
	while (1) {
		if (HWREGBITW(&gFlags, FLAG_ADC_VALUE)) {
				HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 0;
				LCDClear();
				LCDCursor(0);
				LCDOutFix(ADCvalue);
		}
	}
}

//Tests the LCD to see if it is outputting properly
unsigned long Data; 
#define N 256 
int main2(void){ 
	int i; unsigned long sum; 
	init(); // Bus clock is 50 MHz 
	LCDInit(); 
	LCDClear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	while(1){ 
		sum = 0; 
		for(i=0; i<N; i++){ // take N samples and perform the average 
			sum = sum+ADC_In(); // sample 10-bit channel 2 
		} 
		Data = sum/N; // noise reducing filter 
//		LCD_GoTo(0); 
		LCDOutFix(Data); 
		LCDOutString(" cm");
	}
}

//Converts raw data taken in by the ADC into a centimeter value
int Convert(int Data){
	int ConvertedData = Data/340.0; //NEEDS PROPER EQUATION
	return ConvertedData;
}

//Tests to see if all steps to output to LCD work 
unsigned long Data; // 10-bit ADC 
unsigned long Position; // 16-bit fixed-point 0.001 cm 
#define N 256 
int main3(void){ 
	int i; unsigned long sum; 
	init(); // Bus clock is 50 MHz 
	LCDInit(); 
	LCDClear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	while(1){ 
		sum = 0; 
		for(i=0; i<N; i++){ // take N samples and perform the average 
			sum = sum+ADC_In(); // sample 10-bit channel 2 
		} 
		Data = sum/N; // noise reducing filter 
		Position = Convert(Data); // you write this function 
//		LCD_GoTo(0); 
		LCDOutFix(Position); 
	}
}

int main(void){
	init(); // Bus clock is 50 MHz 
	LCDInit(); 
	LCDClear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	SysTickIntEnable();
	while(1) {
														// wait for mailbox flag ADCStatus to be true
		
														// read the 10-bit ADC sample from the mailbox ADCMail
		
														// clear the mailbox flag ADCStatus to signify the mailbox is now empty
		
														// convert the sample into a fixed point number
		
														// output the fixed point number on the LCD with units
	}
}	

void SysTickIntHandler(void) {
	HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 1;
}

void Delay(unsigned long count) {
    while(count--) {
        while(!HWREGBITW(&gFlags, FLAG_CLOCK_TICK)) { }
        HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 0;
    }
}

unsigned long periodToSysTick(unsigned long period) {
	// 0.75 * 50Mhz * period
	return ((3 * gSystemClockFrequency) >> 2) * period;
}

void init(void) { int nop;
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

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

	SysTickPeriodSet( 50 );
	SysTickIntEnable();
	SysTickEnable();
}

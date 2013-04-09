
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

int main1(void) {
	init();
	LCDInit();
	ADC_Init();

	while(1) {
		// pass
	}
}

int main2(void) {
	init();
	ADC_InitSWTriggerSeq3(2);
	
	while(1) {
		Data = ADC_In();
	}
}

int main(void) {
	unsigned char welcome[] = "Welcome to 319k!";
	init();
	LCDInit();
	Delay(1000);
	LCDOutString(welcome);
	while (1) {
		// pass
	}
}

int main3(void) {
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

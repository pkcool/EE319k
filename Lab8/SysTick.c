
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "globals.h"
#include "ADCDriver.h"
#include "SysTick.h"

#define N 512
#define M 9
void SysTickIntHandler(void) {
	register int i;
	long sum = 0;
	for(i = 0; i < N; i++){ // take N samples and perform the average 
		sum = sum+ADC_In(); // sample 10-bit channel 2 
	}
	ADCvalue = sum >> M; // noise reducing filter 
	HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 1;
	HWREGBITW(&gFlags, FLAG_ADC_VALUE) = 1;
	GPIO_PORTG_DATA_R ^= 0x40;
}

void SysTickInit(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	SysTickPeriodSet( 2000000 );
	SysTickIntEnable();
	SysTickEnable();
}

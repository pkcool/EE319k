
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "SysTick.h"

void SysTickIntHandler(void) {
//	ADCvalue = ADC_In();
//	HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 1;
//	HWREGBITW(&gFlags, FLAG_ADC_VALUE) = 1;
//	GPIO_PORTG_DATA_R ^= 0x40;
}

void SysTickInit(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	SysTickPeriodSet( 2000000 );
	SysTickIntEnable();
	SysTickEnable();
}

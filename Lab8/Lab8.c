
#include "inc/sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

unsigned long gSystemClock;

void
SysTickIntHandler(void) {
	HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 1;
}

static void
Delay(unsigned long count) {
    while(count--) {
        while(!HWREGBITW(&gFlags, FLAG_CLOCK_TICK)) { }
        HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 0;
    }
}

void init(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	gSystemClock = SysCtlClockGet();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
						(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
					(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
					GPIO_STRENGTH_2MA,
					GPIO_PIN_TYPE_STD_WPU);

	SysTickPeriodSet(gSystemClock / CLOCK_RATE);
	SysTickIntEnable();
	SysTickEnable();
}

int main(void) {
    init();

}
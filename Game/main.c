
#include <stdio.h>
#include <time.h>

#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "SysTick.h"
#include "PLL.h"
#include "ADCDriver.h"

#include "globals.h"
#include "random.h"
#include "maze.h"

__asm void
Delay(unsigned long ulCount){
	subs    r0, #1
	bne     Delay
	bx      lr
}

int main(void) {
	PLL_Init();
	SysTick_Init(1000000);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
						(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
					(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
					GPIO_STRENGTH_2MA,
					GPIO_PIN_TYPE_STD_WPU);

	ADC_Init(2);
	RIT128x96x4Init(3500000);
	SysTick_IntEnable();
	while (1) {
		while ((GPIO_PORTG_DATA_R & 0x80) != 0) { }
		//while ((GPIO_PORTG_DATA_R & 0x80) == 0) { }
		RandomInit(NVIC_ST_CURRENT_R);
		RandomGenerate();
		MazeInit();		
		MazePrint();
	}
}

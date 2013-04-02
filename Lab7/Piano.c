#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "SysTickInts.h"
#include "lm3s1968.h"
#include "DAC.h"

void Piano_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	
	GPIO_PORTG_DIR_R = 0x00;
	GPIO_PORTF_DEN_R |= 0x0F;
	GPIO_PORTF_AFSEL_R |= 0x00;
}

void Piano_In (void) {
	Sound_Play(GPIO_PORTG_DATA_R);
}
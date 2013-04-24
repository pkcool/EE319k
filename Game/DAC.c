
#include <lm3s1968.h>
#include "globals.h"
#include "dac.h"

void DACInit(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	NOP();
	GPIO_PORTF_DIR_R |= 0x0F;
	GPIO_PORTF_DEN_R |= 0x0F;
	GPIO_PORTF_AFSEL_R |= 0x00;
}

void DACOut(unsigned long packet) {
	packet &= 0x0F;
	GPIO_PORTF_DATA_R = packet;
}

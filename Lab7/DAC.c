
#include <lm3s1968.h>

void DAC_Init(void) { int nop;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	nop = 0;
	nop = nop + 1;
	GPIO_PORTF_DIR_R |= 0x0F;
	GPIO_PORTF_DEN_R |= 0x0F;
	GPIO_PORTF_AFSEL_R |= 0x00;
}

void DAC_Out(unsigned long packet) {
	packet &= 0x0F;
	GPIO_PORTF_DATA_R = packet;
}


#include <lm3s1968.h>

void DAC_Init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	
	GPIO_PORTF_DIR_R |= 0x0F;
	GPIO_PORTF_DEN_R |= 0x0F;
	GPIO_PORTF_AFSEL_R |= 0x00;
}

void DAC_Out(unsigned long packet) {
	GPIO_PORTF_DATA_R &= 0xF0;
	packet &= 0x0F;
	GPIO_PORTF_DATA_R |= packet;
}


#include "inc/hw_types.h"
#include "inc/lm3s1968.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "globals.h"
#include "ADCDriver.h"
#include "SysTick.h"

#define N 256
#define M 8
void SysTickIntHandler(void) {
	int i;
	long sum = 0;
	for(i = 0; i < N; i++){ // take N samples and perform the average 
		sum = sum+ADC_In(); // sample 10-bit channel 2 
	}
	ADCvalue = sum >> M; // noise reducing filter 
	HWREGBITW(&gFlags, FLAG_CLOCK_TICK) = 1;
	HWREGBITW(&gFlags, FLAG_ADC_VALUE) = 1;
	GPIO_PORTG_DATA_R ^= 0x04;
}

void SysTickInit(unsigned long period) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG; // activate port G
	NOP();
	GPIO_PORTG_DIR_R |= 0x04;							// make PG2 out
	GPIO_PORTG_DIR_R &= ~0xF8;							// make PG3-7 in
  GPIO_PORTG_DEN_R |= 0xFF;							// enable digital I/O on PG2
	GPIO_PORTG_PUR_R |= 0xF8;

	NVIC_ST_CTRL_R = 0;										// disable SysTick during setup
  NVIC_ST_RELOAD_R = period - 1;				// maximum reload value
  NVIC_ST_CURRENT_R = 0;								// any write to current clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
}

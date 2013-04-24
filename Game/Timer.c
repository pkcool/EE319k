
#include "inc/lm3s1968.h"

#include "timer.h"

void (*Timer0ATask)(void);

void Timer0AInit(void(*task)(void), unsigned short period) {
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;							// 0) activate timer0
	Timer0ATask = task;																	// user function 
  TIMER0_CTL_R &= ~0x00000001;												// 1) disable timer0A during setup
  TIMER0_CFG_R = 0x00000004;													// 2) configure for 16-bit timer mode
  TIMER0_TAMR_R = 0x00000002;													// 3) configure for periodic mode
  TIMER0_TAILR_R = period;														// 4) reload value
  TIMER0_TAPR_R = 49;																	// 5) 1us timer0A
  TIMER0_ICR_R = 0x00000001;													// 6) clear timer0A timeout flag
  TIMER0_IMR_R |= 0x00000001;													// 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000;	// 8) priority 2
  NVIC_EN0_R |= NVIC_EN0_INT19;												// 9) enable interrupt 19 in NVIC
  TIMER0_CTL_R |= 0x00000001;													// 10) enable timer0A
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout
  (*Timer0ATask)();                // execute user task
}

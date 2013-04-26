
#include "inc/lm3s1968.h"

#include "timer.h"

void (*Timer0ATask)(void);
void (*Timer1ATask)(void);

void Timer0AInit(void(*task)(void), unsigned short period) {
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;							// 0) activate timer0
	Timer0ATask = task;																	// user function 
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN;										// 1) disable timer0A during setup
  TIMER0_CFG_R = 0x00000004;													// 2) configure for 16-bit timer mode
  TIMER0_TAMR_R = 0x00000002;													// 3) configure for periodic mode
  TIMER0_TAILR_R = period - 1;												// 4) reload value
  TIMER0_TAPR_R = 49;																	// 5) 1us timer0A
  TIMER0_ICR_R = 0x00000001;													// 6) clear timer0A timeout flag
  TIMER0_IMR_R |= 0x00000001;													// 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x00000000;	// 8) priority 0
  NVIC_EN0_R |= NVIC_EN0_INT19;												// 9) enable interrupt 19 in NVIC
  TIMER0_CTL_R |= TIMER_CTL_TAEN;											// 10) enable timer0A
}

void Timer1AInit(void(*task)(void), unsigned short period) {
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER1;							// 0) activate timer0
	Timer1ATask = task;																	// user function 
  TIMER1_CTL_R &= ~TIMER_CTL_TAEN;										// 1) disable timer1A during setup
  TIMER1_CFG_R = 0x00000004;													// 2) configure for 16-bit timer mode
  TIMER1_TAMR_R = 0x00000002;													// 3) configure for periodic mode
  TIMER1_TAILR_R = period - 1;												// 4) reload value
  TIMER1_TAPR_R = 49;																	// 5) 1us timer1A
  TIMER1_ICR_R = 0x00000001;													// 6) clear timer0A timeout flag
  TIMER1_IMR_R |= 0x00000001;													// 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI5_R&0xFFFFFF00)|0x00000040;	// 8) priority 2
  NVIC_EN0_R |= NVIC_EN0_INT21;												// 9) enable interrupt 19 in NVIC
  TIMER1_CTL_R |= TIMER_CTL_TAEN;											// 10) enable timer1A
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;		// acknowledge timer0A timeout
  (*Timer0ATask)();                			// execute user task
}

void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;		// acknowledge timer1A timeout
  (*Timer1ATask)();                			// execute user task
}

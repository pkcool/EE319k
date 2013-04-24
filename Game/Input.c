
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"

#include "input.h"
#include "globals.h"

void InputInit(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
  NOP();
  GPIO_PORTG_DIR_R &= ~0x80;// make PG3-7 in (PC3-7 button)
  GPIO_PORTG_DEN_R |= 0x80; // enable digital I/O on PC7
  GPIO_PORTG_IS_R &= ~0x80; // PC7 is edge-sensitive (default setting)
  GPIO_PORTG_IBE_R &= ~0x80;// PC7 is not both edges (default setting)
  GPIO_PORTG_IEV_R |= 0x80; // PC7 rising edge event
  GPIO_PORTG_ICR_R = 0x80;  // clear flag7
  GPIO_PORTG_IM_R |= 0x80;  // enable interrupt on PC7
	NVIC_PRI7_R = (NVIC_PRI7_R&0x00FFFFFF)|0x20000000; // bits 29-31
  NVIC_EN0_R |= NVIC_EN0_INT31;
  EnableInterrupts();
}

void GPIOPortG_Handler(void){
	HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 1;
  GPIO_PORTG_ICR_R = 0x80;  // acknowledge flag7
}

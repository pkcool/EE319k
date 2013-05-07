
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"

#include "input.h"
#include "globals.h"

void InputInit(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
  NOP();	
  GPIO_PORTD_DIR_R &= ~0x0F;// make PG3-7 in (PC3-7 button)
  GPIO_PORTD_DEN_R |= 0x0F; // enable digital I/O on PC7
	GPIO_PORTD_PDR_R |= 0x0F; // enable digital I/O on PC7
  GPIO_PORTD_IS_R &= ~0x0F; // PC7 is edge-sensitive (default setting)
  GPIO_PORTD_IBE_R |= 0x0F;// PC7 is not both edges (default setting)
  //GPIO_PORTD_IEV_R |= 0x0F; // PC7 rising edge event
  GPIO_PORTD_ICR_R = 0x0F;  // clear flag7
  GPIO_PORTD_IM_R |= 0x0F;  // enable interrupt on PC7
	NVIC_PRI0_R = (NVIC_PRI0_R&0x0FFFFFFF)|0x20000000; // bits 29-31
  NVIC_EN0_R |= NVIC_EN0_INT3;
	
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
  NOP();
  GPIO_PORTG_DIR_R &= ~0xF8;// make PG3-7 in (PC3-7 button)
  GPIO_PORTG_DEN_R |= 0xF8; // enable digital I/O on PC7
  GPIO_PORTG_IS_R &= ~0xF8; // PC7 is edge-sensitive (default setting)
  GPIO_PORTG_IBE_R &= ~0xF8;// PC7 is not both edges (default setting)
  GPIO_PORTG_IEV_R |= ~0xF8; // PC7 falling edge event
  GPIO_PORTG_ICR_R = 0xF8;  // clear flag7
  GPIO_PORTG_IM_R |= 0xF8;  // enable interrupt on PC7
	NVIC_PRI7_R = (NVIC_PRI7_R&0x00FFFFFF)|0x20000000; // bits 29-31
  NVIC_EN0_R |= NVIC_EN0_INT31;
}

void GPIOPortG_Handler(void) {
	/*
	if ((GPIO_PORTG_MIS_R & 0x08)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_UP) = 1;
	}
	if ((GPIO_PORTG_MIS_R & 0x10)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_DOWN) = 1;
	}
	if ((GPIO_PORTG_MIS_R & 0x20)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_LEFT) = 1;
	}
	if ((GPIO_PORTG_MIS_R & 0x40)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_RIGHT) = 1;
	}
	*/
	if ((GPIO_PORTG_MIS_R & 0x80)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) ^= 1;
	}
  GPIO_PORTG_ICR_R = 0xF8;  // acknowledge flag7
}

void GPIOPortD_Handler(void) {
	if ((GPIO_PORTD_MIS_R & 0x01)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_UP) = 1;
	}
	if ((GPIO_PORTD_MIS_R & 0x02)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_DOWN) = 1;
	}
	if ((GPIO_PORTD_MIS_R & 0x04)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_LEFT) = 1;
	}
	if ((GPIO_PORTD_MIS_R & 0x08)) {
		HWREGBITW(&g_flags, FLAG_BUTTON_RIGHT) = 1;
	}
  GPIO_PORTD_ICR_R = 0x0F;  // acknowledge flag7
}

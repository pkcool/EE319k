
#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"
#include "globals.h"
#include "graphics.h"

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

void SysTick_Handler(void) {
	if (HWREGBITW(&g_flags, FLAG_BUFFER_READY) == 1) {
		GPIO_PORTG_DATA_R ^= 0x04;
		RIT128x96x4ImageDraw(g_frame, 0, 0, 128, 96);
		ClearScreen();
		HWREGBITW(&g_flags, FLAG_BUFFER_READY) = 0;
	}
}

void SysTick_IntEnable(void) {
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;
}

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(unsigned long period){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = period - 1;  			// set reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x02000000; // set priority 1
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}


#include <stdio.h>

#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "SysTick.h"
#include "PLL.h"
#include "ADCDriver.h"
#include "graphics.h"
#include "globals.h"
#include "random.h"
#include "game.h"

volatile unsigned long g_flags;

__asm void
Delay(unsigned long ulCount){
	subs    r0, #1
	bne     Delay
	bx      lr
}

int main(void) {
	int i,j;
	PLL_Init();
	SysTick_Init(1000000);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
						(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
					(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
					GPIO_STRENGTH_2MA,
					GPIO_PIN_TYPE_STD_WPU);

	ADC_Init(2);
	RIT128x96x4Init(3500000);
	SysTick_IntEnable();

	while ((GPIO_PORTG_DATA_R & 0x80) != 0) { }
	while ((GPIO_PORTG_DATA_R & 0x80) == 0) { }
	RandomInit(NVIC_ST_CURRENT_R);
	RandomGenerate();
	GameInit();
	j = 8;
	while (1) {
		ClearScreen();
		for (i = 0; i < MAX_ENEMIES; i++) {
			switch (g_enemies[i].stat) {
				case ALIVE:
					RotateImage(g_spriteIdle[g_enemies[i].animationStep], g_enemies[i].xpos, g_enemies[i].ypos, g_enemies[i].width, g_enemies[i].height, g_enemies[i].direction, j);
					break;
				case HIT:
					DrawImage(g_explosion[g_enemies[i].animationStep], g_enemies[i].xpos, g_enemies[i].ypos, 14, 14);
					g_enemies[i].animationStep++;
					if (g_enemies[i].animationStep >= MAX_EXPLOSION) {
						g_enemies[i].stat = DEAD;
					}
					break;
				case DEAD:
					break;
			}
			/*if (g_enemies[i].stat == ALIVE) {
				//if (g_enemies[i].direction == 0) {
				//	DrawImage(g_spriteIdle[g_enemies[i].danceStep], g_enemies[i].xpos, g_enemies[i].ypos, g_enemies[i].width, g_enemies[i].height);
				//} else {
					RotateImage(g_spriteIdle[g_enemies[i].animationStep], g_enemies[i].xpos, g_enemies[i].ypos, g_enemies[i].width, g_enemies[i].height, g_enemies[i].direction, j);
				//}
				//g_enemies[i].animationStep = (g_enemies[i].animationStep+1)%MAX_DANCE;
			}*/
			g_enemies[i].direction += 1;
			if (g_enemies[i].direction >= 6) {
				j=(j+1)%128;
			}
			if (g_enemies[i].direction >= 24) {
				g_enemies[i].direction = g_enemies[i].direction%24;
				//g_enemies[i].stat = HIT;
				//g_enemies[i].animationStep = 0;
			}
		}
		RIT128x96x4ImageDraw(g_frame, 0, 0, 128, 96);
	}
}

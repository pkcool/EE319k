
#include <stdio.h>

#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

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
#include "input.h"
#include "sound.h"
#include "timer.h"
#include "dac.h"

volatile unsigned long g_flags;

unsigned long sc;

__asm void
Delay(unsigned long ulCount){
	subs    r0, #1
	bne     Delay
	bx      lr
}

int main(void) {
	int i;
	unsigned char lives[1] = " ";
	PLL_Init();
	SysTick_Init(1000000/30);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
						(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
					(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
					GPIO_STRENGTH_2MA,
					GPIO_PIN_TYPE_STD_WPU);

	ADC_Init(2);
	InputInit();
	SoundInit();
	RIT128x96x4Init(3500000);
	SysTick_IntEnable();
	EnableInterrupts();
	
	while ((GPIO_PORTG_DATA_R & 0x80) != 0) { }
	while ((GPIO_PORTG_DATA_R & 0x80) == 0) { }
	RandomInit(NVIC_ST_CURRENT_R);
	RandomGenerate();
	GameInit();
	HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 0;
	while (1) {
		while (HWREGBITW(&g_flags, FLAG_BUFFER_READY) == 1) { }
		sc = StartCritical();
		for (i = 0; i < MAX_STARS; i++) {
			SetPixel(g_stars[i].xpos, g_stars[i].ypos, 2+(RandomExtract()%10));
		}
		for (i = 0; i < MAX_ENEMY_BULLETS; i++) {
			if (g_enemyBullets[i].stat == B_ALIVE) {
					DrawImageFast(g_bulletSprite, g_enemyBullets[i].xpos, g_enemyBullets[i].ypos, 2, 2);
			}
		}
		for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
			if (g_playerBullets[i].stat == B_ALIVE) {
					DrawImageFast(g_bulletSprite, g_playerBullets[i].xpos, g_playerBullets[i].ypos, 2, 2);
			}
		}
		for (i = 0; i < MAX_ENEMIES; i++) {
			switch (g_enemies[i].stat) {
				case E_ALIVE:
					DrawImageFast(g_enemySpritesIdle[1], g_enemies[i].xpos, g_enemies[i].ypos, g_enemies[i].width, g_enemies[i].height);
					break;
				case E_FIRE:
					if (g_enemies[i].animationStep/8 > MAX_DANCE) {
						DrawImageFast(g_enemySpritesIdle[g_enemies[i].animationStep/8], g_enemies[i].xpos, g_enemies[i].ypos, g_enemies[i].width, g_enemies[i].height);
						g_enemies[i].animationStep++;
					} else {
						g_enemies[i].animationStep = 0;
						g_enemies[i].stat = E_ALIVE;
					}
					break;
				case E_HIT:
					if (g_enemies[i].animationStep/4 < MAX_EXPLOSION) {
						DrawImageFast(g_explosionSprites[g_enemies[i].animationStep/4], g_enemies[i].xpos, g_enemies[i].ypos, 14, 14);
						g_enemies[i].animationStep++;
					} else {
						g_enemies[i].stat = E_DEAD;
					}
					break;
				case E_DEAD:
					break;
			}
		}
		switch (g_player.stat) {
			case P_ALIVE:
				DrawImageFast(g_playerSprites[g_player.shield], g_player.xpos, g_player.ypos, g_player.width, g_player.height);
				lives[0] = g_player.health%10+'0';
				DrawString(lives, 2, 2);
				break;
			case P_HIT:
				if (g_player.animationStep/4 < MAX_EXPLOSION) {
					DrawImageFast(g_playerExplosionSprites[g_player.animationStep/4], g_player.xpos - g_player.width/2 - 26/27, g_player.ypos + g_player.height/2 - 28/2, 26, 28);
					g_player.animationStep++;
				} else {
					g_player.stat = P_DEAD;
				}
				break;
			case P_DEAD:
				break;
		}
		HWREGBITW(&g_flags, FLAG_BUFFER_READY) = 1;
		EndCritical(sc);
	}
}

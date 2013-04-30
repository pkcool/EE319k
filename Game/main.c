
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

#include <math.h>

volatile unsigned long g_flags;

unsigned long sc;

__asm void
Delay(unsigned long ulCount){
	subs    r0, #1
	bne     Delay
	bx      lr
}

unsigned int abs(signed int a) {
		if (a < 0)
			return -a;
		return a;
}

void IntToString(unsigned int a, unsigned char *str, int length) {
	for (length-=1; length >= 0; length--) {
		str[length] = (a%10)+'0';
		a/=10;
	}
}

int main(void) {
	int i, j, k, l;
	char stary;
	unsigned char lives[2] = "  ";
	unsigned char level[2] = "  ";
	unsigned char score[5] = "     ";
	unsigned char randomString[21];
	PLL_Init();
	SysTick_Init(50000000/30);
	
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
	RIT128x96x4Init(5000000);
	SysTick_IntEnable();
	EnableInterrupts();
	
	j = 1024;
	k = 0;
	for (i = 0; i < 32; i++) {
		while (HWREGBITW(&g_flags, FLAG_ADC_VALUE) == 0) { }
		l = ADCValue;
		if (l < j)
			j = l;
		if (l > k)
			k = l;
		ADC_MID += l;
		HWREGBITW(&g_flags, FLAG_ADC_VALUE) = 0;
	}
	ADC_MID /= 32;
	ADC_DEV = k-j;
	
	while (HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) == 0) { }
	HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 0;
	RandomInit(NVIC_ST_CURRENT_R);
	RandomGenerate();
	GameInit();
	while (1) {
		while (HWREGBITW(&g_flags, FLAG_BUFFER_READY) == 1) { }
		sc = StartCritical();
		for (i = 0; i < MAX_STARS; i++) {
			stary = 0;
			for (j = RandomExtract()%10; j > 0; j--) {
				if (g_stars[i].ypos - stary >= 0) {
					SetPixel(g_stars[i].xpos, g_stars[i].ypos - stary, 2+j);
				}
				if (g_levelTimer == 0) { j = 1; }
				stary++;
			}
		}
		for (i = 0; i < MAX_ENEMY_BULLETS; i++) {
			if (g_enemyBullets[i].stat == B_ALIVE) {
					DrawImageFast(g_bulletSprite, g_enemyBullets[i].xpos, g_enemyBullets[i].ypos, 2, 2);
			}
		}
		for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
			if (g_playerBullets[i].stat == B_ALIVE) {
					DrawImageFast(g_playerBulletSprite, g_playerBullets[i].xpos, g_playerBullets[i].ypos, 2, 2);
			}
		}
		for (i = 0; i < MAX_ENEMIES; i++) {
			switch (g_enemies[i].stat) {
				case E_ALIVE:
					DrawImageFast(g_enemySpritesIdle[1], g_enemies[i].xpos, g_enemies[i].ypos, ENEMY_BOX, ENEMY_BOX);
					break;
				case E_FIRE:
					if (g_enemies[i].animationStep/8 < MAX_DANCE) {
						DrawImageFast(g_enemySpritesIdle[g_enemies[i].animationStep/8], g_enemies[i].xpos, g_enemies[i].ypos, ENEMY_BOX, ENEMY_BOX);
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
						g_enemies[i].animationStep = 0;
						g_enemies[i].stat = E_DEAD;
					}
					break;
				case E_DEAD:
					break;
			}
		}
		IntToString(g_player.health, lives,2);
		IntToString(g_player.score, score,5);
		IntToString(g_level, level, 2);
		DrawString(lives, 0, 0);
		DrawString(score, 128-5*6, 0);
		DrawString(level, 128/2-2*6, 0);
		if (g_levelTimer != 0) {
			if (g_levelTimer < 450 && g_levelTimer > 300) {
				for (i = 0; i < 21; i++) {
					if (randomString[i] != g_Stringz[g_level][i]) {
						if (RandomExtract()%32 == 1) {
							randomString[i] = g_Stringz[g_level][i];
						} else {
							randomString[i] = (RandomExtract()%96)+' ';
						}
					}
				}
				DrawString(randomString, 128/2-21*3, 96/2);
			} else if (g_levelTimer > 50 && g_levelTimer < 400) {
				DrawString(g_Stringz[g_level], 128/2-21*3, 96/2);
			}
		}
		switch (g_player.stat) {
			case P_ALIVE:
				DrawImageFast(g_playerSprites[g_player.shield], g_player.xpos, g_player.ypos, PLAYER_BOX, PLAYER_BOX);
				break;
			case P_HIT:
				if (g_player.health == 0) {
					if (g_player.animationStep/4 < MAX_EXPLOSION) {
						DrawImageFast(g_playerExplosionSprites[g_player.animationStep/4], g_player.xpos - PLAYER_BOX/2 - 26/2, g_player.ypos + PLAYER_BOX/2 - 28/2, 26, 28);
						g_player.animationStep++;
					} else {
						g_player.animationStep = 0;
						g_player.stat = P_DEAD;
					}
				} else {
					if (g_player.animationStep/4 < MAX_EXPLOSION) {
						DrawImageFast(g_playerSprites[g_player.shield], g_player.xpos, g_player.ypos, PLAYER_BOX, PLAYER_BOX);
						RotateImage(g_explosionSprites[g_player.animationStep/4], g_player.xpos - 2, g_player.ypos - 4, 14, 14, 0, 6);
						g_player.animationStep++;
					} else {
						g_player.animationStep = 0;
						g_player.stat = P_ALIVE;
					}
				}
				break;
			case P_DEAD:
				DimScreen();
				DrawString("Game Over",128/2-9*3,96/2);
				if (HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) == 1) {
					GameInit();
					HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 0;
				}
				break;
		}
		if (g_level == 5 && g_continue == 0) {
			DimScreen();
			DrawString("  You're a monster.  ", 128/2-21*3, 96/2-12);
			DrawString("  Continue anyway?   ", 128/2-21*3, 96/2);
		}
		HWREGBITW(&g_flags, FLAG_BUFFER_READY) = 1;
		EndCritical(sc);
	}
}

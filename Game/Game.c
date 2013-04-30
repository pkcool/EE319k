#include "inc/lm3s1968.h"
#include "inc/hw_types.h"

#include "sound.h"
#include "game.h"
#include "random.h"
#include "globals.h"
#include "timer.h"
#include "graphics.h"
#include "ADCDriver.h"


unsigned char g_enemySpritesIdle[MAX_DANCE][50] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x55, 0x00, 0x50, 0x05, 0x00, 0xff, 0x00, 0x50, 0x0a, 0x55, 0x55, 0x55, 0xa0, 0x0a, 0xaa, 0x55, 0xaa, 0xa0, 0x00, 0xa0, 0x55, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x05, 0x00, 0x55, 0x00, 0x50, 0x05, 0x55, 0xff, 0x55, 0x50, 0x0a, 0xa5, 0x55, 0x5a, 0xa0, 0x0a, 0x05, 0x55, 0x50, 0xa0, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x05, 0x00, 0x55, 0x00, 0x50, 0x05, 0x55, 0xff, 0x55, 0x50, 0x0a, 0xa5, 0x55, 0x5a, 0xa0, 0x0a, 0x05, 0x55, 0x50, 0xa0, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x55, 0x00, 0x50, 0x05, 0x00, 0xff, 0x00, 0x50, 0x0a, 0x55, 0x55, 0x55, 0xa0, 0x0a, 0xaa, 0x55, 0xaa, 0xa0, 0x00, 0xa0, 0x55, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x05, 0x00, 0x55, 0x00, 0x50, 0x05, 0x55, 0xff, 0x55, 0x50, 0x00, 0xa5, 0x55, 0x5a, 0x00, 0x0a, 0xa0, 0x55, 0x0a, 0xa0, 0x0a, 0x00, 0x55, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x05, 0x00, 0x55, 0x00, 0x50, 0x05, 0x55, 0xff, 0x55, 0x50, 0x00, 0xa5, 0x55, 0x5a, 0x00, 0x0a, 0xa0, 0x55, 0x0a, 0xa0, 0x0a, 0x00, 0x55, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

unsigned char g_explosionSprites[MAX_EXPLOSION][196] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x5f, 0x50, 0x00, 0x00, 0x05, 0x5a, 0x55, 0x5f, 0x55, 0xa5, 0x00, 0x05, 0xf5, 0x5f, 0xf5, 0xf5, 0x5f, 0x00, 0x55, 0xf5, 0xf5, 0xf5, 0xf5, 0xf5, 0x50, 0x00, 0x05, 0x5f, 0xff, 0xf5, 0x55, 0x55, 0x00, 0x5f, 0x55, 0xff, 0x5f, 0x55, 0x00, 0x00, 0x55, 0x55, 0x5f, 0x55, 0xff, 0x00, 0x00, 0x55, 0x50, 0x55, 0xaa, 0x55, 0x00, 0x00, 0x05, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x70, 0x00, 0x00, 0x00, 0x07, 0x77, 0x70, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xf7, 0x77, 0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x70, 0xf0, 0x00, 0x00, 0x00, 0xf7, 0x0f, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xff, 0x70, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x05, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x05, 0x00, 0x00, 0x00, 0x0a, 0x05, 0x05, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x55, 0x5f, 0x00, 0x0a, 0x00, 0x00, 0x05, 0x55, 0xfa, 0x0a, 0xa0, 0x00, 0x0a, 0x55, 0xaf, 0xff, 0x50, 0x00, 0x00, 0x00, 0x50, 0x50, 0x05, 0x00, 0x50, 0x00, 0x05, 0xa5, 0x00, 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x50, 0xa0, 0x00, 0x00, 0x0a, 0x00, 0xa0, 0x05, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xa0, 0xa0, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0a, 0x55, 0x50, 0x0f, 0xa0, 0x00, 0xa0, 0x00, 0x05, 0x55, 0xff, 0xf0, 0x0a, 0x00, 0xa5, 0x55, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x05, 0x5f, 0xff, 0x55, 0x00, 0x00, 0x00, 0xa0, 0x55, 0x0f, 0x00, 0x05, 0x00, 0x05, 0x00, 0x50, 0x00, 0x00, 0x0a, 0x00, 0x50, 0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x50, 0x00, 0x05, 0x0a, 0x50, 0x00, 0x0a, 0xa0, 0x00, 0xa0, 0x00, 0x0a, 0x00, 0xa0, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

unsigned char g_playerSprites[2][168] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x50, 0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa5, 0xa0, 0x00, 0x00, 0x0f, 0x00, 0xa5, 0xa0, 0x0f, 0x00, 0x0f, 0x0a, 0xa5, 0xaa, 0x0f, 0x00, 0x0f, 0xaa, 0xa5, 0xaa, 0xaf, 0x00, 0x0f, 0x0a, 0xa0, 0xaa, 0x0f, 0x00, 0x0f, 0x00, 0xa0, 0xa0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x50, 0x00, 0x00, 0x00, 0x05, 0x55, 0x55, 0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0a, 0x00, 0x0f, 0x00, 0xff, 0xf0, 0xaa, 0xa0, 0xff, 0xf0, 0xfa, 0xfa, 0xaa, 0xaa, 0xfa, 0xf0, 0xfa, 0xfa, 0x0a, 0x0a, 0xfa, 0xf0, 0xfa, 0xf0, 0x0a, 0x00, 0xfa, 0xf0, 0xfa, 0xf0, 0x00, 0x00, 0xfa, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

unsigned char g_playerExplosionSprites[MAX_EXPLOSION][728] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x50, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x55, 0xa0, 0xff, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xff, 0x00, 0xaf, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xfa, 0x00, 0x00, 0x00, 0x00, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0x00, 0x05, 0x00, 0x0a, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xa0, 0x00, 0x55, 0x50, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x55, 0x55, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x05, 0x05, 0x05, 0x00, 0x0f, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x5f, 0xf0, 0x05, 0x00, 0x05, 0x00, 0x05, 0x00, 0xf0, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0xf0, 0x50, 0x00, 0x00, 0x05, 0xf0, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x50, 0x00, 0x50, 0x00, 0x00, 0x50, 0xf0, 0x00, 0x55, 0x55, 0x05, 0x05, 0x55, 0x50, 0x05, 0x00, 0x00, 0x05, 0x0f, 0xa0, 0x00, 0x55, 0x50, 0x05, 0x00, 0x55, 0x50, 0x50, 0x00, 0x00, 0x00, 0x50, 0xf0, 0x00, 0x55, 0x50, 0x00, 0x00, 0x55, 0x50, 0x05, 0x00, 0x00, 0x00, 0x05, 0x0f, 0x00, 0x55, 0x50, 0x00, 0x00, 0x55, 0x50, 0x00, 0x50, 0x00, 0x00, 0x00, 0x05, 0x50, 0x05, 0x0f, 0xf0, 0x00, 0x05, 0x0f, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xa0, 0x05, 0x5a, 0x00, 0x00, 0x0f, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x0f, 0xaf, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xaf, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x50, 0x05, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xff, 0xa0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x05, 0x50, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x50, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xa5, 0x00, 0xa0, 0x55, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x5a, 0x00, 0xa0, 0x00, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xa0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0xa0, 0x0f, 0x00, 0x00, 0x00, 0x05, 0xa0, 0x00, 0x00, 0x55, 0x00, 0x00, 0x0a, 0xaf, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x05, 0x0a, 0x50, 0x5a, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x05, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x05, 0x50, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xaa, 0xff, 0x00, 0x00, 0x0a, 0x0a, 0x05, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x5a, 0xaf, 0xf0, 0x00, 0x00, 0x50, 0xa0, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x50, 0x00, 0x05, 0x0f, 0x55, 0x00, 0x05, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xaa, 0xa0, 0x05, 0x0a, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x00, 0x0a, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x0f, 0xaa, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x50, 0x05, 0xf5, 0x50, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xff, 0x00, 0x05, 0xf5, 0x5a, 0x5a, 0xf5, 0x50, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x5a, 0xa5, 0xa5, 0xf5, 0xfa, 0x55, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xa5, 0x55, 0x5f, 0xa5, 0x5a, 0xaa, 0xaa, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x50, 0x55, 0xf5, 0x55, 0x55, 0x50, 0x55, 0xa0, 0x0f, 0xf0, 0x00, 0x05, 0xaf, 0xf5, 0x50, 0x5a, 0x00, 0xf0, 0xf5, 0x55, 0xa5, 0xa0, 0x0f, 0x00, 0x00, 0x55, 0x5f, 0x05, 0xaa, 0x00, 0xff, 0xaf, 0x5a, 0x5a, 0x00, 0x00, 0xf0, 0x05, 0xaa, 0xa5, 0x5a, 0xaa, 0x0a, 0xfa, 0x55, 0x5a, 0x5a, 0x00, 0x00, 0x55, 0x5a, 0x55, 0x50, 0xaa, 0xaa, 0x0a, 0xaa, 0x55, 0x5a, 0x50, 0x00, 0x00, 0x55, 0xa5, 0x5f, 0xa0, 0x0a, 0xaa, 0xaa, 0xf5, 0x55, 0xa5, 0x50, 0x00, 0x00, 0x0a, 0x5f, 0xf0, 0xaa, 0x00, 0xaa, 0x0a, 0x5f, 0xfa, 0x55, 0x00, 0x00, 0x00, 0x0a, 0x5f, 0x55, 0x00, 0x0a, 0xaa, 0x00, 0xa5, 0xff, 0x50, 0x00, 0x00, 0x00, 0x5a, 0x55, 0xfa, 0xa0, 0x0a, 0x00, 0x00, 0x55, 0x0a, 0x55, 0x00, 0x00, 0x00, 0x05, 0xa5, 0x55, 0x55, 0xaa, 0xaa, 0xa0, 0xa0, 0x55, 0xa5, 0x50, 0x00, 0x00, 0x00, 0x05, 0x55, 0x55, 0x55, 0xaa, 0x55, 0xff, 0xaf, 0x55, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xa5, 0x5a, 0x5a, 0x55, 0xff, 0x5f, 0xa5, 0x50, 0x00, 0x00, 0x00, 0x00, 0xff, 0x5a, 0x55, 0x5a, 0x5a, 0x55, 0xff, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x5a, 0x55, 0x55, 0x55, 0xa5, 0xaa, 0x5f, 0xa0, 0x00, 0x00, 0x00, 0x0f, 0x0a, 0x00, 0x55, 0xaf, 0x00, 0x0a, 0xf5, 0x5a, 0xff, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0xaa, 0x0f, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xaa, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0xaf, 0xa0, 0x0a, 0xfa, 0xff, 0xa0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xa0, 0x0a, 0xfa, 0xaa, 0xff, 0xaa, 0xaf, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaf, 0xfa, 0xaf, 0xa0, 0xa5, 0xaf, 0xfa, 0xaa, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0xaf, 0xff, 0xa5, 0x50, 0x50, 0xaa, 0xaa, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0a, 0xaf, 0xfa, 0x05, 0x05, 0x50, 0x00, 0xaf, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xfa, 0x55, 0x05, 0x55, 0x05, 0xaf, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaf, 0xff, 0xa5, 0x50, 0x55, 0x5a, 0xff, 0xff, 0xa0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfa, 0x05, 0x55, 0x55, 0x50, 0xaf, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x50, 0x55, 0x55, 0x55, 0xaa, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xfa, 0x50, 0x05, 0x55, 0x05, 0xaf, 0xff, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaf, 0xaa, 0x5a, 0xa5, 0x5a, 0x50, 0xaa, 0xaf, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0xaf, 0xfa, 0xa0, 0x5a, 0xaa, 0xaf, 0xff, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xa0, 0xf0, 0x5a, 0xfa, 0xaa, 0xff, 0xa0, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0xfa, 0x00, 0xf0, 0x5a, 0xfa, 0x00, 0x0f, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xfa, 0x0a, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

unsigned char g_bulletSprite[2] = { 0xFF, 0xFF };

EnemyR g_enemies[MAX_ENEMIES];
BulletR g_enemyBullets[MAX_ENEMY_BULLETS];
BulletR g_playerBullets[MAX_PLAYER_BULLETS];
StarR g_stars[MAX_STARS];
PlayerR g_player;

BulletR emptyBullet;


void (*EnemyAI[MAX_LEVELS])(EnemyR* enemy);
unsigned char g_Stringz[6][21] = {"  You're hurting us. ",
																	"    This isn't fun.  ",
																	" I don't wanna fight.",
																	"You killed my family!",
																	" An eye for an eye...",
																	"\0"};

unsigned char g_level = 0;

unsigned int g_bulletTimer = 0;
unsigned int g_shotgunTimer = 0;
unsigned int g_shieldTimer = 0;
unsigned int g_levelTimer = 0;
unsigned int rollover = 0;
unsigned int LEVEL_MAX_BULLETS = 1;
signed int LEVEL_RANDOM = 100;

volatile unsigned long g_step = 0;

void LevelZero(EnemyR* enemy) {
	//	Avoidance
	if ((g_step%16) == 0) {
		(*enemy).xpos += (*enemy).flock;
	}
	if ((g_step%128) == 0) {
		(*enemy).flock = -(*enemy).flock;
	}	
}

void LevelOne(EnemyR* enemy) {
	char i,j;
	if ((*enemy).xpos0 == (*enemy).xpos) {
		(*enemy).xdir = 0;
	}
	i = 1;
	for (j = 0; j < MAX_PLAYER_BULLETS; j++) {
		if ((g_playerBullets[j].stat == B_ALIVE) && 
			((g_playerBullets[j].xpos - (*enemy).xpos0) <= ENEMY_BOX) && 
			((g_playerBullets[j].xpos + 2 - (*enemy).xpos0) >= 0) && 
			(g_playerBullets[j].ypos > (*enemy).ypos0)) {
				if ((*enemy).xdir == 0) {
					(*enemy).xdir = 2*(RandomExtract()%2) - 1;
				}
				i = 0;
				break;
		}
	}
	if ((*enemy).xpos > (*enemy).xpos0 + 10) {
		(*enemy).xdir = -i;
	}
	if ((*enemy).xpos + 10 < (*enemy).xpos0) {
		(*enemy).xdir = i;
	}
	(*enemy).xpos += (*enemy).xdir;
}


void LevelTwo(EnemyR* enemy) {
	BulletR* bullet;
	LEVEL_MAX_BULLETS = 4;
	LEVEL_RANDOM = 100;
	if ((g_player.stat == P_ALIVE) && (RandomExtract()%LEVEL_RANDOM == 2)) {
		if ((((*enemy).xpos - g_player.xpos) <= PLAYER_BOX + 16) && (((*enemy).xpos + 2 - g_player.xpos) > 0 - 16)) {
			(*enemy).animationStep = 0;
			(*enemy).stat = E_FIRE;
			bullet = FreshBullet(&g_enemyBullets, LEVEL_MAX_BULLETS);
			(*bullet).stat = B_ALIVE;
			(*bullet).xpos = (*enemy).xpos+ENEMY_BOX/2;
			(*bullet).ypos = (*enemy).ypos + 2;
			(*bullet).direction = 0;
		}
	}
	LevelOne(enemy);
}

void LevelThree(EnemyR* enemy) {
	if ((g_player.stat == P_ALIVE) && (RandomExtract()%LEVEL_RANDOM == 2)) {
		(*enemy).animationStep = 0;
		(*enemy).stat = E_FIRE;
		BulletTarget(FreshBullet(&g_enemyBullets, LEVEL_MAX_BULLETS), (*enemy).xpos + ENEMY_BOX/2, (*enemy).ypos + 2, g_player.xpos, g_player.ypos);
	}
	LevelOne(enemy);
}

void LevelFour(EnemyR* enemy) {
	// SUPER COOL BOSS
}

BulletR* FreshBullet(BulletR (*bullets)[], unsigned int max) {
	int j;
	for (j = 0; j < max;  j++) {
		if ((*bullets)[j].stat == B_DEAD) {
			return &(*bullets)[j];
		}
	}
	return &emptyBullet;
}

void BulletAngle(BulletR* bullet, int xpos, int ypos, int angle) {
	BulletTarget(bullet, xpos, ypos, xpos+cosarr[angle], ypos+sinarr[angle]);
}

void BulletTarget(BulletR* bullet, int xpos, int ypos, int xdest, int ydest) {
	int tmp;
	(*bullet).stat = B_ALIVE;
	(*bullet).xpos = xpos;
	(*bullet).ypos = ypos;
	(*bullet).dx1 = 0;
	(*bullet).dy1 = 0;
	(*bullet).dx2 = 0;
	(*bullet).dy2 = 0;
	if ((xdest - xpos) < 0) {
		(*bullet).dx1 = -1;
		(*bullet).dx2 = -1;
	} else if ((xdest - xpos) > 0) {
		(*bullet).dx1 = 1;
		(*bullet).dx2 = 1;
	}
	if ((ydest - ypos) < 0) {
		(*bullet).dy1 = -1;
	} else if ((ydest - ypos) > 0) {
		(*bullet).dy1 = 1;
	}
	(*bullet).longest = (xdest > xpos) ? xdest - xpos : xpos - xdest;
	(*bullet).shortest = (ydest > ypos) ? ydest - ypos : ypos - ydest;
	if ((*bullet).longest<=(*bullet).shortest) {
		tmp = (*bullet).longest;
		(*bullet).longest = (*bullet).shortest;
		(*bullet).shortest = tmp;
		if ((ydest - ypos) < 0) {
			(*bullet).dy2 = -1;
		} else if ((ydest - ypos) > 0) {
			(*bullet).dy2 = 1;
		}
		(*bullet).dx2 = 0;
	}
	(*bullet).numerator = (*bullet).longest >> 1;
	(*bullet).direction = 1;
}

void GameUpdate(void) {
	int i, j;
	BulletR* bullet;
	if (g_player.score > rollover && (g_player.score%500) == 0) {
		g_player.health++;
		rollover = g_player.score;
	}
	if (g_player.stat != P_DEAD) {
		if ((g_player.health <= 0) && (g_player.stat == P_ALIVE)) {
			g_player.stat = P_HIT;
			g_player.animationStep = 0;
		}
		/*
		j = (ADC_In()-ADC_MIN)*128/(ADC_MAX-ADC_MIN);
		if (j > 0 && j < 128) {
			g_soundArray = &g_soundMove;
			g_soundIndex = 0;
			g_soundMax = SND_MOVE_LENGTH;
		}*/
		if ((GPIO_PORTG_DATA_R&0x20) == 0) {
			if ((g_soundArray == 0) || (g_soundIndex > SND_MOVE_LENGTH/2)) {
				g_soundArray = &g_soundMove;
				g_soundIndex = 0;
				g_soundMax = SND_MOVE_LENGTH; 
			}
			if (g_player.xpos > 0) {
				g_player.xpos--;
			}
		} else if ((GPIO_PORTG_DATA_R&0x40) == 0) {
			if ((g_soundArray == 0) || (g_soundIndex > SND_MOVE_LENGTH/2)) {
				g_soundArray = &g_soundMove;
				g_soundIndex = 0;
				g_soundMax = SND_MOVE_LENGTH; 
			}
			if (g_player.xpos < (127-PLAYER_BOX)) {
				g_player.xpos++;
			}
		}
		if (HWREGBITW(&g_flags, FLAG_BUTTON_SELECT)) {
			if (g_bulletTimer == 0) {
				for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
					if (g_playerBullets[i].stat == B_DEAD) {
						g_playerBullets[i].stat = B_ALIVE;
						g_playerBullets[i].xpos = g_player.xpos+PLAYER_BOX/2-2;
						g_playerBullets[i].ypos = g_player.ypos - 2;
						g_playerBullets[i].direction = 0;
						g_soundArray = &g_soundBullet;
						g_soundIndex = 0;
						g_soundMax = SND_BULLET_LENGTH; 
						break;
					}
				}
				g_bulletTimer = 15;
			}
		}
		if (HWREGBITW(&g_flags, FLAG_BUTTON_UP)) {
			if (g_shotgunTimer == 0) {
				bullet = FreshBullet(&g_playerBullets, MAX_PLAYER_BULLETS);
				BulletAngle(bullet, g_player.xpos, g_player.ypos, 17);
				bullet = FreshBullet(&g_playerBullets, MAX_PLAYER_BULLETS);
				BulletAngle(bullet, g_player.xpos, g_player.ypos, 18);
				bullet = FreshBullet(&g_playerBullets, MAX_PLAYER_BULLETS);
				BulletAngle(bullet, g_player.xpos, g_player.ypos, 19);
				g_shotgunTimer = 100;
			}
		}
		if (HWREGBITW(&g_flags, FLAG_BUTTON_DOWN)) {
			if (g_player.score > 500) {
				g_player.score -= 500;
				g_player.shield = 1;
				g_shieldTimer = 200;
			}
		}
		if (g_shieldTimer == 0) {
			g_player.shield = 0;
		}
	}
	j=0;
	for (i = 0; i < MAX_ENEMIES; i++) {
		if ((g_enemies[i].stat == E_ALIVE) || (g_enemies[i].stat == E_FIRE)) {
			if (g_enemies[i].health == 0) {
				g_enemies[i].stat = E_HIT;
				g_enemies[i].animationStep = 0;
			}
			(*EnemyAI[g_level])(&g_enemies[i]);
			j++;
		}
	}
	if ((j == 0) && (g_levelTimer == 0)) {
		g_levelTimer = 1000;
	}
	if (g_levelTimer == 1) {
		EnemyInit();
		g_player.score += 200;
		g_player.health++;
		if (g_level < MAX_LEVELS-1) {
			g_level++;
			g_levelTimer = 0;
		}
	}
	for (i = 0; i < MAX_ENEMY_BULLETS; i++) {
		if (g_enemyBullets[i].stat == B_ALIVE) {
			//	BULLET DIRECTION
			if (g_enemyBullets[i].direction != 0) {		
				g_enemyBullets[i].numerator += g_enemyBullets[i].shortest;
				if (g_enemyBullets[i].numerator < g_enemyBullets[i].longest) {
					g_enemyBullets[i].xpos += g_enemyBullets[i].dx2;
					g_enemyBullets[i].ypos += g_enemyBullets[i].dy2;
				} else {
					g_enemyBullets[i].numerator -= g_enemyBullets[i].longest;
					g_enemyBullets[i].xpos += g_enemyBullets[i].dx1;
					g_enemyBullets[i].ypos += g_enemyBullets[i].dy1;
				}
			} else {
				g_enemyBullets[i].ypos++;
			}

			if ((g_enemyBullets[i].ypos >= 96) || (g_enemyBullets[i].xpos < 0) || (g_enemyBullets[i].xpos > 128)) {
					g_enemyBullets[i].stat = B_DEAD;
			}
			
			if ((g_player.stat == P_ALIVE) && (g_player.shield == 0) && 
				((g_enemyBullets[i].xpos - g_player.xpos) <= PLAYER_BOX) && 
				((g_enemyBullets[i].xpos + 2 - g_player.xpos) > 0) && 
				((g_enemyBullets[i].ypos - g_player.ypos) <= PLAYER_BOX) && 
				((g_enemyBullets[i].ypos + 2 - g_player.ypos) > 0)) {
					g_player.health--;
					g_player.score -= 25;
					if (g_player.score < 0) {
						g_player.score = 0;	
					}
					g_player.stat = P_HIT;
					g_enemyBullets[i].stat = B_DEAD;
			}
		}
	}
	for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
		if (g_playerBullets[i].stat == B_ALIVE) {
			//	BULLET DIRECTION
			if (g_playerBullets[i].direction != 0) {		
				g_playerBullets[i].numerator += g_playerBullets[i].shortest;
				if (g_playerBullets[i].numerator < g_playerBullets[i].longest) {
					g_playerBullets[i].xpos += g_playerBullets[i].dx2;
					g_playerBullets[i].ypos += g_playerBullets[i].dy2;
				} else {
					g_playerBullets[i].numerator -= g_playerBullets[i].longest;
					g_playerBullets[i].xpos += g_playerBullets[i].dx1;
					g_playerBullets[i].ypos += g_playerBullets[i].dy1;
				}
			} else {
				g_playerBullets[i].ypos--;
			}

			if ((g_playerBullets[i].ypos < 0) || (g_playerBullets[i].xpos < 0) || (g_playerBullets[i].xpos > 128)) {
					g_playerBullets[i].stat = B_DEAD;
			}

			for (j = 0; j < MAX_ENEMIES; j++) {
				if (((g_enemies[j].stat == E_ALIVE) || (g_enemies[j].stat == E_FIRE)) && 
					((g_playerBullets[i].xpos - g_enemies[j].xpos) <= ENEMY_BOX) && 
					((g_playerBullets[i].xpos + 2 - g_enemies[j].xpos) > 0) && 
					((g_playerBullets[i].ypos - g_enemies[j].ypos) <= ENEMY_BOX) && 
					((g_playerBullets[i].ypos + 2 - g_enemies[j].ypos) > 0)) {
					g_enemies[j].health--;
					if (g_enemies[j].health == 0) {
						g_enemies[j].stat = E_HIT;
						g_player.score += 25;
					}
					g_player.score += 25;
					g_playerBullets[i].stat = B_DEAD;
					break;
				}
			}
		}
	}
	if(g_levelTimer == 0) {
		for (i = 0; i < MAX_STARS; i++) {
			if (((g_step%2) == 0) || (g_levelTimer != 0)) {
				g_stars[i].ypos++;
				if (g_stars[i].ypos >= 96) {
					g_stars[i].xpos	= RandomExtract()%128;
					g_stars[i].ypos	= 0;
				}
			}
		}
	} else { 
		for (i = 0; i < MAX_STARS; i++) {
			g_stars[i].ypos += 2;
			if (g_stars[i].ypos >= 96) {
				g_stars[i].xpos	= RandomExtract()%128;
				g_stars[i].ypos	= 0;
			}
		}
		g_levelTimer--;
	}
	g_step++;
	if (g_bulletTimer > 0) {
		g_bulletTimer--;
	}
	if (g_shotgunTimer > 0) {
		g_shotgunTimer--;
	}
	if (g_shieldTimer > 0) {
		g_shieldTimer--;
	}
	HWREGBITW(&g_flags, FLAG_BUTTON_UP) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_DOWN) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_LEFT) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_RIGHT) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 0;
}

void EnemyInit(void) {
	int x,y;
	if (g_level > 3) {
		LEVEL_MAX_BULLETS += 10;
		if (LEVEL_MAX_BULLETS > MAX_ENEMY_BULLETS) {
			LEVEL_MAX_BULLETS = MAX_ENEMY_BULLETS;
		}
		LEVEL_RANDOM -= 10;
		if (LEVEL_RANDOM < 5) {
			LEVEL_RANDOM = 5;
		}
	}
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 4; x++) {
			g_enemies[y*4+x].xpos0 = x*24+12;
			g_enemies[y*4+x].ypos0 = y*12+6;
			g_enemies[y*4+x].xpos = x*24+12;
			g_enemies[y*4+x].ypos = y*12+6;
			g_enemies[y*4+x].col = x;
			g_enemies[y*4+x].row = y;
			g_enemies[y*4+x].flock = ((y%2)==0) ? 1 : -1;
			g_enemies[y*4+x].animationStep = 0;
			g_enemies[y*4+x].health = ((1+g_level/4) < 5) ? 1+g_level/4 : 4;
			g_enemies[y*4+x].stat = E_ALIVE;
			g_enemies[y*4+x].xdir = 0;
		}
	}
}

void GameInit(void) {
	int i;
	EnemyInit();
	for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
		g_playerBullets[i].stat = B_DEAD;
	}
	for (i = 0; i < MAX_ENEMY_BULLETS; i++) {
		g_enemyBullets[i].stat = B_DEAD;
	}
	for (i = 0; i < MAX_STARS; i++) {
		g_stars[i].xpos = RandomExtract()%128;
		g_stars[i].ypos = RandomExtract()%96;
	}
	g_player.xpos = 128/2-12/2;
	g_player.ypos = 96-14-4;
	g_player.shield = 0;
	g_player.score = 0;
	g_player.health = 5;
	g_player.stat = P_ALIVE;
	
	EnemyAI[0] = LevelZero;
	EnemyAI[1] = LevelOne;
	EnemyAI[2] = LevelTwo;
	EnemyAI[3] = LevelThree;
	EnemyAI[4] = LevelThree;
	EnemyAI[5] = LevelThree;
	
	g_step = 0;
	g_level = 0;
	
	Timer1AInit(*GameUpdate, 1000000/100);
}


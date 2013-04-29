
#include "inc/lm3s1968.h"
#include "inc/hw_types.h"

#include "sound.h"
#include "game.h"
#include "random.h"
#include "globals.h"
#include "timer.h"
#include "graphics.h"
#include <math.h>

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
unsigned char g_level = 0;

unsigned int bulletTimer = 0;
unsigned int shotgunTimer = 0;
unsigned int rollover = 0;
unsigned int LEVEL_MAX_BULLETS = 1;
unsigned int currentEnemies = 0;

volatile unsigned long g_step = 0;

void LevelOne(EnemyR* enemy) {
	BulletR* bullet;
	LEVEL_MAX_BULLETS = 4;
	//	NAIVE SHOOTING ALGORITHM (for easy AI)
	//	ONLY SHOOT IF YOU ARE THE FIRST SHIP IN YOUR COLUMN
	//	AND THE PLAYER IS ALIVE AND RANDOM NUMBER
	if ((g_player.stat == P_ALIVE) && (RandomExtract()%100 == 8)) {
		if ((((*enemy).xpos - g_player.xpos) <= g_player.width + 16) && (((*enemy).xpos + 2 - g_player.xpos) > 0 - 16)) {
			(*enemy).animationStep = 0;
			(*enemy).stat = E_FIRE;
			bullet = FreshBullet(&g_enemyBullets, LEVEL_MAX_BULLETS);
			(*bullet).stat = B_ALIVE;
			(*bullet).xpos = (*enemy).xpos+(*enemy).width/2;
			(*bullet).ypos = (*enemy).ypos + 2;
			(*bullet).direction = 0;
		}
	}
	//	NAIVE MOVEMENT ALGORITHM
	if ((g_step%16) == 0) {
		(*enemy).xpos += (*enemy).flock;
	}
	if ((g_step%128) == 0) {
		(*enemy).flock = -(*enemy).flock;
	}
}

void LevelTwo(EnemyR* enemy) {
	LEVEL_MAX_BULLETS = 10;
	if ((g_player.stat == P_ALIVE) && (RandomExtract()%100 == 8)) {
		(*enemy).animationStep = 0;
		(*enemy).stat = E_FIRE;
		BulletTarget(FreshBullet(&g_enemyBullets, LEVEL_MAX_BULLETS), (*enemy).xpos + (*enemy).width/2, (*enemy).ypos + 2, g_player.xpos, g_player.ypos);
	}
	//	NAIVE MOVEMENT ALGORITHM
	if ((g_step%16) == 0) {
		(*enemy).xpos += (*enemy).flock;
	}
	if ((g_step%128) == 0) {
		(*enemy).flock = -(*enemy).flock;
	}
}

void LevelThree(EnemyR* enemy) {
	LEVEL_MAX_BULLETS = 20;
	if ((g_player.stat == P_ALIVE) && (RandomExtract()%50 == 8)) {
		(*enemy).animationStep = 0;
		(*enemy).stat = E_FIRE;
		BulletTarget(FreshBullet(&g_enemyBullets, LEVEL_MAX_BULLETS), (*enemy).xpos + (*enemy).width/2, (*enemy).ypos + 2, g_player.xpos, g_player.ypos);
	}
	//	NAIVE MOVEMENT ALGORITHM
	if ((g_step%16) == 0) {
		(*enemy).xpos += (*enemy).flock;
	}
	if ((g_step%64) == 0) {
		(*enemy).flock = -(*enemy).flock;
	}
	//	FACE PLAYER
	
}

void LevelFour(EnemyR* enemy) {
	/*
	//	HARD MODE SHOOTING ALGORITHM :D
	if (RandomExtract()%2048 == 1) {
		for (j = 0; j < MAX_ENEMY_BULLETS;  j++) {
			if (g_enemyBullets[j].stat == B_DEAD) {
				g_enemyBullets[j].stat = B_ALIVE;
				g_enemyBullets[j].xpos = g_enemies[i].xpos+g_enemies[i].width/2-2;
				g_enemyBullets[j].ypos = g_enemies[i].ypos + 2;
				// make the bullet go towards the player:
				g_enemyBullets[j].xpos0 = g_enemyBullets[j].xpos;
				g_enemyBullets[j].ypos0 = g_enemyBullets[j].ypos;
				g_enemyBullets[j].xpos1 = g_player.xpos;
				g_enemyBullets[j].ypos1 = g_player.ypos;
				g_enemyBullets[j].xposA = g_enemyBullets[j].xpos * 8;
				g_enemyBullets[j].yposA = g_enemyBullets[j].ypos * 8;					
				g_enemyBullets[j].xposI = (g_enemyBullets[j].xpos1 - g_enemyBullets[j].xpos0);
				g_enemyBullets[j].yposI = (g_enemyBullets[j].ypos1 - g_enemyBullets[j].ypos0);
				distance = sqrt((g_enemyBullets[j].xposI)^2 + (g_enemyBullets[j].yposI)^2);
				g_enemyBullets[j].xposI = (g_enemyBullets[j].xposI * 8) / distance;
				g_enemyBullets[j].yposI = (g_enemyBullets[j].yposI * 8) / distance;
				break;
			}
		}
	}
	//	DODGING ALGORITHM
	for (i = 0; i < MAX_ENEMIES; i++) {
		for (j = 0; j < MAX_PLAYER_BULLETS; j++) {
			if ((g_enemies[i].stat == E_ALIVE) && 
					((g_playerBullets[j].xpos - g_enemies[i].xpos) <= g_enemies[i].width) && 
					((g_playerBullets[j].xpos + 2 - g_enemies[i].xpos) > 0)) {
					if (g_enemies[i].xpos0 <= g_enemies[i].xpos - 6) {
						if (g_enemies[i].ypos0 > g_enemies[j].ypos) {
							g_enemies[i].xpos--;
							g_enemies[i].ypos++;
						} else {
							g_enemies[i].xpos--;
							g_enemies[i].ypos--;
						}
					} else {
						if (g_enemies[i].ypos0 > g_enemies[j].ypos) {
							g_enemies[i].xpos++;
							g_enemies[i].ypos++;
						} else {
							g_enemies[i].xpos++;
							g_enemies[i].ypos--;
						}
					}
			}
		}
	}
	*/
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
			if (g_player.xpos < (127-g_player.width)) {
				g_player.xpos++;
			}
		}
		if (HWREGBITW(&g_flags, FLAG_BUTTON_SELECT)) {
			if (bulletTimer == 0) {
				for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
					if (g_playerBullets[i].stat == B_DEAD) {
						g_playerBullets[i].stat = B_ALIVE;
						g_playerBullets[i].xpos = g_player.xpos+g_player.width/2-2;
						g_playerBullets[i].ypos = g_player.ypos - 2;
						g_playerBullets[i].direction = 0;
						g_soundArray = &g_soundBullet;
						g_soundIndex = 0;
						g_soundMax = SND_BULLET_LENGTH; 
						break;
					}
				}
				bulletTimer = 50;
			}
		}
		if (HWREGBITW(&g_flags, FLAG_BUTTON_UP)) {
			if (shotgunTimer == 0) {
				bullet = FreshBullet(&g_playerBullets, MAX_PLAYER_BULLETS);
				BulletAngle(bullet, g_player.xpos, g_player.ypos, 17);
				bullet = FreshBullet(&g_playerBullets, MAX_PLAYER_BULLETS);
				BulletAngle(bullet, g_player.xpos, g_player.ypos, 18);
				bullet = FreshBullet(&g_playerBullets, MAX_PLAYER_BULLETS);
				BulletAngle(bullet, g_player.xpos, g_player.ypos, 19);
				shotgunTimer = 100;
			}
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
	currentEnemies = j;
	if (currentEnemies == 0 && (g_step%400)==0) {
		EnemyInit();
		g_player.score += 200;
		g_player.health++;
		if (g_level < MAX_LEVELS-1) {
			g_level++;
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
			
			/*	BULLET DIRECTION ALGORITHM
			g_enemyBullets[i].xposA += g_enemyBullets[i].xposI / 8;
			g_enemyBullets[i].yposA += g_enemyBullets[i].yposI / 8;
			g_enemyBullets[i].xpos = g_enemyBullets[i].xposA / 8;
			g_enemyBullets[i].ypos = g_enemyBullets[i].yposA / 8;
			*/
			if ((g_player.stat == P_ALIVE) && 
				((g_enemyBullets[i].xpos - g_player.xpos) <= g_player.width) && 
				((g_enemyBullets[i].xpos + 2 - g_player.xpos) > 0) && 
				((g_enemyBullets[i].ypos - g_player.ypos) <= g_player.height) && 
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
					((g_playerBullets[i].xpos - g_enemies[j].xpos) <= g_enemies[j].width) && 
					((g_playerBullets[i].xpos + 2 - g_enemies[j].xpos) > 0) && 
					((g_playerBullets[i].ypos - g_enemies[j].ypos) <= g_enemies[j].height) && 
					((g_playerBullets[i].ypos + 2 - g_enemies[j].ypos) > 0)) {
					g_enemies[j].health--;
					if (g_enemies[j].health == 0) {
						g_player.score += 25;
					}
					g_player.score += 25;
					g_playerBullets[i].stat = B_DEAD;
				}
			}
		}
	}
	for (i = 0; i < MAX_STARS; i++) {
		if ((g_step%2) == 0) {
			g_stars[i].ypos++;
			if (g_stars[i].ypos >= 96) {
				g_stars[i].xpos	= RandomExtract()%128;
				g_stars[i].ypos	= 0;
			}
		}
	}
	g_step++;
	if (bulletTimer > 0) {
		bulletTimer--;
	}
	if (shotgunTimer > 0) {
		shotgunTimer--;
	}
	HWREGBITW(&g_flags, FLAG_BUTTON_UP) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_DOWN) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_LEFT) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_RIGHT) = 0;
	HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 0;
}

void EnemyInit(void) {
	int x,y;
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 4; x++) {
			g_enemies[y*4+x].xpos0 = x*20+24;
			g_enemies[y*4+x].ypos0 = y*12+4;
			g_enemies[y*4+x].xpos = x*20+24;
			g_enemies[y*4+x].ypos = y*12+4;
			g_enemies[y*4+x].width = 10;
			g_enemies[y*4+x].height = 10;
			g_enemies[y*4+x].col = x;
			g_enemies[y*4+x].row = y;
			g_enemies[y*4+x].flock = ((y%2)==0) ? 1 : -1;
			g_enemies[y*4+x].direction = 0;
			g_enemies[y*4+x].animationStep = 0;
			g_enemies[y*4+x].health = 1;
			g_enemies[y*4+x].stat = E_ALIVE;
		}
	}
}

void GameInit(void) {
	int i;
	EnemyInit();
	for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
		g_playerBullets[i].xpos = 0;
		g_playerBullets[i].ypos = 0;
		g_playerBullets[i].stat = B_DEAD;
	}
	for (i = 0; i < MAX_ENEMY_BULLETS; i++) {
		g_enemyBullets[i].xpos = 0;
		g_enemyBullets[i].ypos = 0;
		g_enemyBullets[i].direction = 0;
		/*
		g_enemyBullets[i].xposA = 0;
		g_enemyBullets[i].yposA = 0;
		g_enemyBullets[i].xposI = 0;
		g_enemyBullets[i].yposI = 0;
		g_enemyBullets[i].xpos0 = 0;
		g_enemyBullets[i].ypos0 = 0;
		g_enemyBullets[i].xpos1 = 0;
		g_enemyBullets[i].ypos1 = 0;
		*/
		g_enemyBullets[i].stat = B_DEAD;
	}
	for (i = 0; i < MAX_STARS; i++) {
		g_stars[i].xpos = RandomExtract()%128;
		g_stars[i].ypos = RandomExtract()%96;
	}
	g_player.xpos = 128/2-12/2;
	g_player.ypos = 96-14-4;
	g_player.width = 12;
	g_player.height = 12;
	g_player.direction = 0;
	g_player.animationStep = 0;
	g_player.shield = 0;
	g_player.score = 0;
	g_player.health = 5;
	g_player.stat = P_ALIVE;
	
	EnemyAI[0] = LevelOne;
	EnemyAI[1] = LevelTwo;
	EnemyAI[2] = LevelThree;
	EnemyAI[3] = LevelThree;
	EnemyAI[4] = LevelThree;
	
	g_step = 0;
	g_level = 0;
	
	Timer1AInit(*GameUpdate, 1000000/100);
}



#include "inc/lm3s1968.h"
#include "inc/hw_types.h"

#include "sound.h"
#include "game.h"
#include "random.h"
#include "globals.h"
#include "timer.h"
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

unsigned long g_step = 0;

void GameUpdate(void) {
	int i, j;
	double distance;
	switch(g_player.stat) {
		case P_ALIVE:
			if (g_player.health <= 0) {
				g_player.stat = P_HIT;
				g_player.animationStep = 0;
				break;
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
				if (g_player.xpos < 127) {
					g_player.xpos++;
				}
			}
			if (HWREGBITW(&g_flags, FLAG_BUTTON_SELECT)) {
				for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
					if (g_playerBullets[i].stat == B_DEAD) {
						g_playerBullets[i].stat = B_ALIVE;
						g_playerBullets[i].xpos = g_player.xpos+g_player.width/2-2;
						g_playerBullets[i].ypos = g_player.ypos - 2;
						g_soundArray = &g_soundBullet;
						g_soundIndex = 0;
						g_soundMax = SND_BULLET_LENGTH; 
						break;
					}
				}
			}
			break;
		case P_HIT:
			break;
		case P_DEAD:
			break;
	}
	for (i = 0; i < MAX_ENEMIES; i++) {
		switch (g_enemies[i].stat) {
			case E_ALIVE:
				if (g_enemies[i].health == 0) {
					g_enemies[i].stat = E_HIT;
					g_enemies[i].animationStep = 0;
				}
				//	NAIVE SHOOTING ALGORITHM (for easy AI)
				//	ONLY SHOOT IF YOU ARE THE FIRST SHIP IN YOUR COLUMN
				//	AND THE PLAYER IS ALIVE AND RANDOM NUMBER
				if ((g_player.stat == P_ALIVE) && (RandomExtract()%50 == 42)) {
					switch (g_enemies[i].row) {
						case 0:
							//if ((g_enemies[(g_enemies[i].row+2)*4+g_enemies[i].col].stat == E_ALIVE) &&
							//(g_enemies[(g_enemies[i].row+1)*4+g_enemies[i].col].stat == E_ALIVE)) {
							//	break;
							//}
						case 1:
							//if (g_enemies[(g_enemies[i].row+1)*4+g_enemies[i].col].stat == E_ALIVE) {
							//	break;
							//}
						case 2:
							if (((g_enemies[i].xpos - g_player.xpos) <= g_player.width + 16) && 
							((g_enemies[i].xpos + 2 - g_player.xpos) > 0 - 16)) {
								for (j = 0; j < MAX_ENEMY_BULLETS;  j++) {
									if (g_enemyBullets[j].stat == B_DEAD) {
										g_enemyBullets[j].stat = B_ALIVE;
										g_enemyBullets[j].xpos = g_enemies[i].xpos+g_enemies[i].width/2;
										g_enemyBullets[j].ypos = g_enemies[i].ypos + 2;
										break;
									}
								}
							}
					}
				}
				
				//	NAIVE MOVEMENT ALGORITHM
				if ((g_step%16) == 0) {
					g_enemies[i].xpos += g_enemies[i].flock;
				}
				if ((g_step%128) == 0) {
					g_enemies[i].flock = -g_enemies[i].flock;
				}
					
				/*	HARD MODE SHOOTING ALGORITHM :D
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
				*/
				/*	DODGING ALGORITHM
				for (j = 0; j < MAX_PLAYER_BULLETS; j++) {
					if ((g_enemies[i].stat == E_ALIVE) && (g_playerBullets[j].xpos - g_enemies[i].xpos) <= g_enemies[i].width) {
							if (g_enemies[i].xpos0 <= g_enemies[i].xpos) {
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
				*/
				// enemy code
				break;
			case E_HIT:
				break;
			case E_DEAD:
				break;
		}
	}
	for (i = 0; i < MAX_ENEMY_BULLETS; i++) {
		if (g_enemyBullets[i].stat == B_ALIVE) {
			/*	BULLET DIRECTION ALGORITHM
			g_enemyBullets[i].xposA += g_enemyBullets[i].xposI / 8;
			g_enemyBullets[i].yposA += g_enemyBullets[i].yposI / 8;
			g_enemyBullets[i].xpos = g_enemyBullets[i].xposA / 8;
			g_enemyBullets[i].ypos = g_enemyBullets[i].yposA / 8;
			*/
			g_enemyBullets[i].ypos+=2;
			if (g_enemyBullets[i].ypos >= 96) {
				g_enemyBullets[i].stat = B_DEAD;
			}
			if ((g_player.stat == P_ALIVE) && 
				((g_enemyBullets[i].xpos - g_player.xpos) <= g_player.width) && 
				((g_enemyBullets[i].xpos + 2 - g_player.xpos) > 0) && 
				((g_enemyBullets[i].ypos - g_player.ypos) <= g_player.height) && 
				((g_enemyBullets[i].ypos + 2 - g_player.ypos) > 0)) {
					g_player.health--;
					g_enemyBullets[i].stat = B_DEAD;
			}
		}
	}
	for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
		if (g_playerBullets[i].stat == B_ALIVE) {
			g_playerBullets[i].ypos-=2;
			if (g_playerBullets[i].ypos < 0) {
				g_playerBullets[i].stat = B_DEAD;
			}
			for (j = 0; j < MAX_ENEMIES; j++) {
				if ((g_enemies[j].stat == E_ALIVE) && 
					((g_playerBullets[i].xpos - g_enemies[j].xpos) <= g_enemies[j].width) && 
					((g_playerBullets[i].xpos + 2 - g_enemies[j].xpos) > 0) && 
					((g_playerBullets[i].ypos - g_enemies[j].ypos) <= g_enemies[j].height) && 
					((g_playerBullets[i].ypos + 2 - g_enemies[j].ypos) > 0)) {
					g_enemies[j].health--;
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
	HWREGBITW(&g_flags, FLAG_BUTTON_SELECT) = 0;
}

void GameInit(void) {
	int x,y;
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 4; x++) {
			g_enemies[y*4+x].xpos0 = x*20+24;
			g_enemies[y*4+x].ypos0 = y*12+8;
			g_enemies[y*4+x].xpos = x*20+24;
			g_enemies[y*4+x].ypos = y*12+8;
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
	for (y = 0; y < MAX_PLAYER_BULLETS; y++) {
		g_playerBullets[y].xpos = 0;
		g_playerBullets[y].ypos = 0;
		g_playerBullets[y].stat = B_DEAD;
	}
	for (y = 0; y < MAX_ENEMY_BULLETS; y++) {
		g_enemyBullets[y].xpos = 0;
		g_enemyBullets[y].ypos = 0;
		g_enemyBullets[y].xposA = 0;
		g_enemyBullets[y].yposA = 0;
		g_enemyBullets[y].xposI = 0;
		g_enemyBullets[y].yposI = 0;
		g_enemyBullets[y].stat = B_DEAD;
		g_enemyBullets[y].xpos0 = 0;
		g_enemyBullets[y].ypos0 = 0;
		g_enemyBullets[y].xpos1 = 0;
		g_enemyBullets[y].ypos1 = 0;
	}
	for (y = 0; y < MAX_STARS; y++) {
		g_stars[y].xpos = RandomExtract()%128;
		g_stars[y].ypos = RandomExtract()%96;
	}
	g_player.xpos = 128/2-12/2;
	g_player.ypos = 96-14-4;
	g_player.width = 12;
	g_player.height = 12;
	g_player.direction = 0;
	g_player.animationStep = 0;
	g_player.shield = 0;
	g_player.health = 2;
	g_player.stat = P_ALIVE;
	Timer1AInit(*GameUpdate, 1000000/100);
}


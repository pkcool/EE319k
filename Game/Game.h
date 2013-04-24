
#ifndef __GAME_H__
#define __GAME_H__

#define MAX_DANCE			6
#define MAX_EXPLOSION	5
#define MAX_ENEMIES		12
#define MAX_BULLETS		8
#define BULLET_SPEED	4

typedef enum {
	E_ALIVE,													// self explanatory
	E_HIT,														// we need to explode
	E_DEAD,														// self explanatory
	E_ATTACK													// we need to enter attack sequence
} EnemyStat;

typedef enum {
	P_ALIVE,													// self explanatory
	P_HIT,														// we need to explode a bit
	P_DEAD														// self explanatory
} PlayerStat;

typedef enum {
	B_ALIVE,													// self explanatory
	B_HIT,														// we need to explode a bit
	B_DEAD														// self explanatory
} BulletStat;

typedef struct {
	unsigned char xpos0, ypos0;			// initial x and y (in case we need to return)
	unsigned char xpos, ypos;				// current x and y
	unsigned char width, height;		// width and height of sprite in pixels (10x10)
	int direction;									// angle (angle = 15*direction)
	char animationStep;							// used for stepping through dance/explosion (please be nice and set to 0 if you're about to explode
	char health;										// number of hits before death (decremented on each hit)
	EnemyStat stat;									// used for game state
} EnemyR;

typedef struct {
	unsigned char xpos, ypos;				// x and y
	unsigned char width, height;		// width and height of sprite in pixels (12x14)
	int direction;									// angle (angle = 15*direction)
	char animationStep;							// used for stepping through explosion
	char shield;										// 0 for normal, 1 for shield (behavior to be determined)
	char health;										// number of hits before death (decremented on each hit)
	PlayerStat stat;								// used for game state
} PlayerR;

typedef struct {
	unsigned char xpos, ypos;				// x and y
	int direction;									// angle (angle = 15*direction)
	BulletStat stat;								// used for game state
} BulletR;

extern unsigned char g_enemySpritesIdle[MAX_DANCE][50];
extern unsigned char g_explosionSprites[MAX_EXPLOSION][196];
extern unsigned char g_playerSprites[2][168];
extern unsigned char g_playerExplosionSprites[MAX_EXPLOSION][728];
extern unsigned char g_bulletSprite[2];

extern EnemyR g_enemies[MAX_ENEMIES];
extern BulletR g_bullets[MAX_BULLETS];
extern PlayerR g_player;

void GameInit(void);

#endif //__GAME_H__

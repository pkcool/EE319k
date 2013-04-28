
#ifndef __GAME_H__
#define __GAME_H__

#define MAX_DANCE							6
#define MAX_EXPLOSION					5
#define MAX_ENEMIES						12
#define MAX_ENEMY_BULLETS			40
#define MAX_PLAYER_BULLETS		2
#define MAX_STARS							40
#define MAX_LEVELS						5

typedef enum {
	E_ALIVE,													// self explanatory
	E_FIRE,														// we need to dance
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
	B_DEAD														// self explanatory
} BulletStat;

typedef struct {
	signed char xpos0, ypos0;			// initial x and y (in case we need to return)
	signed char xpos, ypos;				// current x and y
	unsigned char width, height;		// width and height of sprite in pixels (10x10)
	int direction;									// angle (angle = 15*direction)
	char animationStep;							// used for stepping through dance/explosion (please be nice and set to 0 if you're about to explode
	char health;										// number of hits before death (decremented on each hit)
	unsigned char row, col;
	unsigned char flock;
	EnemyStat stat;									// used for game state
} EnemyR;

typedef struct {
	signed char xpos, ypos;				// x and y
	unsigned char width, height;		// width and height of sprite in pixels (12x14)
	int direction;									// angle (angle = 15*direction)
	char animationStep;							// used for stepping through explosion
	char shield;										// 0 for normal, 1 for shield (behavior to be determined)
	char health;										// number of hits before death (decremented on each hit)
	int score;
	PlayerStat stat;								// used for game state
} PlayerR;

typedef struct {
	signed char xpos, ypos;				// x and y
	signed int dx1, dx2, dy1, dy2, longest, shortest, numerator, direction;
	//signed int xposA, yposA; 		  // accurate x and y position * 8
	//signed char xposI, yposI;			// slope of travel * 8
  //signed char xpos0, ypos0; 		// used for starting position
	//signed char xpos1, ypos1;			// used for destination
	BulletStat stat;								// used for game state
} BulletR;

typedef struct {
	signed char xpos, ypos;				// x and y
} StarR;

extern unsigned char g_enemySpritesIdle[MAX_DANCE][50];
extern unsigned char g_explosionSprites[MAX_EXPLOSION][196];
extern unsigned char g_playerSprites[2][168];
extern unsigned char g_playerExplosionSprites[MAX_EXPLOSION][728];
extern unsigned char g_bulletSprite[2];

extern EnemyR g_enemies[MAX_ENEMIES];
extern BulletR g_enemyBullets[MAX_ENEMY_BULLETS];
extern BulletR g_playerBullets[MAX_PLAYER_BULLETS];
extern StarR g_stars[MAX_STARS];
extern PlayerR g_player;

extern void (*EnemyAI[MAX_LEVELS])(EnemyR* enemy);

void BulletTarget(int xpos, int ypos, int xdest, int ydest);
void EnemyInit(void);
void GameInit(void);

#endif //__GAME_H__

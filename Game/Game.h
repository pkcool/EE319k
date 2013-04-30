
#ifndef __GAME_H__
#define __GAME_H__

#define MAX_DANCE							6
#define MAX_EXPLOSION					5
#define MAX_ENEMIES						12
#define MAX_ENEMY_BULLETS			60
#define MAX_PLAYER_BULLETS		5
#define MAX_STARS							30
#define MAX_LEVELS						6

#define ADC_MAX		1022
#define ADC_MIN		88

#define PLAYER_BOX		12
#define ENEMY_BOX			10

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
	char animationStep;							// used for stepping through dance/explosion (please be nice and set to 0 if you're about to explode
	char health;										// number of hits before death (decremented on each hit)
	unsigned char row, col;
	unsigned char flock;
	signed char xdir;
	EnemyStat stat;									// used for game state
} EnemyR;

typedef struct {
	signed char xpos, ypos;				// x and y
	char animationStep;							// used for stepping through explosion
	char shield;										// 0 for normal, 1 for shield (behavior to be determined)
	signed int health;							// number of hits before death (decremented on each hit)
	int score;
	PlayerStat stat;								// used for game state
} PlayerR;

typedef struct {
	signed char xpos, ypos;				// x and y
	signed int dx1, dx2, dy1, dy2, longest, shortest, numerator, direction;
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

extern unsigned char g_Stringz[6][21];
extern unsigned char g_continue;
extern unsigned char g_level;
extern unsigned int g_bulletTimer;
extern unsigned int g_shotgunTimer;
extern unsigned int g_levelTimer;

extern void (*EnemyAI[MAX_LEVELS])(EnemyR* enemy);

BulletR* FreshBullet(BulletR (*bullet)[], unsigned int max);
void BulletAngle(BulletR* bullet, int xpos, int ypos, int angle);
void BulletTarget(BulletR* bullet, int xpos, int ypos, int xdest, int ydest);
void EnemyInit(void);
void GameInit(void);

#endif //__GAME_H__

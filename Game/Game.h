
#ifndef __GAME_H__
#define __GAME_H__

#define MAX_DANCE			6
#define MAX_EXPLOSION	5
#define MAX_ENEMIES		12

typedef enum {
	ALIVE,
	HIT,
	DEAD,
	ATTACK
} EnemyStat;

typedef struct {
	unsigned char xpos0, ypos0;
	unsigned char xpos, ypos;
	unsigned char width, height;
	int direction;
	char animationStep;
	char health;
	EnemyStat stat;
} EnemyR;

extern unsigned char g_spriteIdle[MAX_DANCE][50];
extern unsigned char g_spriteAttack[][50];
extern unsigned char g_explosion[MAX_EXPLOSION][196];
extern EnemyR g_enemies[MAX_ENEMIES];

void GameInit(void);

#endif //__GAME_H__

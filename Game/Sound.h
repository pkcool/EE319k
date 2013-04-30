
#ifndef __SOUND_H__
#define __SOUND_H__

#define SND_MOVE_LENGTH			549*2
#define SND_BULLET_LENGTH		2040*2
#define SND_DEATH_LENGTH			3377*2

extern unsigned char g_soundMove[SND_MOVE_LENGTH];
extern unsigned char g_soundBullet[SND_BULLET_LENGTH];
extern unsigned char g_soundDeath[SND_DEATH_LENGTH];

extern unsigned char (*g_soundArray)[];
extern unsigned long g_soundIndex;
extern unsigned long g_soundMax;

void SoundInit(void);
void PlaySound(void);

#endif // __SOUND_H__

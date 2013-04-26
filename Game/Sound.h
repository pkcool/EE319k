
#ifndef __SOUND_H__
#define __SOUND_H__

#define SND_BULLET_LENGTH 4435*2
#define SND_MOVE_LENGTH 2191*2

//extern unsigned char g_soundTheme[];
extern unsigned char g_soundMove[];
extern unsigned char g_soundShot[];

extern unsigned char *g_soundArray;
extern unsigned long g_soundIndex;
extern unsigned long g_soundMax;

void SoundInit(void);
void PlaySound(void);

#endif // __SOUND_H__
 
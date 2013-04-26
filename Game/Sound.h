
#ifndef __SOUND_H__
#define __SOUND_H__

#define SND_THEME_LENGTH 		9240*2
#define SND_MOVE_LENGTH			2998*2
#define SND_BULLET_LENGTH		3057*2

extern unsigned char g_soundTheme[SND_THEME_LENGTH];
extern unsigned char g_soundMove[SND_MOVE_LENGTH];
extern unsigned char g_soundBullet[SND_BULLET_LENGTH];

extern unsigned char (*g_soundArray)[];
extern unsigned long g_soundIndex;
extern unsigned long g_soundMax;

void SoundInit(void);
void PlaySound(void);

#endif // __SOUND_H__

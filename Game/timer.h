
#ifndef __TIMER_H__
#define __TIMER_H__

void Timer0AInit(void(*task)(void), unsigned short period);
void Timer0A_Handler(void);

#endif // __TIMER_H__

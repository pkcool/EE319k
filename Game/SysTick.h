
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

void SysTickInterrupt(void(*task)(void));
void SysTick_Init(unsigned long period);
void SysTick_IntEnable(void);

#endif // __SYSTICK_H__


#ifndef __SYSTICK_H__
#define __SYSTICK_H__

extern void SysTickIntHandler(void);
extern void SysTickInit(unsigned long period);
extern void SysTickInterruptEnable(void);

#endif // __SYSTICK_H__

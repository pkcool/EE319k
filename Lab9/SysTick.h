
#ifndef __SYSTICKINT_H__
#define __SYSTICKINT_H__

extern void SysTickIntHandler(void);
extern void SysTickIntEnable(void);
extern void SysTickInit(unsigned long period);

#endif // __SYSTICKINT_H__

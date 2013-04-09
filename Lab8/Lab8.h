#ifndef __LAB8_H__
#define __LAB8_H__

void SysTickIntHandler(void);
void Delay(unsigned long);
unsigned long periodToSysTick(unsigned long);
void init(void);

#endif // __LAB8_H__

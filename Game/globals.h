
#ifndef __GLOBALS_H_INCLUDED
#define __GLOBALS_H_INCLUDED

#define HEIGHT	23
#define WIDTH		31

#define NOP() do { } while(0);

extern volatile unsigned long g_flags;

void Delay(unsigned long ulCount);

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#endif // __GLOBALS_H_INCLUDED

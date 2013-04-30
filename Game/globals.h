
#ifndef __GLOBALS_H_INCLUDED
#define __GLOBALS_H_INCLUDED

#define HEIGHT	23
#define WIDTH		31

#define NOP() __nop(); __nop();

extern volatile unsigned long g_step;
extern volatile unsigned long g_flags;
#define FLAG_BUTTON_UP			0
#define FLAG_BUTTON_DOWN		1
#define FLAG_BUTTON_LEFT		2
#define FLAG_BUTTON_RIGHT		3
#define FLAG_BUFFER_READY		4
#define FLAG_ADC_VALUE			5

void Delay(unsigned long ulCount);
unsigned int abs(signed int a);
void IntToString(unsigned int a, unsigned char *str, int length);

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#endif // __GLOBALS_H_INCLUDED

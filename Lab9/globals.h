
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define CLOCK_RATE              100000
#define LENGTH									2170

#define NOP() do { } while(0);

extern unsigned long gFlags;
#define FLAG_CLOCK_TICK         0           // A timer interrupt has occurred
#define FLAG_ADC_VALUE          1           // There is a new value in the ADC

extern unsigned long gSystemClockFrequency;

#endif // __GLOBALS_H__

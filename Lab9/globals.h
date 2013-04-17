
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// standard ASCII symbols
#define BACKSPACE               0x8  // back up one character
#define TAB                     0x9  // move cursor right
#define HOME                    0xA  // move cursor all the way left on current line
#define NEWLINE                 0xD  // move cursor all the way left on next line
#define RETURN                  0xD  // move cursor all the way left on next line
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

#define LENGTH									2170

#define NOP() do { } while(0);

extern unsigned long gErrors;
extern unsigned long gFlags;
#define FLAG_CLOCK_TICK         0           // A timer interrupt has occurred
#define FLAG_ADC_VALUE          1           // There is a new value in the ADC
#define FLAG_JOB								2						// Button selection job type
#define FLAG_SELECT							3						// Selection confirmed
#define FLAG_FIFO_FULL					4						// FIFO Buffer full

extern unsigned long gSystemClockFrequency;

#endif // __GLOBALS_H__

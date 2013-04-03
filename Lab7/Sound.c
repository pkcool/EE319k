
#include "Sound.h"
#include <lm3s1968.h>
#include <math.h>
#include "DAC.h"
#include "systick.h"
#include "systickints.h"

const unsigned long SAMPLE_RATE = 128;
unsigned int sinArray[SAMPLE_RATE];
volatile unsigned long index = 0;

void Sound_Init() {
	int sinResult;
	double pi = 4.0 * atan(1.0);
  int i;
	for (i = 0; i < SAMPLE_RATE; i++) {
		sinResult = (int)(4.0*sin(2.0*pi*i/SAMPLE_RATE)+4.49);
		sinArray[i] = sinResult;
	}
}

void Sound_Off(void) {
	SysTickPeriodSet(0);
}

void Sound_Play(unsigned int n) {
	unsigned long note = Sound_Note_To_Frequency(n);
	
	unsigned long period = 0.75 * 50000000.0 / (SAMPLE_RATE*note);
	SysTickPeriodSet(period);
}

void Sound_Play_Timing(unsigned int note, unsigned long time) {
	unsigned long mult;
	if (note != 0) {
		Sound_Play(note);
	}
	for (mult = 500000; mult > 0; mult--) {
		for (; time > 0; time--) {
			// stupid wait
		}
	}
	index = 0;
}

unsigned long Sound_Note_To_Frequency(unsigned int n) {
	return pow(2.0,(n-50.0)/12.0)*440.0;
}

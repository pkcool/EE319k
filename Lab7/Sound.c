
#include "Sound.h"
#include <lm3s1968.h>
#include <math.h>
#include "DAC.h"
#include "SysTickInts.h"

const unsigned long SAMPLE_RATE = 100;

unsigned int sinArray[SAMPLE_RATE];

void Sound_Init() {
	int sinResult;
	double pi = 4.0 * atan(1.0);
  int i;
	for (i = 0; i < SAMPLE_RATE; i++) {
		sinResult = 4.5*sin(2.0*pi*i/SAMPLE_RATE)+4.0;
		sinArray[i] = sinResult;
	}
}

void Sound_Play(unsigned int n) {
	unsigned long note = Sound_Note_To_Frequency(n);	
	int i = 0;
	double delay = 1.0 /(SAMPLE_RATE*note) * 1000000000.0 / 20.0;
	while (i < SAMPLE_RATE) {
		DAC_Out(sinArray[i]);
		SysTick_Wait((int)delay);
		i += 1;
	}
}

unsigned long Sound_Note_To_Frequency(unsigned int n) {
	return pow(2.0,(n-49.0)/12.0)*440.0;
}

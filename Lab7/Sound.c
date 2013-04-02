
#include "Sound.h"
#include <lm3s1968.h>
#include <math.h>
#include "DAC.h"
#include "systick.h"

const unsigned long SAMPLE_RATE = 200;

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

void SysTick_Handler(void) {
	DAC_Out(sinArray[index]);
	index+=1;
	if (index >= SAMPLE_RATE) {
		index = 0;
	}
}

void Sound_Play(unsigned int n) {
	unsigned long note = Sound_Note_To_Frequency(n);
	
	unsigned long period = 50000000.0 / (SAMPLE_RATE*note);
	SysTickPeriodSet(period);
}

unsigned long Sound_Note_To_Frequency(unsigned int n) {
	return pow(2.0,(n-49.0)/12.0)*440.0;
}

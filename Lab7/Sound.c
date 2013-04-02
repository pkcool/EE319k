
#include "Sound.h"
#include <lm3s1968.h>
#include <math.h>
#include "DAC.h"

const unsigned long SAMPLE_RATE = 8000;
const unsigned long MHZ = 50000000;

signed int sinArray[SAMPLE_RATE];

void Sound_Init() {
	char sinResult;
	double pi = 4.0 * atan(1.0);
  int i;
	for (i = 0; i < SAMPLE_RATE; i++) {
		sinResult = sin(2*pi*i/SAMPLE_RATE);
		sinArray[i] = sinResult;
	}
}

void Sound_Play(unsigned char n) {
	unsigned long note = Sound_Note_To_Frequency(n);	
	int i,j;
	for (i = 0; i < SAMPLE_RATE; i++) {
		DAC_Out(sinArray[i]);
		j = note/SAMPLE_RATE*MHZ;
		while (j>0) { j--; }
	}
}

unsigned long Sound_Note_To_Frequency(unsigned char n) {
	return pow(2,(n-49)/12)+440;
}

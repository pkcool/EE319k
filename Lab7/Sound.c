#include <math.h>
#include <lm3s1968.h>
#include <math.h>
const unsigned long SAMPLE_RATE = 8000;

void Sound_Init() {
	signed int sinArray[SAMPLE_RATE];
	char sinResult;
	double pi = 4.0 * atan(1.0);
  int i;
	for (i = 0; i < SAMPLE_RATE; i++) {
		sinResult = sin(2*pi*i/SAMPLE_RATE);
		sinArray[i] = sinResult;
	} 
	// initialize data structures
}

void Sound_Play(unsigned char n) {
	// play sound
}

double Sound_Note_To_Frequency(unsigned char n) {
	return pow(2,(n-49)/12)+440;
}

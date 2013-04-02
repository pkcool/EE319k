
#include <math.h>
#include <lm3s1968.h>
#include <math.h>

void Sound_Init() {
	signed char sinArray[SAMPLERATE];
	char sinResult;
	double pi = 4.0 * atan(1.0);
  for (int i = 0; i < SAMPLERATE; i++) {
		sinResult = sin(2*pi*i/SAMPLERATE);
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

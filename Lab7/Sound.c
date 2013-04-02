
#include <math.h>
#include <lm3s1968.h>

void Sound_Init() {
	// initialize data structures
}

void Sound_Play(unsigned char n) {
	// play sound
}

double Sound_Note_To_Frequency(unsigned char n) {
	return pow(2,(n-49)/12)+440;
}

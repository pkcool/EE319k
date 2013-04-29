
#include "inc/lm3s1968.h"
#include "random.h"
#include "ADCDriver.h"


#include "inc/lm3s1968.h"
#include "random.h"
#include "ADCDriver.h"
#include "globals.h"

unsigned int MT[624];
unsigned int index = 0;

void RandomInit(unsigned long seed) {
    unsigned int i;
    index = 0;
    MT[0] = seed;
    for (i = 1; i < 624; i++) {
        MT[i] = (1812433253 * (MT[i-1] ^ (MT[i-1]>>30)) + i) & 0xFFFF;
    }
}

unsigned int RandomExtract(void) {
    unsigned int y;
    if (index == 0) {
				index = 0;
        RandomGenerate();
    }

    y = MT[index];
    y = y ^ (y>>11);
		y = y ^ ((y<<7) & 2636928640);
    y = y ^ ((y<<15) & 4022730752);
    y = y ^ (y>>18);

    index = (index+1) % 624;
    return y;
}

void RandomGenerate(void) {
    unsigned int i,y;
    for (i = 0; i < 624; i++) {
        y = (MT[i] & 0x80000000) + (MT[(i+1) % 624] & 0x7fffffff);
        MT[i] = MT[(i + 397) % 624] ^ (y>>1);
        if ((y%2) != 0) {
            MT[i] = MT[i] ^ 2567483615;
        }
    }
}

void RandomSort(char (*array)[], int size) {
	char i,j,k;
	for (i = size - 1; i > 0; i--) {
		j = RandomExtract()%i;
		k = (*array)[i];
		(*array)[i] = (*array)[j];
		(*array)[j] = k;
	}
}

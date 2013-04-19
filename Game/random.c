#include "random.h"

unsigned long g_random_seed = 4;

unsigned long RandomNumber(void) {
	g_random_seed = (g_random_seed * 1664525) + 1013904223;
	return g_random_seed;
}

void RandomSort(char (*array)[], int size) {
	char i,j,k;
	for (i = size - 1; i > 0; i--) {
		j = RandomNumber()%i;
		k = (*array)[i];
		(*array)[i] = (*array)[j];
		(*array)[j] = k;
	}
}


#ifndef __RANDOM_H_INCLUDED
#define __RANDOM_H_INCLUDED

void RandomInit(unsigned long seed);
unsigned int RandomExtract(void);
void RandomGenerate(void);
void RandomSort(char (*array)[], int size);

#endif // __RANDOM_H_INCLUDED

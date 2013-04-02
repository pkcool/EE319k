

extern const unsigned long SAMPLE_RATE;
extern unsigned int sinArray[];
extern volatile unsigned long index;

void SysTick_Handler(void);

void Sound_Init(void);

void Sound_Play(unsigned int);

unsigned long Sound_Note_To_Frequency(unsigned int);


// Global variables
extern const unsigned long SAMPLE_RATE;
extern unsigned int sinArray[];
extern volatile unsigned long index;

// Turns sound off (sets period to 0)
void Sound_Off(void);

// Initialize sound array
void Sound_Init(void);

// Plays a note
// note will be converted to a frequency by the function
// only pass note number (ex. 0x49 for C)
void Sound_Play(unsigned int);

// Plays a note for a specified time
// Time is in milliseconds
void Sound_Play_Timing(unsigned int, unsigned long);

// Convert the note parameter to a frequency
// Should not be needed outside this class
unsigned long Sound_Note_To_Frequency(unsigned int);

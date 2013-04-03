#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "lm3s1968.h"
#include "Sound.h"

//0x2a - UP, 0x20 - DOWN, 0x26 - LEFT, 0x25 - RIGHT, 0x1e - SELECT
unsigned int note;
void Piano_In (void) {
	note = GPIO_PORTG_DATA_R & 0xF8;
	if (note == 0xF0) {	// UP
		Sound_Play(0x2a);
	} else if (note == 0xE8) {	// DOWN
		Sound_Play(0x20);
	} else if (note == 0xD8) {	// LEFT
		Sound_Play(0x26);
	} else if (note == 0xB8) {	// RIGHT
		Sound_Play(0x25);
	} else if (note == 0x78) {	// SELECT
		Sound_Play(0x1e);
	} else {
		Sound_Off();
	}
}

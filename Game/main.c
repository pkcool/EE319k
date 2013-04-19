
#include <stdio.h>
#include <time.h>

#include "drivers/rit128x96x4.h"

#include "globals.h"
#include "random.h"
#include "maze.h"

unsigned char g_frame[6144];

int main(void) {
	int x,y,i,j,k;
	unsigned char data;
	RIT128x96x4Init(3500000);
	MazeInit();
	x = 0;
	y = 0;
	for (j = 0; j < HEIGHT; j++) {
		for (i = 0; i < WIDTH; i++) {
			if (grid[j][i]&0x1) {
				data = 0xF;
			} else {
				data = 0x0;
			}
			putPixel(x++,y, 0xF);
			putPixel(x++,y, data);
			putPixel(x++,y, data);
			putPixel(x++,y, 0xF);
		}
		x = 0;
		y++;
		for (k = 0; k < 2; k++) {
			for (i = 0; i < WIDTH; i++) {
				if (grid[j][i]&0x8) {
					data = 0xF;
				} else {
					data = 0x0;
				}
				putPixel(x++,y, data);
				putPixel(x++,y, 0x0);
				putPixel(x++,y, 0x0);
				if (grid[j][i]&0x4) {
					data = 0xF;
				} else {
					data = 0x0;
				}
				putPixel(x++,y, data);
			}
			x = 0;
			y++;
		}
		for (i = 0; i < WIDTH; i++) {
			if (grid[j][i]&0x2) {
				data = 0xF;
			} else {
				data = 0x0;
			}
			putPixel(x++,y, 0xF);
			putPixel(x++,y, data);
			putPixel(x++,y, data);
			putPixel(x++,y, 0xF);
		}
		x = 0;
		y++;
	}
	RIT128x96x4ImageDraw(&g_frame, 0, 0, 128, 96);
}

void putPixel(unsigned int x, unsigned int y, unsigned char data) {
	printf("%i %i\n", x, y);
	if (x >= 0 && x/2 < WIDTH && y >= 0 && y < HEIGHT) {
		printf("HEY NO! %i %i\n", x, y);
		return;
	}
	if ((x%2) == 0) {
		g_frame[y*64+x/2] &= 0xF0;
		g_frame[y*64+x/2] |= data;
	} else {
		g_frame[y*64+x/2] &= 0x0F;
		g_frame[y*64+x/2] |= data << 4;
	}
}
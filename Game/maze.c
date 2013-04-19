
#include <stdio.h>

#include "graphics.h"
#include "globals.h"
#include "random.h"
#include "maze.h"

#define NORTH	1
#define SOUTH	2
#define EAST	4
#define WEST	8

char kDX[4] = {0, 0, 1, -1};
char kDY[4] = {-1, 1, 0, 0};
char opposite[4] = {1, 0, 3, 2};

unsigned char grid[HEIGHT][WIDTH];

void MazeInit(void) {
	int x, y;
	for (y = 0; y < HEIGHT; y++) {		
		for (x = 0; x < WIDTH; x++) {
			grid[y][x] = 0;
			/*if (y == 0) {
				grid[y][x] |= NORTH;
			}
			if (y == (HEIGHT-1)) {
				grid[y][x] |= SOUTH;
			}
			if (x == 0) {
				grid[y][x] |= WEST;
			}
			if (x == (WIDTH-1)) {
				grid[y][x] |= EAST;
			}*/
		}
	}
	MazeGen(1, 1);
}

void MazeGen(int cur_x, int cur_y) {
	int i, new_x, new_y;
	char dir[4] = {0, 1, 2, 3};
	RandomSort(&dir, 4);
	for (i = 0; i < 4; i++) {
		new_x = cur_x + kDX[dir[i]];
		new_y = cur_y + kDY[dir[i]];
		if ((new_x >= 0) && (new_x <= (WIDTH-1)) && (new_y >= 0) && (new_y <= (HEIGHT-1)) && (grid[new_y][new_x] == 0)) {
			grid[cur_y][cur_x] |= 1<<dir[i];
			grid[new_y][new_x] |= 1<<opposite[dir[i]];
			MazeGen(new_x, new_y);
		}
	}
}

void MazePrint(void) {
	int x,y;
	unsigned char datum;
	unsigned char data[8] = {0xAA, 0xAA, 0xA0, 0x0A, 0xA0, 0x0A, 0xAA, 0xAA};
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			if ((grid[y][x]&0x1) > 0) {
				datum = 0x0;
			} else {
				datum = 0xA;
			}
			data[0] &= 0xA0;
			data[0] |= datum;
			data[1] &= 0x0A;
			data[1] |= (datum << 4);
			
			if ((grid[y][x]&0x8) > 0) {
				datum = 0x0;
			} else {
				datum = 0xA;
			}
			data[2] &= 0x0A;
			data[2] |= (datum << 4);
			data[4] &= 0x0A;
			data[4] |= (datum << 4);
			
			if ((grid[y][x]&0x4) > 0) {
				datum = 0x0;
			} else {
				datum = 0xA;
			}
			data[3] &= 0xA0;
			data[3] |= datum;
			data[5] &= 0xA0;
			data[5] |= datum;
			
			if ((grid[y][x]&0x2) > 0) {
				datum = 0x0;
			} else {
				datum = 0xA;
			}
			data[6] &= 0xA0;
			data[6] |= datum;
			data[7] &= 0x0A;
			data[7] |= (datum << 4);
			DrawImageFast(data, x*4, y*4, 4, 4);
			Delay(10000);
		}
	}
	data[0] = data[1] = data[6] = data[7] = 0x11;
	data[2] = data[4] = 0x1F;
	data[3] = data[5] = 0xF1;
	DrawImage(data, 1*4, 1*4, 4, 4);
	DrawImage(data, (WIDTH-2)*4, (HEIGHT-2)*4, 4, 4);
}

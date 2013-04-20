
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

/*
		FF FF
		FF FF
		FF FF
		FF FF
*/

void MazePrint(void) {
	int x,y;
	unsigned char datum;
	unsigned char data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00};
	unsigned char blank[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	ClearScreen();
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			// NORTH
			if ((grid[y][x]&0x1) > 0) {
				datum = 0x0;
			} else {
				datum = 0xFF;
			}
			data[1] = datum;
			data[3] = datum;
			
			// WEST
			if ((grid[y][x]&0x8) > 0) {
				datum = 0x0;
			} else {
				datum = 0xFF;
			}
			data[4] = datum;
			data[6] = datum;
			
			DrawImageFast(data, x*4, y*4, 4, 4);
		}
	}
	
	for (y = 0; y < HEIGHT; y++) {
		DrawImageFast(blank, WIDTH*4, y*4, 2, 4);
	}
	for (x = 0; x < WIDTH; x++) {
		DrawImageFast(blank, x*4, HEIGHT*4, 4, 2);
	}
	DrawImageFast(blank, WIDTH*4, HEIGHT*4, 2, 2);
}

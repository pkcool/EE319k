
#include <stdio.h>

#include "globals.h"
#include "random.h"
#include "maze.h"

char kDX[4] = {0, 0, 1, -1};
char kDY[4] = {-1, 1, 0, 0};
char opposite[4] = {1, 0, 3, 2};

unsigned char grid[HEIGHT][WIDTH];

void MazeInit(void) {
	MazeGen(13,13);
}

void MazeGen(unsigned char cur_x, unsigned char cur_y) {
	char i, new_x, new_y;
	char dir[4] = {0, 1, 2, 3};
	RandomSort(&dir, 4);
	for (i = 0; i < 4; i++) {
		new_x = cur_x + kDX[dir[i]];
		new_y = cur_y + kDY[dir[i]];
		if ((new_x >= 0 && new_x <= (WIDTH-1)) && (new_y >= 0 && new_y <= (HEIGHT-1)) && (grid[new_y][new_x] == 0)) {
			grid[cur_y][cur_x] |= 1<<dir[i];
			grid[new_y][new_x] |= 1<<opposite[dir[i]];
			MazeGen(new_x, new_y);
		}
	}
}
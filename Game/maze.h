
#ifndef __MAZE_H_INCLUDED
#define __MAZE_H_INCLUDED

unsigned char grid[HEIGHT][WIDTH];

void MazeInit(void);
void MazeGen(unsigned char x, unsigned char y);

#endif // __MAZE_H_INCLUDED

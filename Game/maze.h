
#ifndef __MAZE_H_INCLUDED
#define __MAZE_H_INCLUDED

extern unsigned char grid[HEIGHT][WIDTH];

void MazeInit(void);
void MazeGen(int x, int y);
void MazePrint(void);

#endif // __MAZE_H_INCLUDED


#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"
#include "graphics.h"
#include <math.h>

unsigned char g_frame[6144];
typedef struct { 
	char x,y;
} Point;
signed int sinarr[24] = {0, 33, 64, 91, 111, 124, 128, 124, 111, 91, 64, 33, 0, -33, -64, -91, -111, -124, -128, -124, -111, -91, -64, -33};
signed int cosarr[24] = {128, 124, 111, 91, 64, 33, 0, -33, -64, -91, -111, -124, -128, -124, -111, -91, -64, -33, 0, 33, 64, 91, 111, 124};


void ClearScreen(void) {
	int i;
	for (i = 0; i < 6144; i++) {
		g_frame[i] = 0;
	}
}

// set a SINGLE pizel
// 	sets the pixel corresponding to the x, y location
// 	to the lower four bits of data
void SetPixel(unsigned int x, unsigned int y, 
							unsigned char data)
{
	if ((x < 128) && (y < 96)) {
		if ((x%2) == 0) {
			g_frame[y*64+x/2] &= 0x0F;
			g_frame[y*64+x/2] |= (data&0x0F) << 4;
		} else {		
			g_frame[y*64+x/2] &= 0xF0;
			g_frame[y*64+x/2] |= (data&0x0F);
		}
	}
}

// draw a line from x0, y0 to x1, y1
// 	line is NOT antialiased
void DrawLine(unsigned int x0, unsigned int y0, 
		unsigned int x1, unsigned int y1,
		unsigned char color)
{
	signed int tmp, dx, dy, x, y, eps;
	if (x1 < x0) {
		tmp = x0; x0 = x1; x1 = tmp;
		tmp = y0; y0 = y1; y1 = tmp;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	y = y0;
	x	= x0;
	eps = 0;
	if (y0 <= y1) {
		for (; x < x1; x++ ) {
			SetPixel(x,y,color);
			eps += dy;
			if ( (eps << 1) >= dx )  {
				y++;
				eps -= dx;
			}
		}
	} else {
		for (; x < x1; x++ ) {
			SetPixel(x,y,color);
			eps += dy;
			if ( (eps << 1) <= -dx )  {
				y--;
				eps += dx;
			}
		}
	}
}

// draws an image to x, y of width and height
// 	if any of the nibbles are equal to 0x01
//  they will be treated as transparent
void DrawImage(unsigned char* data, unsigned int x, 
								unsigned int y, unsigned int width, 
								unsigned int height)
{
	int i,j;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width/2; i++) {
			if (data[j*width/2+i] == 0x11) {
				continue;
			}
			if ((data[j*width/2+i]&0x0F) == 0x01) {
				g_frame[(j+y)*64+x/2+i] &= 0x0F;
				g_frame[(j+y)*64+x/2+i] |= (data[j*width/2+i]&0xF0);
			} else if ((data[j*width/2+i]&0xF0) == 0x10) {
				g_frame[(j+y)*64+x/2+i] &= 0xF0;
				g_frame[(j+y)*64+x/2+i] |= (data[j*width/2+i]&0x0F);
			} else {
				g_frame[(j+y)*64+x/2+i] = data[j*width/2+i];
			}
		}
	}
}

void DrawImageFast(unsigned char* data, unsigned int x, 
								unsigned int y, unsigned int width, 
								unsigned int height)
{
	int i,j;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width/2; i++) {
			g_frame[(j+y)*64+x/2+i] = data[j*width/2+i];
		}
	}
}




void RotateImage(unsigned char* data, unsigned int x, 
								unsigned int y, unsigned int width, 
								unsigned int height, unsigned int angle, signed int scale)
{
	int i,j; 
	int newI, newJ, newI2, newJ2;
	int newM;
	int centerX = width/2;
	int centerY = height/2;
	signed int mat11 = (cosarr[angle%24])/8;
	signed int mat21 = (sinarr[angle%24])/8;
	signed int mat12 = -mat21;
	signed int mat22 = mat11;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width/2; i++) {
			
			newI = centerX + scale*(mat11*(i*2 - centerX) + mat12*(j - centerY))/128;
			newI2 = centerX + scale*(mat11*(i*2 + 1 - centerX) + mat12*(j - centerY))/128;
			newJ = centerY + scale*(mat21*(i*2 - centerX) + mat22*(j - centerY))/128;
			newJ2 = centerY + scale*(mat21*(i*2 + 1 - centerX) + mat22*(j - centerY))/128;
			
			newM = (data[j*width/2+i]&0xF0)/16;
			SetPixel(newI + x, newJ + y, newM);
			newM = (data[j*width/2+i]&0x0F);
			SetPixel(newI2 + x, newJ2 + y, newM);
		}
	}
}

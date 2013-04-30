
#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"
#include "graphics.h"
#include <math.h>

unsigned char g_frame[6144];
unsigned char g_charBuffer[8];
typedef struct { 
	char x,y;
} Point;
signed char sinarr[24] = {0, 33, 64, 91, 111, 124, 127, 124, 111, 91, 64, 33, 0, -33, -64, -91, -111, -124, -127, -124, -111, -91, -64, -33};
signed char cosarr[24] = {127, 124, 111, 91, 64, 33, 0, -33, -64, -91, -111, -124, -127, -124, -111, -91, -64, -33, 0, 33, 64, 91, 111, 124};


void ClearScreen(void) {
	int i;
	for (i = 0; i < 6144; i++) {
		g_frame[i] = 0;
	}
}

void DimScreen(void) {
	int i;
	for (i = 0; i < 6144; i++) {
		g_frame[i] = g_frame[i]*6/0xF;
	}
}

// set a SINGLE pizel
// 	sets the pixel corresponding to the x, y location
// 	to the lower four bits of data
void SetPixel(signed int x, signed int y, 
							unsigned char data)
{
	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 96)) {
		if ((x%2) == 0) {
			g_frame[y*64+x/2] &= 0x0F;
			g_frame[y*64+x/2] |= (data&0x0F) << 4;
		} else {		
			g_frame[y*64+x/2] &= 0xF0;
			g_frame[y*64+x/2] |= (data&0x0F);
		}
	}
}

void DrawImageFast(unsigned char* data, signed int x, 
								signed int y, unsigned int width, 
								unsigned int height)
{
	int i,j;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width/2; i++) {
			if ((x+i >= 0) && (x+i < 128) && (y+j >= 0) && (y+j < 96)) {
				g_frame[(j+y)*64+x/2+i] = data[j*width/2+i];
			}
		}
	}
}

void DrawString(unsigned char* pcStr, signed int x, signed int y) {
	unsigned long ulIdx1, ulIdx2;
	unsigned char ucTemp;

	while(*pcStr != 0) {
		ucTemp = *pcStr++ & 0x7f;
		if(ucTemp < ' ') {
			ucTemp = 0;
		} else {
			ucTemp -= ' ';
		}
		
		for(ulIdx1 = 0; ulIdx1 < 6; ulIdx1 += 2) {
			for(ulIdx2 = 0; ulIdx2 < 8; ulIdx2++) {
				g_charBuffer[ulIdx2] = 0;
				if(g_pucFont[ucTemp][ulIdx1] & (1 << ulIdx2)) {
					g_charBuffer[ulIdx2] = 0xf0;
				}
				if((ulIdx1 < 4) && (g_pucFont[ucTemp][ulIdx1 + 1] & (1 << ulIdx2))) {
					g_charBuffer[ulIdx2] |= 0x0f;
				}
			}

			DrawImageFast(g_charBuffer, x, y, 2, 8);
			x += 2;
		}
	}
}

void RotateImage(unsigned char* data, signed int x, 
								signed int y, unsigned int width, 
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

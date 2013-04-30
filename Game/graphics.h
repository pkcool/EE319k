
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

extern unsigned char g_frame[6144];

extern signed char sinarr[24];
extern signed char cosarr[24];

void ClearScreen(void);
void DimScreen(void);
void SetPixel(signed int x, signed int y, 
							unsigned char data);
void DrawLine(signed int x0, signed int y0, 
		signed int x1, signed int y1,
		unsigned char color);
void DrawImage(unsigned char* data, signed int x, 
								signed int y, unsigned int width, 
								unsigned int height);
void RotateImage(unsigned char* data, signed int x, 
									signed int y, unsigned int width, 
									unsigned int height, unsigned int angle,
									signed int scale);
void DrawString(unsigned char* string, signed int x, signed int y);
void DrawImageFast(unsigned char* data, signed int x, 
										signed int y, unsigned int width, 
										unsigned int height);

#endif // __GRAPHICS_H__

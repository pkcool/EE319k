
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

extern unsigned char g_frame[6144];

void ClearScreen(void);
void SetPixel(unsigned int x, unsigned int y, 
							unsigned char data);
void DrawLine(unsigned int x0, unsigned int y0, 
		unsigned int x1, unsigned int y1,
		unsigned char color);
void DrawImage(unsigned char* data, unsigned int x, 
								unsigned int y, unsigned int width, 
								unsigned int height);

void DrawImageFast(unsigned char* data, unsigned int x, 
										unsigned int y, unsigned int width, 
										unsigned int height);

#endif // __GRAPHICS_H__

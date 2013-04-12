#ifndef __LAB8_H__
#define __LAB8_H__

void SysTickIntHandler(void);
void Convert(int);
void Delay(unsigned long);
unsigned long periodToSysTick(unsigned long);
void init(void);

void LCD_Open(void);
void LCD_Clear(void);
void LCD_GoTo(long);
void LCD_OutString(char*);
void LCD_OutFix(long);

#endif // __LAB8_H__

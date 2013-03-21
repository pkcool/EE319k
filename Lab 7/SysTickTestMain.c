// SysTickTestMain.c
// Runs on LM3S1968
// Test the SysTick functions by activating the PLL, initializing the
// SysTick timer, and flashing an LED at a constant rate.
// Daniel Valvano
// February 22, 2012

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to the Arm Cortex M3",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2011
   Program 2.11, Section 2.6

 Copyright 2011 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// PG2 is an output for debugging

#include "SysTick.h"
#include "PLL.h"

#define GPIO_PORTG_DATA_R       (*((volatile unsigned long *)0x400263FC))
#define GPIO_PORTG_DIR_R        (*((volatile unsigned long *)0x40026400))
#define GPIO_PORTG_AFSEL_R      (*((volatile unsigned long *)0x40026420))
#define GPIO_PORTG_DEN_R        (*((volatile unsigned long *)0x4002651C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOG      0x00000040  // port G Clock Gating Control

int main(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG; // activate port G
  PLL_Init();               // set system clock to 50 MHz
  SysTick_Init();           // initialize SysTick timer
  GPIO_PORTG_DIR_R |= 0x04; // make PG2 out (built-in LED)
  GPIO_PORTG_AFSEL_R &= ~0x04;// disable alt funct on PG2
  GPIO_PORTG_DEN_R |= 0x04; // enable digital I/O on PG2
  while(1){
    GPIO_PORTG_DATA_R = GPIO_PORTG_DATA_R^0x04; // toggle PG2
//    SysTick_Wait(1);        // approximately 620 ns
//    SysTick_Wait(2);        // approximately 620 ns
//    SysTick_Wait(10000);    // approximately 0.2 ms
    SysTick_Wait10ms(1);    // approximately 10 ms
  }
}

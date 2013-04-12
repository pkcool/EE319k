; LCD.s
; Runs on LM3S1968
; EE319K lab 6 device driver for the LCD
; Valvano
; March 2, 2013 (Spring 2013 version)
;
;  size is 1*16
;  because we do not need to read busy, then we will tie R/W=ground
;  10k potentiometer (not the slide pot for Lab 8)
;	  one end of pot is +5V, 
;	  center of pot to pin 3 of LCD,
;	  other end of pot is ground
;  ground = pin 1	Vss
;  power  = pin 2	Vdd   +5V (EE319K LCDs)
;  pot	= pin 3	Vlc   connected to center of pot
;  PF4	= pin 4	RS	(1 for data, 0 for control/status)
;  ground = pin 5	R/W   (1 for read, 0 for write)
;  PF5	= pin 6	E	 (enable)
;  PF0	= pin 11   DB4   (4-bit data)
;  PF1	= pin 12   DB5
;  PF2	= pin 13   DB6
;  PF3	= pin 14   DB7
;16 characters are configured as 2 rows of 8
;addr  00 01 02 03 04 05 06 07 40 41 42 43 44 45 46 47


		EXPORT	LCD_Open
		EXPORT	LCD_Clear
		EXPORT	LCD_OutChar
		EXPORT	LCD_GoTo
		EXPORT	LCD_OutString
		EXPORT	LCD_OutChar
		EXPORT	LCD_OutDec
		EXPORT	LCD_OutFix
		EXPORT	LCD_Delay
		
;		IMPORT IO_HeartBeat
SYSCTL_RCGC2_R		EQU 0x400FE108
SYSCTL_RCGC2_GPIOG	EQU 0x00000040   ; port G Clock Gating Control
SYSCTL_RCGC2_GPIOF	EQU 0x00000020   ; port F Clock Gating Control

GPIO_PORTF_DIR_R	EQU 0x40025400
GPIO_PORTF_AFSEL_R	EQU 0x40025420
GPIO_PORTF_DEN_R	EQU 0x4002551C
GPIO_PORTF_DATA_NIBBLE	EQU 0x4002503C	; 0x40025000 + 4*1 + 4*2 + 4*4 + 4*8
LCD_E			EQU 0x40025040	; 0x40025000 + 4*16
LCD_RS			EQU 0x40025080	; 0x40025000 + 4*32
LCD_10us		EQU 0x7D	; 125
VALUE_10000		EQU 0x2710	; 10000
	  AREA	|.text|, CODE, READONLY, ALIGN=2
	  THUMB
	  ALIGN		  


;--------------- outCsrNibble ------------------
; Sends 4 bits to the LCD control/status
; Input: R0 is 4-bit command, in bit positions 3,2,1,0 of R0
; Output: none
; This is a private function
; Invariables: This function must not permanently modify registers R4 to R11
outCsrNibble
	PUSH {R1-R2,LR}

	LDR	R1, =GPIO_PORTF_DATA_NIBBLE
	STR	R0, [R1]
	
	MOV	R0, #6 
	BL	LCD_Delay
	
	LDR	R1, =LCD_E
	MOV	R2, #0x10
	STR	R2, [R1]
	
	MOV	R0, #6
	BL	LCD_Delay	
	
	LDR	R1, =LCD_E
	MOV	R2, #0x00
	STR	R2, [R1]
	
	MOV	R0, #6
	BL	LCD_Delay
	
	POP {R1-R2,PC}


;---------------------outCsr---------------------
; Sends one command code to the LCD control/status
; Input: R0 is 8-bit command to execute
; Output: none
;* Entry Mode Set 0,0,0,0,0,1,I/D,S
;*	 I/D=1 for increment cursor move direction
;*		=0 for decrement cursor move direction
;*	 S  =1 for display shift
;*		=0 for no display shift
;*   Display On/Off Control 0,0,0,0,1,D,C,B
;*	 D  =1 for display on
;*		=0 for display off
;*	 C  =1 for cursor on
;*		=0 for cursor off
;*	 B  =1 for blink of cursor position character
;*		=0 for no blink
;*   Cursor/Display Shift  0,0,0,1,S/C,R/L,*,*
;*	 S/C=1 for display shift
;*		=0 for cursor movement
;*	 R/L=1 for shift to left
;*		=0 for shift to right
;*   Function Set   0,0,1,DL,N,F,*,*
;*	 DL=1 for 8 bit
;*	   =0 for 4 bit
;*	 N =1 for 2 lines
;*	   =0 for 1 line
;*	 F =1 for 5 by 10 dots
;*	   =0 for 5 by 7 dots 
; This is a private function
; Invariables: This function must not permanently modify registers R4 to R11
outCsr
	PUSH {R1-R3,LR}
	
	LDR	R1, =LCD_RS
	MOV	R2, #0x00
	STR	R2, [R1]
	
	MOV	R1, R0
	
	LSR	R0, R1, #4
	BL	outCsrNibble

	BIC	R0, R1, #0xF0
	BL	outCsrNibble
	
	MOV	R0, #9
	BL	LCD_Delay
	POP  {R1-R3,PC}

;---------------------LCD_Open---------------------
; initialize the LCD display, called once at beginning
; Input: none
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_Open 
	PUSH {LR}
		; save any registers that will be destroyed by pushing on the stack 
		; wait 20ms allowing the LCD to power up 
	MOV	R0, #2000
	BL	LCD_Delay
		; set direction register(s) so that the six pins are output signals to the LCD
	
	LDR R1, =SYSCTL_RCGC2_R
	LDR R0, [R1]
	ORR R0, R0, #(SYSCTL_RCGC2_GPIOG|SYSCTL_RCGC2_GPIOF) ; activate port F and port G 
	STR R0, [R1]                 
	NOP
	NOP                ; allow time to finish activating
	
	LDR R1, =GPIO_PORTF_DIR_R
	LDR R0, [R1]
	ORR R0, R0, #0x3F  ; PG2 output
	STR R0, [R1]
	LDR R1, =GPIO_PORTF_AFSEL_R    
	LDR R0, [R1]
	BIC R0, R0, #0x3F  ; no alt funct                              
	STR R0, [R1]
	LDR R1, =GPIO_PORTF_DEN_R       
	LDR R0, [R1]
	ORR R0, R0, #0x3F  ; enable PG2
	STR R0, [R1]
	
	LDR	R1, =LCD_RS
	MOV	R2, #0x00
	STR	R2, [R1]
	
		; outCsrNibble(0x03) (DL=1 8-bit mode) 
	MOV	R0, #0x03
	BL	outCsrNibble
		; blind cycle 5ms wait
	MOV	R0, #500
	BL	LCD_Delay
		; outCsrNibble(0x03) (DL=1 8-bit mode)
	MOV	R0, #0x03
	BL	outCsrNibble
		; blind cycle 100us wait
	MOV	R0, #10
	BL	LCD_Delay
		; outCsrNibble(0x03) (DL=1 8-bit mode)
	MOV	R0, #0x03
	BL	outCsrNibble
		; blind cycle 100us wait (not called for, but do it anyway)
	MOV	R0, #10
	BL	LCD_Delay
		; outCsrNibble(0x02)(DL=0 4-bit mode)
	MOV	R0, #0x02
	BL	outCsrNibble
		; blind cycle 100 us wait
	MOV	R0, #10
	BL	LCD_Delay
		; outCsr(0x28) // DL=s0 4-bit, N=1 2-line, F=0 5by7 dots
	MOV	R0, #0x28
	BL	outCsr
		; outCsr(0x14) // S/C=0 cursormove, R/L=1 shiftright
	MOV	R0, #0x14
	BL	outCsr
		; outCsr(0x06) // I/D=1 Increment, S=0 no displayshift
	MOV	R0, #0x06
	BL	outCsr
		; outCsr(0x0C) // D=1 displayon, C=0 cursoroff, B=0 blink off
	MOV	R0, #0x0C
	BL	outCsr
		; restore the registers by pulling off the stack
	POP {PC}


;---------------------LCD_OutChar---------------------
; sends one ASCII to the LCD display
; Input: R0 (call by value) letter is 8-bit ASCII code
; Outputs: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11===+++
LCD_OutChar
	PUSH {R1-R3,LR}
	LDR	R1, =LCD_RS
	MOV	R2, #0x20
	STR	R2, [R1]
	
	MOV	R1, R0
	
	LSR	R0, R1, #4
	BL	outCsrNibble
	
	BIC	R0, R1, #0xF0
	BL	outCsrNibble	

	MOV	R0, #9
	BL	LCD_Delay
	POP  {R1-R3,PC}

;---------------------LCD_Clear---------------------
; clear the LCD display, send cursor to home
; Input: none
; Outputs: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_Clear
	PUSH	{LR}

	LDR	R1, =LCD_RS
	MOV	R2, #0x00
	STR	R2, [R1]

	MOV	R0, #0x01
	BL	outCsr
	
	MOV	R0, #1640
	BL	LCD_Delay
	
	MOV	R0, #0x02
	BL	outCsr
	
	MOV	R0, #1640
	BL	LCD_Delay
	POP	{PC}


;-----------------------LCD_GoTo-----------------------
; Move cursor (set display address) 
; Input: R0 is display address (DDaddr) is 0 to 7, or 0x40 to 0x47 
; Output: none
; errors: it will check for legal address
;  0) save any registers that will be destroyed by pushing on the stack
;  1) go to step 3 if DDaddr is 0x08 to 0x3F or 0x48 to 0xFFFFFFFF
;  2) outCsr(DDaddr+0x80)	 
;  3) restore the registers by pulling off the stack
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_GoTo
	MOV	R1, R0
	ADD	R0, #0x80
	BICS	R1, #0x47
	BEQ	outCsr
	BX	LR

; ---------------------LCD_OutString-------------
; Output character string to LCD display, terminated by a NULL(0)
; Inputs:  R0 (call by reference) points to a string of ASCII characters 
; Outputs: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutString
	PUSH	{R4,LR}
	MOV	R1, R0
Load
	LDRB	R0, [R1]
	CMP	R0, #0
	BEQ	Null
	ADD	R1, R1, #1
	BL	LCD_OutChar
	B	Load
Null
	POP	{R4,PC}



;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number 
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH	{R4,LR}
	CMP	R0, #0
	BEQ	OutDec_Print_Zero
	MOV	R4, #10
	MOV	R3, #0
OutDec_Recur
	ADDS	R0, R0, #0
	BEQ	OutDec_Print
	SDIV	R2, R0, R4	; R2 = R0/10
	MUL	R1, R2, R4
	SUB	R1, R0, R1	; R1 = R0%10
	ADD	R1, R1, #0x30	; R1 = R1 + 48
	PUSH	{R1}
	ADD	R3, R3, #1
	MOV	R0, R2
	B	OutDec_Recur
OutDec_Print
	POP	{R0}
	BL	LCD_OutChar
	SUBS	R3, R3, #1
	BLE	OutDec_Ret
	B	OutDec_Print
OutDec_Print_Zero
	MOV	R0, #0x30
	BL	LCD_OutChar
OutDec_Ret
	POP	{R4,PC}


; -----------------------LCD_OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999 
; Inputs:  R0 is an unsigned 16-bit number
; Outputs: none
; E.g., R0=0,	then output "0.000 " 
;	   R0=3,	then output "0.003 " 
;	   R0=89,   then output "0.089 " 
;	   R0=123,  then output "0.123 " 
;	   R0=9999, then output "9.999 " 
;	   R0>9999, then output "*.*** "
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
; Deprecated - please avoid use

LCD_OutFix
	PUSH	{R4,LR}
	
	MOV	R1, #0
	PUSH	{R1}
	
	LDR	R1, =VALUE_10000
	CMP 	R0, R1
	BPL	OutFix_Star
	
	MOV	R4, #10
	MOV	R3, #0
OutFix_Recur
	ADDS	R0, R0, #0
	BEQ	OutFix_Pad
	SDIV	R2, R0, R4	; R2 = R0/10
	MUL	R1, R2, R4
	SUB	R1, R0, R1	; R1 = R0%10
	ADD	R1, R1, #0x30	; R1 = R1 + 48
	PUSH	{R1}
	ADD	R3, R3, #1
	CMP 	R3, #3
	BNE	OutFix_CONT
	MOV 	R0, #0x2E
	PUSH 	{R0}
	ADD	R3, R3, #1
OutFix_CONT
	MOV	R0, R2
	B	OutFix_Recur
OutFix_Pad
	CMP 	R3, #5
	BGE	OutFix_Print
	CMP 	R3, #3
	BNE	OutFix_Cont
	MOV 	R0, #0x2E
	PUSH	{R0}
	ADD	R3, R3, #1
OutFix_Cont
	MOV	R0, #0x30
	PUSH	{R0}
	ADD	R3, R3, #1
	B	OutFix_Pad	
OutFix_Print
	POP	{R0}
	CMP	R0, #0
	BEQ	OutFix_Ret
	BL	LCD_OutChar
	B	OutFix_Print
OutFix_Star
	MOV	R0, #0x2A
	PUSH	{R0}
	MOV	R0, #0x2A
	PUSH	{R0}
	MOV	R0, #0x2A
	PUSH	{R0}
	MOV	R0, #0x2E
	PUSH	{R0}
	MOV	R0, #0x2A
	PUSH	{R0}
	BL	OutFix_Print
OutFix_Ret
	POP	{R4,PC}


; -----------------------LCD_Delay-----------------------
; Executes a blind wait for the time specified * 10 us
; Inputs:  R0 is an unsigned 16-bit number
; Outputs: none
; E.g., R0 = 50  -> blind wait for 500 us
;	R0 = 500 -> blind wait for 5 ms
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_Delay
	PUSH	{LR}
	LDR	R1, =LCD_10us
	MOV	R2, R0
Delay_Inner
	SUBS	R2, R2, #1
	BNE	Delay_Inner
Delay_Outer
	MOV	R2, R0
	SUBS	R1, R1, #1
	BEQ	Delay_Done
	B	Delay_Inner
Delay_Done
	POP	{PC}
	ALIGN					; make sure the end of this section is aligned
	END					; end of file
	
Lab 7. Digital Piano using a Digital to Analog Converter 
======

##Index
* [Preparation](#Preparation)
* [Purpose](#purpose)
* [Programming Requirements](#programming_requirements)
* [System Requirements](#system_requirements)
* [Procedure](#procedure)
* [Demonstration](#demonstration)
* [Deliverables](#deliverables)

##Preparation<a id="preparation"></a>
* Read Sections 9.1, 9.2, 9.4, 9.6, 10.1, 10.2 and 10.3, starter file ``PeriodicSysTickInts_1968``
* Download http://users.ece.utexas.edu/~valvano/Starterfiles/Dac.xls

##Purpose<a id="purpose"></a>
There are three objectives for this lab:

* To learn about DAC conversion
* To understand how digital data stored in a computer could be used to represent sounds and music
* To study how the DAC can be used to create sounds

##Programming Requirements<a id="programming_requirements"></a>
All software for this lab must be written in C. You can debug your code in the simulator but your final code must run on the board with a DAC circuit. Keil uVision4 projects in C are a little different than the assembly projects used for Labs 1 to 6. The project configuration and the ``startup.s`` file are different. Therefore, please start with one of the C starter files, like ``PeriodicSysTickInts_1968``, to generate your Lab 7 software. 

##System Requirements<a id="system_requirements"></a>
Most digital music devices rely on high-speed DAC converters to create the analog waveforms required to produce high-quality sound. In this lab you will create a very simple sound generation system that illustrates this application of the DAC. Your goal is to create an embedded system that plays three notes, which will be a digital piano with three keys. The first step is to design and test a 4-bit **binary-weighted** DAC, which converts 4 bits of digital output from the LM3S1968 to an analog signal. You are free to design your DAC with a precision of more than 4 bits. You will convert the four digital bits to an analog output using a simple resistor network. During the static testing phase, you will connect the DAC analog output to your voltmeter and measure resolution, range, precision and accuracy. During the dynamic testing phase you will connect the DAC output to headphones, and listen to sounds created by your software. It doesn’t matter what range the DAC is, as long as there is an approximately linear relationship between the digital data and the speaker current. The performance score of this lab is not based on loudness, but sound quality. The quality of the music will depend on both hardware and software factors. The precision of the DAC, external noise and the dynamic range of the speaker are some of the hardware factors. Software factors include the DAC output rate and the number of data points stored in the sound data. You can create a 3k resistor from two 1.5k resistors. You can create a 6k resistor from two 12k resistors.

The second step is to design a low-level device driver for the DAC. Remember, the goal of a device driver is to separate what the device does from how it works. “What it does” means the general descriptions and function prototypes of ``DAC_Init`` and ``DAC_Out`` that are placed in ``DAC.h``. “How it works” means the implementations of ``DAC_Init`` and ``DAC_Out`` that will be placed in ``DAC.c``. The third step is to design a low-level device driver for the three keys of the piano. For example, if you could create public functions ``Piano_Init`` and ``Piano_In``, where ``Piano_In`` returns a logical key code for the pattern of keys that are pressed. You may design this driver however you wish, but the goal is to abstract the details how it works (which port, which pin) from what it does (which key pressed). The fourth step is to organize the sound generation software into a device driver. You will need a data structure to store the sound waveform. You are free to design your own format, as long as it uses a formal data structure. Compressed data occupies less storage, but requires runtime calculation. Although you will be playing only three notes, the design should allow additional notes to be added with minimal effort. For example, if you could create public functions ``Sound_Init`` and ``Sound_Play(note)``, where the parameter note specifies the frequency (pitch) of the sound. For example, calling ``Sound_Play(Off)`` makes it silent and calling ``Sound_Play(C)`` plays the note C. A background thread within the sound driver implemented with SysTick interrupts will fetch data out of your music structure and send them to the DAC. The last step is to write a main program that links the modules together creating the digital piano.

You must write the entire code in C. In addition, if you perform the extra credit, it too should be implemented in C.

##Procedure<a id="procedure"></a>
1. Draw the circuit required to interface the binary-weighted DAC to the LM3S1968. Design the DAC converter using a simple resistor-adding technique. A 4-bit binary-weighted DAC uses resistors in a 1/2/4/8 resistance ratio. Select values in the 1.5 kΩ to 240 kΩ range. For example, you could use 1.5 kΩ, 3 kΩ, 6 kΩ, and 12 kΩ. Notice that you could create double/half resistance values by placing identical resistors in series/parallel. It is a good idea to email your design to your TA and have him/her verify your design before you build it. You can solder 24 gauge solid wires to the audio jack to simplify connecting your circuit to the headphones. Plug your headphones into your audio jack and use your ohmmeter to determine which two wires to connect. You have the option of connecting just the left, just the right, or both channels of the headphones. Draw interface circuits for three switches, which will be used for the piano keyboard.

2. Write the C language device driver for the DAC interface. Include at least two functions that implement the DAC interface. For example, you could implement the function ``DAC_Init()`` to initialize the DAC, and the function ``DAC_Out``to send a new data value to the DAC. Place all code that accesses the DAC in a separate ``DAC.c`` code file. Add a ``DAC.h`` header file with the prototypes for public functions. Describe how to use a module in the comments of the header file. Describe how the module works, how to test the module, and how to change module in the comments of the code file.

3. Begin with the static testing of the DAC. You will write a simple main program to test the DAC, similar in style as Program 7.1. You are free to debug this system however you wish, but you must debug The DAC module separately. You should initially debug your software in the simulator (Figure 7.9). You can single step this program, comparing digital Data to the analog voltage at the Vout without the speaker attached (i.e., left side of Figure 7.1).
```C
#include "DAC.h"
int main(void) { 
        unsigned long Data; // 0 to 15 DAC output 
        PLL_Init(); // like Program 4.6 in the book, except make it to 50 MHz 
        DAC_Init(); 
        for(;;) { 
            DAC_Out(Data); 
            Data = 0x0F&(Data+1); 
        }
} 
```
Using Ohm’s Law and fact that the digital output voltages will be approximately 0 and 3.3 V, make a table of the theoretical DAC voltage and as a function of digital value (without the speaker attached). Calculate resolution, range, precision and accuracy. Complete Table 7.2 and attach it as a deliverable.

4. Design and write the piano keyboard device driver software. These routines facilitate the use of the three piano keys. Include at least two functions that implement the piano keyboard interface. For example, you could implement the function ``Piano_Init()`` to initialize the switch inputs, and the function ``Piano_In`` that returns a logical key code for the pattern of switches that are pressed. Place all code that directly accesses the three switches in a separate ``Piano.c`` code file. Add a ``Piano.h`` header file with the prototypes for public functions. Add comments that describe what it does in the Piano.h file and how it works in the ``Piano.c`` file. 

5. Design and write the sound device driver software. The input to the sound driver is the pitch of the note to play. SysTick interrupts will be used to set the time in between outputs to the DAC. Add minimally intrusive debugging instruments to allow you to visualize when interrupts are being processed. Include at least two functions that implement the sound output. For example, you could implement the function ``Sound_Init()`` to initialize the data structures, calls ``DAC_Init``, and initializes the SysTick interrupt. You could implement a function ``Sound_Play(note)`` that starts sound output at the specified pitch. Place all code that implements the waveform generation in a separate Sound.c code file. Add a Sound.h header file with the prototypes for public functions. Add comments that describe what it does in the ``Sound.h`` file and how it works in the ``Sound.c`` file.  One approach to debugging is to attempt to create a sine wave with a constant frequency as shown in Figure 7.10 without any switch input. Just run the SysTick periodic interrupts and output one DAC value each interrupt. The toggling digital line shows you the interrupts are happening, and the top sine wave shows your table and DAC output are working.

6. Write a main program to implement the three-key piano. Make a heartbeat connected to an LED so you can see your program is running. Document clearly the operation of the routines. Figure 7.11 shows a possible data flow graph of the music player. Debug the system first in the simulator then on the real LM3S1968 with an oscilloscope. Take a photograph of the scope traces (like Figure 7.10) to capture the waveform generated by your digital piano. When no buttons are pressed, the output will be quiet. When Button 1 is pressed, output a sine wave at one frequency. When Button 2 is pressed, output a sine wave at a second frequency. When Button 3 is pressed, output a sine wave at a third frequency. Only one button will be pressed at a time. The sound lasts until the button is released.

#Demonstration<a id="demonstration"></a>
You should be able to demonstrate the three notes. Be prepared to explain how your software works. You should be prepared to discuss alternative approaches and be able to justify your solution. 

* How is the data collected?
* How does the DAC work? (design a DAC with 5 to 10 bits)
* What is the range, resolution and precision?
* What is the frequency supposed to be? (Prove using calculations)
* Be able to attach your DAC output to the oscilloscope and demonstrate correct operation.
* If the desired frequency is f, and there are n samples in the sine wave table, what SysTick interrupt period would you use?
* This lab mentions 32 samples per cycle. Increasing the DAC output rate and the number of points in the table is one way of smoothing out the “steps” that in the DAC output waveform. If we double the number of samples from 32 to 64 to 128 and so on, keeping the DAC precision at 4-bit, will we keep getting a corresponding increase in quality of the DAC output waveform?

#Deliverables<a id="deliverables"></a>
1. Circuit diagram showing the DAC and any other hardware used in this lab, PCB Artist 
2. Software Design 
 * Draw pictures of the data structures used to store the sound data 
 * If you organized the system different than Figure 7.11 and 7.12, then draw its data flow and call graphs 
3. A picture of the dual scope (part g) like Figures 7.10 7.13, or 7.15. 
4. Measurement Data 
 * Show the theoretical response of DAC voltage versus digital value (part c, Table 7.2) 
 * Show the experimental response of DAC voltage versus digital value (part c, Table 7.2) 
 * Calculate resolution, range, precision and accuracy 
5. Final version of the music playing software (intermediate testing software is not required) 


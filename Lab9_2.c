/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/24/2021
* Project: Lab 9
* File: Lab9_2.c
* Description: .c file for lab 9
**************************************************************************************/

#include "Lab9_Functions.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init_interrupt();                       //initializes systick interrupt
	__enable_irq();                                 //enables interrupt

	sevenSegment_Init();                            //initializes seven segment display

while(1){
    if(flag){                                       //checks flag
     if(count==10)count=0;                          //checks if count is 10,sets count to 0
     P4->OUT = 0;                                   //clears output
     segmentNumber();                               //displays seven segment number
     flag = 0;                                      //sets flag to 0
}
}
}
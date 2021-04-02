/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/24/2021
* Project: Lab 9
* File: Lab9_3.c
* Description: .c file for lab 9
**************************************************************************************/

#include "Lab9_Functions.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	sevenSegment_Init();                            //initializes seven segment display
	setupPort6Interrupt();                          //sets up port 6 interrupt
	NVIC->ISER[1]=1<<((PORT6_IRQn)&31);             //sets up port 6 interrupt
	__enable_irq();                                 //enables interrupt

	segmentNumber();                                //displays 0 first

	 while(1){
	      ;                                         //interrupt run in backround
	 }
}

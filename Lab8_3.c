/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 7
* File: Lab8_3.c
* Description: Program takes a user input and uses it to control PWM
**************************************************************************************/

#include "Lab8_Functions.h"
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	keypad_init();
	TimerA_init();                    // Call initialization functions for functionality
	uint8_t pressed = 0;

	 while(1){
	     do{
	     pressed = Read_Keypad();
	     }while(pressed==0 || pressed== 10 || pressed == 12);
	            if(pressed == 11)pressed = 0;
	            TimerA_setMotorSpeed(pressed);
	            }
	        }
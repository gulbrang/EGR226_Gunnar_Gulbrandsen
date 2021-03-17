/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 6
* File: Lab7_1.c
* Description: Initiated LCD for command/print
**************************************************************************************/

#include "Lab7_Functions.h"


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	LCD_init();
}


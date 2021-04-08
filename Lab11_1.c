/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/7/2021
* Project: Lab 11
* File: Lab9_Functions.c
* Description: Lab 11 part 1
**************************************************************************************/

#include "Lab11_Functions.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	TimerA_init();
	TimerA_setPulses();

}

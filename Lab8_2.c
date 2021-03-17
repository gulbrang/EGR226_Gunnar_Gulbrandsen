/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 7
* File: Lab8_2.c
* Description: Function controlled motor using PWM and TimerA
**************************************************************************************/
#include "Lab8_Functions.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	uint8_t dutyCycle=1;
	TimerA_init();

	while(1){
	    TimerA_setMotorSpeed(dutyCycle);
	}
}
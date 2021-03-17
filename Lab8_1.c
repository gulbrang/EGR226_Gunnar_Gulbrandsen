/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 8
* File: Lab8_1.c
* Description: Function controls PWM of DC motor through SysTick Delay
**************************************************************************************/

#include "Lab8_Functions.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	  P1->SEL0 &= ~BIT6; // configure P1.6 GPIO
	  P1->SEL1 &= ~BIT6;
	  P1->DIR |= BIT6; // make P1.6 output

	  uint8_t dutyCycle=50;

	         while(1){
	             P1->OUT |= BIT6;               //pin set high
	             systickPWM_High(dutyCycle);    //delay on
	             P1->OUT &= ~BIT6;              //pin set low
	             systickPWM_Low(dutyCycle);     //delay off
}
}

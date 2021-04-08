/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/7/2021
* Project: Lab 11
* File: Lab9_Functions.c
* Description: Lab11 part 2
**************************************************************************************/

#include "Lab11_Functions.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    NVIC->ISER[0] = 1<<((TA0_0_IRQn)&31);          // Enable interrupt in NVIC vector
    __enable_irq();                                      // Enable global interrupt


    TimerA_init();
    TimerA_capture();

    while (1) {
            ;
}
}
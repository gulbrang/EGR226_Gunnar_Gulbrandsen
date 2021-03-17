/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 6
* File: Lab7_3.c
* Description: Function scrolled text across the first line of the LCD from right to 
* left then continued to continously loop the text
**************************************************************************************/

#include "Lab7_Functions.h"

void main(void)
{
  char scroll[20]="Laboratory Over";

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    LCD_init();

    scrollLeft(scroll);             //scrolls string across display
}

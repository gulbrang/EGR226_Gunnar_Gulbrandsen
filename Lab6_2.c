/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/3/2021
* Project: Lab 6
* File: Lab6_2.c
* Description: The program detects the * and # key presses and do not allow them to be
* entered into the numerical code. As well as use the # key press to signify the termination
* of the entry. The program detected if less than 4 entries were entered as well as collected
* entries until the # was press. If press the program printed the last 4 valid entries.
**************************************************************************************/

#include "msp.h"
#include <stdio.h>
#include "Lab6_Functions.h"


int main (void)
 {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;       // stop watchdog timer
    keypad_init();                                   // Call initialization functions for functionality

    entry pinCode;

 while(1){
         pinCode = keypad_PIN();
         Print_Keys_Code(pinCode);
        }
 }
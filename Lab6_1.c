/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/3/2021
* Project: Lab 6
* File: Lab6_1.c
* Description: prompted the user to press a key on the keypad as well as read the keypad
*  and print the number of the key that was pressed to the CCS console.
**************************************************************************************/

#include "msp.h"
#include <stdio.h>
#include "Lab6_Functions.h"

int main (void)
 {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;       // stop watchdog timer
    keypad_init();                                   // Call initialization functions for functionality
    uint16_t pressed = 0;

    printf("Press the keypad to take in an input\n");

 while(1){
     do{
     pressed = Read_Keypad();
     }while(pressed==0);
            Print_Keys(pressed);
            }
        }
/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 6
* File: Lab7_2.c
* Description: Function printed four strings each on seperate lines and centered on
* an LCD
**************************************************************************************/

#include "Lab7_Functions.h"

void main(void)
{
  char firstName[16]="Gunnar";
  char lastName[16]="Gulbrandsen";
  char Class[16]= "EGR";
  char section[16]="226";

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    LCD_init();                                 //initiate LCD
    commandWrite(1);                            //clear display

    commandWrite(0x85);                         //moves cursor line 1
    printString(firstName);                     //prints firstName
    commandWrite(0xC2);                         //moves cursor line 2
    printString(lastName);                      //prints last name
    commandWrite(0x96);                         //moves cursor line 3
    printString(Class);                         //prints class
    commandWrite(0xD6);                         //moves cursor line 4
    printString(section);                       //prints section
}
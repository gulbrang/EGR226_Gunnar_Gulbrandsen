/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 2/18/2021
* Project: Lab 4
* File: main.c
* Description: This project project switches LED's on and off over 3 colors using a pushbutton
**************************************************************************************/

#include "msp.h"

void DebounceSwitch1();

int main(void) {
         P1->SEL1 &= ~2;         /* configure P1.1 as simple I/O */
         P1->SEL0 &= ~2;
         P1->DIR &= ~2;      /*P1.1 set as input */
         P1->REN |= 2;      /*P1.1 pull resistor enabled */
         P1->OUT |= 2;       /*Pull up/down is selected by P1-OUT */

         P2->SEL1 &= ~7;         /* configure P2.2-P2.0 as simple I/O */
         P2->SEL0 &= ~7;
         P2->DIR |= 7;           /* P2.2-2.0 set as output pin */
         P2->OUT &= 0x00;

while(1) {

int pressed = 0; //button presses checked

 while(pressed != 2) {                   //checks number of presses
       if(P1->IN & 2){                   //checks button input
           DebounceSwitch1();            //debounces switch
           pressed = pressed + 1;        // adds number of presses
           if(pressed == 1)P2->OUT |= 1; //checks if its the first press, Red LED turns on
           if(pressed == 2) P2->OUT &= ~1;//checks if its the second press, LED turns off
                  }
        }

 pressed=0;

 while(pressed != 2) {                   //checks number of presses
       if(P1->IN & 2){                   //checks button input
           DebounceSwitch1();            //debounces switch
           pressed = pressed + 1;        // adds number of presses
           if(pressed == 1)P2->OUT |= 2; //checks if its the first press, Green LED turns on
           if(pressed == 2) P2->OUT &= ~2;//checks if its the second press, LED turns off
                  }
        }

 pressed = 0;

 while(pressed != 2) {                   //checks number of presses
       if(P1->IN & 2){                   //checks button input
           DebounceSwitch1();            //debounces switch
           pressed = pressed + 1;        // adds number of presses
           if(pressed == 1)P2->OUT |= 4; //checks if its the first press, Green LED turns on
           if(pressed == 2) P2->OUT &= ~4;//checks if its the second press, LED turns off
                  }
        }
}
}

/****| DebounceSwitch1 | *****************************************
* Brief: This function looks at debouncing a switch and assuring
* that the input has stablized before moving on.
* param:
* N/A
* return:
* N/A
*************************************************************/

void DebounceSwitch1() {

uint16_t State = 0;         // Current debounce status

while(State!=0xfc00) {// indicates 0 level is stable for 10 consecutive calls
  State=(State<<1 | (P1IN & 0x2)>>1 | 0xf800);
  __delay_cycles(5);
}
}
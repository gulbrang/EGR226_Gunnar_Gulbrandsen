/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 2/18/2021
* Project: Lab 4
* File: Lab4_2.c
* Description: This project project switches LED's on and off over 3 colors using a pushbutton
**************************************************************************************/

#include "msp.h"

void delay1();
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
    char state;

    enum States{ //light sequencing states
        red,
        green,
        blue,
        start,
    };

    state = start; //start up state

 while(1){

    if((P1->IN & 2)) { //if pin is clicked
        DebounceSwitch1(); //debounce
       while((P1->IN & 2)==0){ //while pin is clicked

        switch(state){ //reads state

        case start: {
            state = red; //starts with red
        }

        case red: {
            if((P1->IN & 2)==0){ //checks if pin is pressed
                P2->OUT |= 1; //turns on red LED
                delay1(); //delays 1 second
                P2->OUT &= ~1; //turns off red LED
                state = green; //changes to green LED state
                break;
            }
            else{
                break;
            }
        }

        case green: {
            if((P1->IN & 2)==0){//checks if pin is pressed
                P2->OUT |= 2; //turns on red LED
                delay1();     //delays 1 second
                P2->OUT &= ~2;//turns off red LED
                state = blue; //changes to blue LED state
                break;
            }
            else{
                break;
            }
        }

        case blue: {
             if((P1->IN & 2)==0){ //checks if pin is pressed
                P2->OUT |= 4;     //turns on red LED
                delay1();         //delays 1 second
                P2->OUT &= ~4;    //turns off red LED
                state = red;      //changes to red LED state
                break;
            }
             else{
                 break;
        }
        }
}
}
}
}
}

/****| delay1 | *****************************************
* Brief: This function delay 1 second using the 32-bit timer
* or TIMER32 in an MSP
* param:
* N/A
* return:
* N/A
*************************************************************/

void delay1(void){
            TIMER32_1->LOAD = 3000000-1;  //set reload value
            TIMER32_1->CONTROL =0xC2;   //periodic wrapping mode, disable interrupt
            while((TIMER32_1->RIS & 1) == 0); //wait until raw interrupt flag
            TIMER32_1->INTCLR = 0; //clear raw interrupt flag
}

/****| DebounceSwitch1 | *****************************************
* Brief: This function looks at debouncing a switch and assuring
* that the input has stablized before moving on.
* param:
* N/A
* return:
* N/A
*************************************************************/
void DebounceSwitch1(){

uint16_t State = 0;         // Current debounce status

while(State!=0xfc00) {        // indicates 0 level is stable for 10 consecutive calls
  State=(State<<1 | (P1IN & 0x2)>>1 | 0xf800);
  __delay_cycles(5); //delays 5 seconds
}
}

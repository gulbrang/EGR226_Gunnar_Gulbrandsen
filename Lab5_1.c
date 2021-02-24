/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 2/18/2021
* Project: Lab 5
* File: main.c
* Description: This project project switches LED's on and off over 3 colors using a pushbutton
**************************************************************************************/

#include "msp.h"
#include <stdio.h>

void  SysTick_Init();
void SysTick_Delay(uint16_t d);
int Debounce1(uint16_t d);


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	     //Button
	     P3->SEL0 &= ~0x80; // configure P3.7 GPIO
	     P3->SEL1 &= ~0x80;
	     P3->DIR &= ~0x80; // make P3.7 input
	     P3->REN |= 0x80; // enable pull resistor on P3.7
	     P3->OUT |= 0x80; // P3.7 pull-down

	     //LED
	     P2->SEL0 &= ~0xE0; // configure P2.5-2.7 GPIO
	     P2->SEL1 &= ~0xE0;
	     P2->DIR |= 0xE0; // make P2.5-2.7 output
	     P2->OUT &= 0x00;

	     uint16_t delayT = 5; //5 ms time delay

	     while(Debounce1(delayT) == 0);//debounces press
	     P2->OUT|=0x20; //green turns on
	     while(Debounce1(delayT));//debounces realase

	     while(1){


	         while(Debounce1(delayT) == 0); //debounces press
	         P2->OUT&=~0x20;//green turns off
	         P2->OUT|=0x40;//Yellow turns on
	         while(Debounce1(delayT));//debounces realase

	         while(Debounce1(delayT) == 0);//debounces press
	         P2->OUT&=~0x40;//Yellow turns off
	         P2->OUT|=0x80;//Red turns on
	         while(Debounce1(delayT));//debounces realase

	         while(Debounce1(delayT) == 0);//debounces press
	         P2->OUT&=~0x80;//Red turns off
	         P2->OUT|=0x20;//green turns on
	         while(Debounce1(delayT));//debounces realase

	         }
	     }


void  SysTick_Init(){
    int fail = 0;
    SysTick->LOAD=3000 - 1;  //1 Millisecond
    SysTick->VAL =  0; //Clears with any value
    SysTick->CTRL = 0x01; //Enables Clock
    while(fail == 0){
        if(SysTick->CTRL&BIT(16))//Delays until Clock ends
            fail = 1;
    }
}

void SysTick_Delay(uint16_t d){
    int i;
        for(i = 0; i <= d; i++){
            SysTick_Init();
    }
}

int Debounce1(uint16_t delayTime){
    if((P3->IN & 0x80)==0){ //checks if the button is pressed
       SysTick_Delay(delayTime); //delay
         if((P3->IN & 0x80)==0) return 1; //Checks if button is pressed
    }
    return 0; //returns 0 if button is not pressed
}
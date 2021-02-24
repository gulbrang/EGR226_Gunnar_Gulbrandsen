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
int Debounce_B1(uint16_t d);
int Debounce_B2(uint16_t c);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

         //Button
         P3->SEL0 &= ~0xC0; // configure P3.6,3.7 GPIO
         P3->SEL1 &= ~0xC0;
         P3->DIR &= ~0xC0; // make P3.6,3.7 input
         P3->REN |= 0xC0; // enable pull resistor on P3.6,3.7
         P3->OUT |= 0xC0; // P3.6,3.7 pull-down


         //LED
         P2->SEL0 &= ~0xE0; // configure P2.5-2.7 GPIO
         P2->SEL1 &= ~0xE0;
         P2->DIR |= 0xE0; // make P2.5-2.7 output
         P2->OUT &= 0x00;

         uint16_t delayLED = 1000; //1s time delay
         uint16_t delayD = 5; //5ms debounce delay

                  enum States{ //light sequencing states
                      green,
                      yellow,
                      red,
                  };

                  char color = green;


  while(1){

      while(Debounce_B1(delayD)){
          switch(color){
                    case green: {
                    P2->OUT &= 0x00;//cleared
                    P2->OUT|=0x20;//green turns on
                    if(Debounce_B1(delayD)==0)break;
                    SysTick_Delay(delayLED);
                    color = yellow;
                   }

                    case yellow:  {
                    P2->OUT&=0x00;//cleared
                    P2->OUT|=0x40;//Yellow turns on
                    if(Debounce_B1(delayD)==0)break;
                    SysTick_Delay(delayLED);
                    color = red;
                    }

                    case red: {
                    P2->OUT&=0x00;//cleared
                    P2->OUT|=0x80;//red turns on
                    if(Debounce_B1(delayD)==0)break;
                    SysTick_Delay(delayLED);
                    color = green;
                   }
            }
         }

        while(Debounce_B2(delayD)){
                        switch(color){

                            case yellow: {
                            P2->OUT &= 0x00;//cleared
                            P2->OUT|=0x40;//Yellow turns on
                            if(Debounce_B2(delayD)==0)break;
                            SysTick_Delay(delayLED);
                            color = green;
                            }

                            case green: {
                             P2->OUT&=0x00;//cleared
                             P2->OUT|=0x20;//green turns on
                             if(Debounce_B2(delayD)==0)break;
                            SysTick_Delay(delayLED);
                            color = red;
                            }

                            case red: {
                            P2->OUT &= 0x00;//cleared
                            P2->OUT|= 0x80;//red turns on
                            if(Debounce_B2(delayD)==0)break;
                            SysTick_Delay(delayLED);
                            color = yellow;
                           }
                        }
                }
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

int Debounce_B1(uint16_t delayTime){
    if((P3->IN & 0x80)==0){ //checks if the button is pressed
       SysTick_Delay(delayTime); //delay
         if((P3->IN & 0x80)==0) return 1; //Checks if button is pressed
    }
    return 0; //returns 0 if button is not pressed
}

int Debounce_B2(uint16_t delayTime){
    if((P3->IN & 0x40)==0){ //checks if the button is pressed
       SysTick_Delay(delayTime); //delay
         if((P3->IN & 0x40)==0) return 1; //Checks if button is pressed
    }
    return 0; //returns 0 if button is not pressed
}

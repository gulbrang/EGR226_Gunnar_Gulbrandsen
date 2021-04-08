/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/7/2021
* Project: Lab 11
* File: Lab9_Functions.c
* Description: .c file for lab 11
**************************************************************************************/

#include "Lab11_Functions.h"

/****| TimerA_setPulses() | *****************************************
* Brief: This function initiates Timer A and sets pulses.
* param:
* uint8_t c
* return:
* N/A
*************************************************************/
void TimerA_setPulses(){
       uint16_t p = 37500;
       TIMER_A0->CCR[0]= p - 1;                         //sets period for TimerA
       TIMER_A0->CCR[1]= p/2;
       TIMER_A0->CCTL[1]= 0xE0;                        //reset/set mode
       TIMER_A0->CTL = 0x2D4;                          //SMCLK, count up,1/8 divider clear TA0R
       TIMER_A0->EX0 = 7;
}

/****| LED_init() | *****************************************
* Brief: This function initiates Timer A and sets pulses.
* param:
* uint8_t c
* return:
* N/A
*************************************************************/
void LED_init(){                    //initiate LED
    P2->SEL0 &= ~BIT0;
    P2->SEL1 &= ~BIT0;
    P2->DIR |= BIT0;
}

/****| TimerA_init() | *****************************************
* Brief: This function initiates Timer A at P2.4 and P2.7
* param:
* uint8_t c
* return:
* N/A
*************************************************************/
void TimerA_init(){
    //configure P2.4 as TimerA0.1 output
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;
    P2->DIR |= BIT4;

    //configure P2.7 as TimerA0.4 input
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;
    P2->DIR &= ~BIT7;
}

/****| TimerA_capture() | *****************************************
* Brief: This function initiates Timer A and sets pulses.
* param:
* uint8_t c
* return:
* N/A
*************************************************************/
void TimerA_capture(){
       //P2.4 LED emitter
       uint16_t p = 37500;
       TIMER_A0->CCR[0]= p - 1;                         //sets period for TimerA
       TIMER_A0->CCR[1]= p/2;
       TIMER_A0->CTL = 0x2D4;                          //SMCLK, count up,1/8 divider clear TA0R,interrrupt enabled
       TIMER_A0->EX0 = 7;                              //divide clock by 8
       TIMER_A0->CCTL[1]= 0xE0;                        //reset/set mode

       //P2.7 LED capture
       TIMER_A0->CCTL[4] = 0x4914;                     //capture enabled, synchronous, capture rising edge,capture interrupt enabled,CCxA
}

/****| TA_0_0IRQHandler() | *****************************************
* Brief: This function initiates Timer A and sets pulses.
* param:
* uint8_t c
* return:
* N/A
*************************************************************/
void TA_0_0IRQHandler(){
      uint32_t currentEdge;
      uint32_t lastEdge;
      uint32_t period;

      currentEdge =  TIMER_A0->CCR[2];
      period = currentEdge - lastEdge;
      lastEdge = TIMER_A0->CCR[2];


       if(TIMER_A0->CCTL[4] & BIT0){
           LED_init();
           P2->OUT ^= BIT0;
       }


        if ((35635 < period ) && ( period < 39375 )){
            LED_init();
            P2->OUT ^= BIT0;
    }

    TIMER_A0->CCTL[4] &= ~(BIT0);    // Clear the interrupt flag
 }

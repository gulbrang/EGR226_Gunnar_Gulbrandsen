/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/1/2021
* Project: Lab 10
* File: Lab10_1.c
* Description: Program prints the voltage being returned to the MSP 
**************************************************************************************/

#include "Lab10_Functions.h"

void main(void)
{
    static volatile uint16_t result;
    float nADC;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    MEM0_init();                                    //initiates ADC

    printf("\n");

    while (1)
          {
    ADC14->CTL0 |= 1;                               //start conversation
    while(!ADC14->IFGR0);                           //wait for conversation to complete
    result = ADC14->MEM[0];                         // get the value from the ADC
    nADC = (result * 3.3) / 16384;                  //convert result to voltage
    printf("Potentiometer:\t%fv\n",nADC );
    delayMs(2000);                                  // SysTick delay has been configured
    }
    }
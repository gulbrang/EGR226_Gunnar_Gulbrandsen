/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/1/2021
* Project: Lab 10
* File: Lab10_2.c
* Description: Program reads voltage being returned to MSP the is filtered through
* a temperature sensor. Said voltage is converted to a temperature and printed. 
**************************************************************************************/

#include "Lab10_Functions.h"

void main(void)
{
    static volatile uint16_t result;
    float nADC,temp;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    MEM1_init();

    printf("\n");

    while(1){

    ADC14->CTL0 |= 1;                            //start conversation
    while(!ADC14->IFGR0);                       //wait for conversation to complete
    result = ADC14->MEM[1];                     // get the value from the ADC
    nADC = (result * 3.3) / 16384;              // convert result to voltage
    printf("\n");
    printf("\nTemp:\n",nADC);
    temp = ((nADC*1000) - 500)/10;              //convert voltage to degrees celsius
    printf("\tCelsius:%.2F\n",temp);    
    temp = (temp * 1.8)+32;                     //convert celsius to fahrenheit
    printf("\tFahrenheit:%.2F \n",temp);
    delayMs(2000);                              // SysTick delay has been configure
    }
}
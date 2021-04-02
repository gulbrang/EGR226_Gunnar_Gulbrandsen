/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/1/2021
* Project: Lab 10
* File: Lab10_3.c
* Description: Program displays the degrees in celsius one an LED display and if 
* a button is pressed the display switches between celsius and fahrenheit.
**************************************************************************************/

#include "Lab10_Functions.h"

//RS Pin: P4.0
//E Pin: P4.2
//DB4-7: P4.4-P4.7

void main(void)
{
    static volatile uint16_t result;
    float nADC,temp;
    char prompt[50]="Current Temp is:";

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    MEM1_init();                                    //initiates ADC
    LCD_init();                                     //initiates LCD
    commandWrite(1);                                //clears display
    delayMs(2);
    setupPort6Interrupt();                          //sets up port 6 interrupt
    NVIC->ISER[1]=1<<((PORT6_IRQn)&31);             //sets up port 6 interrupt
    __enable_irq();                                 //enables interrupt

    pressed = 0;

    while(1){

    ADC14->CTL0 |= 1;                             //start conversation
    while(!ADC14->IFGR0);                       //wait for conversation to complete
    result = ADC14->MEM[1];                      // get the value from the ADC
    nADC = (result * 3.3) / 16384;               //converts result to voltage
    temp = ((nADC*1000) - 500)/10;               //converts voltage to temp

    if(pressed == 0){
    commandWrite(1);                            //clear display
    commandWrite(0x80);                         //moves cursor line 1
    printString(prompt);                         //prints firstName
    commandWrite(0xC4);                         //moves cursor line 2
    bufferPrint(temp);                         //prints last name
    dataWrite(0xDF);                           //prints degree symbol
    dataWrite('C'); 
    }

    if(pressed != 0){
       commandWrite(1);                            //clear display
       commandWrite(0x80);                         //moves cursor line 1
       printString(prompt);                         //prints firstName
       commandWrite(0xC4);                         //moves cursor line 2
       temp = (temp * 1.8)+32;                      //convert temp to fahrenheit
       bufferPrint(temp);                            //prints last name
       dataWrite(0xDF);                             //prints degree symbol
       dataWrite('F');
       }

    delayMs(2000);                          // SysTick delay has been configure
    }
}
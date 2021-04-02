/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/1/2021
* Project: Lab 10
* File: Lab10_Functions.c
* Description: .c file for functions used in Lab 10
**************************************************************************************/

#include "Lab10_Functions.h"

/****| delayMicro() | *****************************************
* Brief: This function initiates the stystick clock and will
* delay 1 microsecond when called
* param:
* unsigned microsecond
* return:
* N/A
*************************************************************/
void delayMicro(unsigned microsecond){          // SysTick timer generate a delay in milliseconds.
        SysTick -> LOAD = (microsecond*3 - 1);  // delay*3 value must be < 2^24-1=16,777,215
        SysTick -> VAL    = 0;                      // any write to CVR clears it
        SysTick->CTRL = 0x05; //Enables Clock
        while(((SysTick -> CTRL) & 0x00010000) == 0);
        SysTick->CTRL = 0x00; //Disables Clock
}

/****| delayMs() | *****************************************
* Brief: This function initiates the stystick clock and will
* delay 1 microsecond when called
* param:
* unsigned ms
* return:
* N/A
*************************************************************/
void delayMs(unsigned ms){          // SysTick timer generate a delay in milliseconds.
        SysTick -> LOAD = (ms*3000 - 1);  // delay*3 value must be < 2^24-1=16,777,215
        SysTick -> VAL = 0;                      // any write to CVR clears it
        SysTick->CTRL = 0x05; //Enables Clock
        while(((SysTick -> CTRL) & 0x00010000) == 0);
        SysTick->CTRL = 0x00; //Disables Clock
}

/****| PulseEnablePin() | *****************************************
* Brief: Turns enable pin on and off to read data or command
* into the LCD
* param:
* N/A
* return:
* N/A
*************************************************************/
void PulseEnablePin(void)
{
    P4->OUT &=~BIT2;        //clear E
    delayMicro(10);
    P4->OUT |= BIT2;        //Turn E on
    delayMicro(10);
    P4->OUT &=~BIT2;
    delayMicro(10);         //clear E
}

/****| pushNibble() | *****************************************
* Brief: Nibble is shifted and sent to the LCD through
* P4.4-P4.7
* param:
* uint8_t nibble
* return:
* N/A
*************************************************************/
void pushNibble(uint8_t nibble)
{
    P4->OUT &= ~0xF0;                    // clear P4.4-P4.7
    P4->OUT |= (nibble & 0x0F) << 4;     // port pins P4.4 - P4.7 wired to D4 - D7
    PulseEnablePin();
}


/****| pushByte() | *****************************************
* Brief: Nibble is shifted and sent to the LCD through
* P4.4-P4.7
* param:
* uint8_t byte,uint8_t control
* return:
* N/A
*************************************************************/
void pushByte(uint8_t byte,uint8_t control){
    uint8_t nibble;
    if(control == 1){
        P4->OUT |= BIT0;              //R/S pin on
        delayMs(1);
    }
    else {
        P4->OUT &= ~BIT0;            //R/S pin off
        delayMs(1);
    }
    nibble = (byte & 0xF0) >> 4;         //Shift upper bits
    pushNibble(nibble);                 //read upper bits
    nibble = byte & 0x0F;               //lower bits
    pushNibble(nibble);                 //read lower bits
    delayMicro(100);
}

/****| commandWrite() | *****************************************
* Brief: Data is sent to the LCD as a command
* param:
* unsigned char data
* return:
* N/A
*************************************************************/
void commandWrite(unsigned char data){
    uint8_t RS = 0;

    pushByte(data,RS);          //push bytes with command

    if(data < 4){
        delayMs(1);             //commands 1 and 2 need up to 1.64ms
        delayMicro(70);
    }
    else delayMicro(40);             //all others 40 us
}

/****| dataWrite() | *****************************************
* Brief: Data is sent to the LCD as data
* param:
* unsigned char data
* return:
* N/A
*************************************************************/
void dataWrite(unsigned char data){
    uint8_t RS = 1;

    pushByte(data,RS);          //push data bytes

    delayMs(1);                 //ms delay for data push
}

/****| LCD_init() | *****************************************
* Brief: LCD is initiated through and initialization sequence
* as well as setting up the cursor
* param:
* unsigned char data
* return:
* N/A
*************************************************************/
void LCD_init(){
       P4->DIR |= 0xFF;              //set port 4 to output

       delayMs(30);                 //initialization sequence
       commandWrite(0x30);
       delayMs(10);
       commandWrite(0x30);
       delayMs(1);
       commandWrite(0x30);
       delayMs(1);
       commandWrite(0x20);              //4 bit data mode
       delayMs(1);
                                   //initilize LCD write
           commandWrite(0x28);
           delayMicro(100);
           commandWrite(0x0F);
           delayMicro(100);
           commandWrite(0x01);
           delayMicro(100);
           commandWrite(0x06);
           delayMs(10);
}

/****| printString() | *****************************************
* Brief: String is taken as a parameter and printed to the LCD
* param:
* char str[]
* return:
* N/A
*************************************************************/
void printString(char str[]){
          int i=0;

          while(str[i] != 0)             //loops until end of string
           {
             dataWrite(str[i]);         //prints element of string
             i=i+1;                     //moves to the next element
           }
}

/****| MEM0_init() | *****************************************
* Brief: Function initializes the ADC at P5.5
* param:
* N/A
* return:
* N/A
*************************************************************/
void MEM0_init(void){
  P5->SEL0 |= BIT5;
  P5->SEL1 |= BIT5;
  ADC14 -> CTL0  &= ~0x2;                 // disable ADC converter during initialization
  ADC14->CTL0 |= 0x04200210;            // S/H pulse mode, SMCLK, 16 sample clocks
  ADC14->CTL1 = 0x00000030;                      // 14 bit resolution
  ADC14->CTL1 |=  0x00000000;                    // convert for mem0 register
  ADC14->MCTL[0] = 0x00000000;                   // ADC14INCHx = 0 for mem[0]
  ADC14->CTL0 |= 0x2;                             // enable ADC14ENC, Starts the ADC after confg.
 }


/****| MEM1_init() | *****************************************
* Brief: Function initializes the ADC at P.5.4
* param:
* N/A
* return:
* N/A
*************************************************************/
void MEM1_init(void){
  P5->SEL0 |= BIT4;
  P5->SEL1 |= BIT4;
  ADC14 -> CTL0  &= ~0x2;                 // disable ADC converter during initialization
  ADC14->CTL0 |= 0x04200210;            // S/H pulse mode, SMCLK, 16 sample clocks
  ADC14->CTL1 = 0x00000030;                      // 14 bit resolution
  ADC14->CTL1 |=  0x00010000;                    // convert for mem1 register
  ADC14->MCTL[1] = 0x00000001;                   // ADC14INCHx = 0 for mem[0]
  ADC14->CTL0 |= 0x2;                             // enable ADC14ENC, Starts the ADC after confg.
 }


/****| bufferPrint() | *****************************************
* Brief: Function buffers number and converts it to a string
* and prints said string onto LCD display
* param:
* float temp
* return:
* N/A
*************************************************************/
void bufferPrint(float temp){
  char buffer[50];

  sprintf(buffer, "%.2F", temp);                        //integer converted to a string

  printString(buffer);                                  //prints string to display
  
}


/****| setupPort6Interrupt() | *****************************************
* Brief: This function initiates an interrupt on port six bit4
* param:
* N/A
* return:
* N/A
*************************************************************/
void setupPort6Interrupt(){

         P6->SEL0 &= ~BIT4;                         // configure P6.4
         P6->SEL1 &= ~BIT4;
         P6->DIR &= ~BIT4;                          // make P6.4 input
         P6->REN |= BIT4;                           // enable pull resistor on P6.4
         P6->OUT |= BIT4;                           // P6.4 pull-down
         P6->IES &= ~BIT4;                          //P6.4 interrupt low-high
         P6->IE  |= BIT4;                           //P6.4 interrupt enabled

         P6->IFG = 0;

}

/****| PORT6_IRQHandler() | *****************************************
* Brief: This function changes the value of variable pressed
* param:
* N/A
* return:
* N/A
*************************************************************/
void PORT6_IRQHandler(void){
    int status = P6->IFG;                            //check port 6 interrupt

    if(status){
        P4->OUT = 0;                                 //check status
        pressed = !pressed;
    }

    P6->IFG = 0;                                      //clear flag
}


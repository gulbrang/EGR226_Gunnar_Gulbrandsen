/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 6
* File: Lab7_Functions.c
* Description: .c file for functions used in Lab 7 
**************************************************************************************/

#include "Lab7_Functions.h"

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

/****| commandWrite() | *****************************************
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

/****| printString() | *****************************************
* Brief: String is taken as a parameter and printed to the LCD.
* The printed string is then shifted across the LCD as a scrolling
* marquee
* param:
* char scroll[]
* return:
* N/A
*************************************************************/
void scrollLeft(char scroll[]){
    while(1){
        commandWrite(0x80);             //cursor first line of lcd
        commandWrite(0x01);             //clear lcd
        int i=0;
        int j=0;
        printString(scroll);            //prints string to lcd
        commandWrite(0x8F);             //cursor moved to right side of lcd
        delayMs(500);                   //half second delay
      while(scroll[i]!='\0'){           //loops till end of string
          commandWrite(0x18);           //display shifted left
          i++;                          //next element of string
          j=i+1;
          commandWrite(0x01);           //clear lcd
          while(scroll[j]!='\0'){       //loops till end of string
             dataWrite(scroll[j]);      //prints element of string
             j++;                       //next element
        }
    delayMs(500);                        //half second delay
      }
          i=0;                          //variable set back to 0
          commandWrite(0x01);           //display cleared
          commandWrite(0x8F);           //cursor moved back left
     while(scroll[i]!='\0'){            //loops till end of loop
         dataWrite(scroll[i]);          //prints array element
         delayMs(500);                   //half second delay
         commandWrite(0x18);            //shifts display left
         i=i+1;                         //next element of array
    }
    }
}

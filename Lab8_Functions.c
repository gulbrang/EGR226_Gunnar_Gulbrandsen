/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/17/2021
* Project: Lab 8
* File: Lab8_Functions.c
* Description: .c file for lab 8
**************************************************************************************/

#include "Lab8_Functions.h"

/****| TimerA_init() | *****************************************
* Brief: This function iniates the Timer A to P2.4 as TimerA0.1 output
* param:
* N/A
* return:
* N/A
*************************************************************/
void TimerA_init(){
    //configure P2.4 as TimerA0.1 output
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;
    P2->DIR |= BIT4;

}

/****| TimerA_setPeriod(void) | *****************************************
* Brief: This function sets the period for TimerA
* param:
* uint16_t p
* return:
* N/A
*************************************************************/
void TimerA_setPeriod(uint16_t p){
    TIMER_A0->CCR[0]= p - 1; //sets period for TimerA
}

/****| TimerA_setDutyCycle() | *****************************************
* Brief: This function sets the duty cycle for Timer A
* param:
* uint16_t p,uint8_t cycle
* return:
* N/A
*************************************************************/
void TimerA_setDutyCycle(uint16_t p,uint8_t cycle){
    TIMER_A0->CCR[1]= (p*cycle)/100;
}

/****| TimerA_setDutyCycle() | *****************************************
* Brief: This function initiates Timer A and sets the motor speed. It
* does so by taking the duty cycle as a user input.
* param:
* uint8_t c
* return:
* N/A
*************************************************************/
void TimerA_setMotorSpeed(uint8_t c){
       uint8_t dutyCycle;
       uint16_t period = 37500;

       if(c<10){
       dutyCycle = c*10;
       }
       else{
          dutyCycle = c;
       }

       TimerA_setPeriod(period);                        //PWM period
       TimerA_setDutyCycle(period, dutyCycle);          // PWM duty cycle
       TIMER_A0->CCTL[1]= 0xE0;                        //reset/set mode
       TIMER_A0->CTL = 0x214;                          //SMCLC, count up, clear TA0R
}

/****| keypad_init(void) | *****************************************
* Brief: This function iniates the keypad where the rows are P4.0-P4.3
* and the columns are P4.4-P4.6
* param:
* N/A
* return:
* N/A
*************************************************************/
void keypad_init(void)
 {
    P4->SEL0 &= ~0x7F;
    P4->SEL1 &= ~0x7F;    //configure P4.0-4.6 as GPIO
    P4->DIR  &= ~0x7F;    //configure P4.0-4.6 as inputs

    P4->REN  |= 0x0F;   //enable pull resistors on P4.0-P4.4.3, rows
    P4->OUT  |= 0x0F;   //enable pull-up resistors on P4.0-P4.3, rows
}


/****| Read_Keypad(void) | *****************************************
* Brief: This function reads whether or not the user has inputed
* into the keypad if so the function reads what was inputed
* and returns said input to main.
* param:
* N/A
* return:
* "uint8_t num"
*************************************************************/
uint8_t Read_Keypad(void)
{
    uint8_t col, row, num;
    row = 0;
    num = 0;
    for (col = 0; col < 3; col++){

          P4->DIR  &=     0x00;           // Set Columns to inputs
          P4->DIR  |=     BIT(4+col);     // Set column 3 to output
          P4->OUT  &=    ~BIT(4+col);    // Set column 3 to LOW

          SysTick_Delay(10);           // Delay the while loop

          row = P4->IN & 0x0F;                  // read all rows

          while (!(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3));

          if (row != 0x0F)   break;                  // if one of the input is low, some key is pressed.
      }

        P4->DIR = 0x00;                             // Set Columns to inputs
        if(col == 3)return 0;

        if (row == 0x0E) num = col + 1;        // key in row 0
        if (row == 0x0D) num = 3 + col +1;       // key in row 1
        if (row == 0x0B) num = 6 + col +1;       // key in row 2
        if (row == 0x07) num = 9 + col+1;       // key in row 3

        return num;
}

/****| SysTick_Init() | *****************************************
* Brief: This function initiates the stystick clock and will
* delay 1 ms when called
* param:
* N/A
* return:
* N/A
*************************************************************/
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

/****| SysTick_Delay() | *****************************************
* Brief:This function loops the number of desired ms or "d"
* param:
* "uint16_t d"
* return:
* N/A
*************************************************************/
void SysTick_Delay(uint16_t d){
    int i;
        for(i = 0; i <= d; i++){
            SysTick_Init();
    }
}

/****| systickPWM_High() | *****************************************
* Brief:This function delays for the desired duty cycle when
* the pin is on
* param:
* uint8_t cycle
* return:
* N/A
*************************************************************/
void systickPWM_High(uint8_t cycle){          // Generate PWM
            if(cycle == 0){
                return;
            }
            SysTick -> LOAD = (37500/100)*cycle;            //40hz
            SysTick -> VAL = 0;                      // any write to CVR clears it
            SysTick->CTRL = 0x05; //Enables Clock
            while(((SysTick -> CTRL) & 0x00010000) == 0);
            SysTick->CTRL = 0x00; //Disables Clock
    }

/****| systickPWM_Low() | *****************************************
* Brief:This function delays for the desired duty cycle when
* the pin is low
* param:
* uint8_t cycle
* return:
* N/A
*************************************************************/
    void systickPWM_Low(uint8_t cycle){          // Generate PWM
                if(cycle == 0){
                        return;
                    }
            cycle = 100-cycle;
            SysTick->LOAD = (37500/100)*cycle;            //40hz
            SysTick -> VAL = 0;                      // any write to CVR clears it
            SysTick->CTRL = 0x05; //Enables Clock
            while(((SysTick -> CTRL) & 0x00010000) == 0);
            SysTick->CTRL = 0x00; //Disables Clock
    }

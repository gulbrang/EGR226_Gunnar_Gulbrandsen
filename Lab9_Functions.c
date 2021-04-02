/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/24/2021
* Project: Lab 9
* File: Lab9_Functions.c
* Description: .c file for lab 9
**************************************************************************************/

#include "Lab9_Functions.h"


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


/****| TimerA_setMotorSpeed() | *****************************************
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

       if(c<=10){                                       //checks keypad entry
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


/****| delayMs() | *****************************************
* Brief: This function initiates the stystick clock and will
* delay 1 microsecond when called
* param:
* unsigned ms
* return:
* N/A
*************************************************************/
void delayMs(unsigned ms){                              // SysTick timer generate a delay in milliseconds.
        SysTick -> LOAD = (ms*3000 - 1);                // delay*3 value must be < 2^24-1=16,777,215
        SysTick -> VAL = 0;                             // any write to CVR clears it
        SysTick->CTRL = 0x05;                           //Enables Clock
        while(((SysTick -> CTRL) & 0x00010000) == 0);   //checks 16th bit
        SysTick->CTRL = 0x00;                           //Disables Clock
}


/****| buttonInit() | *****************************************
* Brief: This function initiates a pull down resistor at P3.5-3.7
* as buttons
* param:
* N/A
* return:
* N/A
*************************************************************/
void buttonInit(){

         //Button 1
         P3->SEL0 &= ~BIT5;                         // configure P3.5 GPIO
         P3->SEL1 &= ~BIT5;
         P3->DIR &= ~BIT5;                          // make P3.5 input
         P3->REN |= BIT5;                           // enable pull resistor on P3.5
         P3->OUT |= BIT5;                           // P3.5 pull-down

         //Button 2
         P3->SEL0 &= ~BIT6;                          // configure P3.6 GPIO
         P3->SEL1 &= ~BIT6;
         P3->DIR &= ~BIT6;                          // make P3.6 input
         P3->REN |= BIT6;                           // enable pull resistor on P3.6
         P3->OUT |= BIT6;                           // P3.6 pull-down

         //Button 3
         P3->SEL0 &= ~BIT7;                          // configure P3.7 GPIO
         P3->SEL1 &= ~BIT7;
         P3->DIR &= ~BIT7;                          // make P3.7 input
         P3->REN |= BIT7;                           // enable pull resistor on P3.7
         P3->OUT |= BIT7;                            // P3.7 pull-down
}


/****| Debounce_B1() | *****************************************
* Brief: This function checks the input of the first button
* param:
* N/A
* return:
* N/A
*************************************************************/
int Debounce_B1(){                                  //debounce button 1
    if((P3->IN & 0x80)==0){                         //checks if the button is pressed
         delayMs(5);                                //delay
         if((P3->IN & 0x80)==0) return 1;           //Checks if button is pressed
    }
    return 0;                                       //returns 0 if button is not pressed
}


/****| Debounce_B2() | *****************************************
* Brief: This function checks the input of the second button
* param:
* N/A
* return:
* N/A
*************************************************************/
int Debounce_B2(){                                  //debounce button 2
    if((P3->IN & 0x40)==0){                         //checks if the button is pressed
         delayMs(5);                                //delay
         if((P3->IN & 0x40)==0) return 1;           //Checks if button is pressed
    }
    return 0;                                       //returns 0 if button is not pressed
}


/****| Debounce_B3() | *****************************************
* Brief: This function checks the input of the third button
* param:
* N/A
* return:
* N/A
*************************************************************/
int Debounce_B3(){                                  //debounce button 3
    if((P3->IN & 0x20)==0){                         //checks if the button is pressed
         delayMs(5);                                //delay
         if((P3->IN & 0x20)==0) return 1;           //Checks if button is pressed
    }
    return 0;                                       //returns 0 if button is not pressed
}

/****| Debounce_B4() | *****************************************
* Brief: This function checks the input of the fourth button
* param:
* N/A
* return:
* N/A
*************************************************************/
int Debounce_B4(){                                  //debounce button 4
    if((P6->IN & 0x10)==0){                         //checks if the button is pressed
         delayMs(5);                                //delay
         if((P6->IN & 0x10)==0) return 1;           //Checks if button is pressed
    }
    return 0;                                       //returns 0 if button is not pressed
}

/****| Debounce_B5() | *****************************************
* Brief: This function checks the input of the fifth button
* param:
* N/A
* return:
* N/A
*************************************************************/
int Debounce_B5(){                                   //debounce button 5
    if((P6->IN & 0x20)==0){                          //checks if the button is pressed
         delayMs(5);                                 //delay
         if((P6->IN & 0x20)==0) return 1;            //Checks if button is pressed
    }
    return 0;                                       //returns 0 if button is not pressed
}

/****| segmentNumber() | *****************************************
* Brief: This function displays the corresponding number on a
* seven segment display
* param:
* N/A
* return:
* N/A
*************************************************************/
void segmentNumber(void){
    switch(count){                                  //checks count

            case 0: {
                P4->OUT |= 0x3F;                    //displays 0
                break;
            }

            case 1: {
                P4->OUT |= 0x06;                    //displays 1
                break;
            }

            case 2: {
                P4->OUT |= 0x5B;                    //displays 2
                break;
            }

            case 3: {
                P4->OUT |= 0x4F;                    //displays 3
                break;
            }

            case 4: {
                P4->OUT |= 0x66;                    //displays 4
                break;
            }

            case 5: {
                P4->OUT |= 0x6D;                    //displays 5
                break;
            }

            case 6: {
                P4->OUT |= 0x7D;                    //displays 6
                break;
            }

            case 7: {
                P4->OUT |= 0x07;                    //displays 7
                break;
            }

            case 8: {
                P4->OUT |= 0x7F;                    //displays 8
                break;
            }

            case 9: {
                P4->OUT |= 0x67;                    //displays 9
                break;
    }
}
}

/****| segmentNumber_Init() | *****************************************
* Brief: This function initiates the seven segment display
* param:
* N/A
* return:
* N/A
*************************************************************/
void sevenSegment_Init(void){
         P4->SEL0 &= ~0xFF;                         // configure Port 4 GPIO
         P4->SEL1 &= ~0xFF;
         P4->DIR |= 0xFF;                           // make Port 4 output
         P4->OUT &= ~0xFF;                          // clear Port 4 output
}

/****| segmentNumber_Init() | *****************************************
* Brief: This function initiates an interrupt on port six bit4 and bit5
* param:
* N/A
* return:
* N/A
*************************************************************/
void setupPort6Interrupt(){

         //Button 4
         P6->SEL0 &= ~BIT4;                         // configure P6.4
         P6->SEL1 &= ~BIT4;
         P6->DIR &= ~BIT4;                          // make P6.4 input
         P6->REN |= BIT4;                           // enable pull resistor on P6.4
         P6->OUT |= BIT4;                           // P6.4 pull-down
         P6->IES &= ~BIT4;                          //P6.4 interrupt low-high
         P6->IE  |= BIT4;                           //P6.4 interrupt enabled

         //Button 5
         P6->SEL0 &= ~BIT5;                         // configure P6.5
         P6->SEL1 &= ~BIT5;
         P6->DIR &= ~BIT5;                          // make P6.5 input
         P6->REN |= BIT5;                            // enable pull resistor on P6.5
         P6->OUT |= BIT5;                            // P6.5 pull-down
         P6->IES &= ~BIT5;                          //P6.5 interrupt low-high
         P6->IE  |= BIT5;                            //P6.5 interrupt enabled

         P6->IFG = 0;
}


/****| SysTick_Init_interrupt() | *****************************************
* Brief: This function initiates a systick interrupt with a one second delay
* param:
* N/A
* return:
* N/A
*************************************************************/
void SysTick_Init_interrupt(void){
        SysTick -> CTRL = 0;                         // disable SysTick During step
        SysTick -> LOAD = 3000000;                   //  reload value for 1s interrupts
        SysTick -> VAL = 20;                         // any write to current clears
        SysTick -> CTRL = 0x00000007;                // enable SysTick, 3MHz,   with Interrupts
}


/****| SysTick_Handler() | *****************************************
* Brief: This function raises a flag and increases the count by one
* param:
* N/A
* return:
* N/A
*************************************************************/
void SysTick_Handler(void){
    flag = 1;                                        //raise flag
    count++;                                         //increase count
}


/****| PORT6_IRQHandler() | *****************************************
* Brief: This function either increases or decreases a number displayed
* on a seven segment display depending on which button is pressed
* param:
* N/A
* return:
* N/A
*************************************************************/
void PORT6_IRQHandler(void){
    int status = P6->IFG;                            //check port 6 interrupt

    if(status){                                      //check status

        P4->OUT = 0;                                 //clear port four
        printf("flag raised\n");

        if(status & BIT4){                           //check status at BIT4
              while(Debounce_B4());                  //debouce button 4
              printf("B4\n");
              if(count == 9) count = 0;              //roll count back
              else count++;                          //increase count
              segmentNumber();                       //display current number
        }

        if(status & BIT5){                           //check status at BIT5
              while(Debounce_B5());                  //debouce button 5
              printf("B5\n");
              if(count == 0) count = 9;              //roll count back
              else count--;                          //decrease count
              segmentNumber();                       //display current number
    }
}
    P6->IFG = 0;                                      //clear flag
}

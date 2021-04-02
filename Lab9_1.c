/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/24/2021
* Project: Lab 9
* File: Lab9_1.c
* Description: .c file for lab 9
**************************************************************************************/

#include "Lab9_Functions.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	TimerA_init();                                  // Call initialization functions for functionality
	buttonInit();                                   //initiates buttons
	uint8_t speed = 0;
	uint8_t pressed;

	     while(1){
	         pressed = 0;
	         while(pressed == 0){
	                        if(Debounce_B1()){                                  //checks if button 1 is pressed
	                            while(Debounce_B1()==0);                        //debounces button
	                            printf("B1\n");
	                            if((speed < 10) && (speed >= 0))                //checks previous speed
	                                speed = speed +1;                           //increases speed
	                                pressed = 1;
	                        }

	                        if(Debounce_B2()){                                  //checks if button 2 is pressed
	                            while(Debounce_B2()==0);
	                            printf("B2\n");
	                            if((speed <= 10) && (speed > 0))                //checks previous speed
	                            speed = speed -1;                               //decreases speed
	                            pressed = 1;
	                        }

	                        if(Debounce_B3()){                                  //checks if button 3 is pressed
	                            while(Debounce_B3()==0);                         //debounces button
	                            printf("B3\n");
	                            speed = 0;                                       //sets speed to 0
	                            pressed = 1;
	                        }
	       }
	                    if((speed <= 10) && (speed >= 0)){                        //checks previous speed
	                        printf("Speed Set\n");
	                        printf("Current Speed:%d\n",speed);
	                        TimerA_setMotorSpeed(speed);                           //sets speed
	                        }
	     }
}

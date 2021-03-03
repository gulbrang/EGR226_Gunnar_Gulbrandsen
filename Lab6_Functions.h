/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/3/2021
* Project: Lab 6
* File: Lab6_Functions.h
* Description: Header file for Lab6_Functions.c
**************************************************************************************/
#ifndef __LAB6_FUNCTIONS_H__
#define __LAB6_FUNCTIONS_H__

#include "msp.h"
#include <stdio.h>


typedef struct entry{
       uint8_t one;
       uint8_t two;
       uint8_t three;
       uint8_t four;
   }entry;

uint16_t d;
uint16_t delayTime;

void  SysTick_Init();
void SysTick_Delay(uint16_t d);
int Debounce_Keypad(uint16_t delayTime);
void keypad_init(void);
void Print_Keys(int n);
uint8_t Read_Keypad(void);
void Print_Keys_Code(entry a);
entry keypad_PIN_AGAIN();
entry keypad_PIN();
void keypad_PIN_Confirm(entry a,entry b);


#endif
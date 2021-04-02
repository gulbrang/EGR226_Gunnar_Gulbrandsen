/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/24/2021
* Project: Lab 9
* File: Lab9_Functions.h
* Description: .h file for lab 9
**************************************************************************************/

#ifndef __LAB9_FUNCTIONS_H__
#define __LAB9_FUNCTIONS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "msp.h"
#include <limits.h>
#include <float.h>
#include <math.h>

volatile uint8_t count;
volatile uint8_t flag;
uint8_t delayD;

void buttonInit();
void TimerA_setMotorSpeed(uint8_t c);
void TimerA_setDutyCycle(uint16_t p,uint8_t cycle);
void TimerA_setPeriod(uint16_t p);
void TimerA_init();
void delayMs(unsigned ms);
int Debounce_B1();
int Debounce_B2();
int Debounce_B3();
int Debounce_B5();
int Debounce_B4();
void segmentNumber(void);
void sevenSegment_Init(void);
void segmentNumber(void);
void setupPort6Interrupt();
void SysTick_Init_interrupt(void);
void SysTick_Handler(void);

#endif

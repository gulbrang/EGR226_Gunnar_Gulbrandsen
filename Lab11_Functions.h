/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 3/24/2021
* Project: Lab 9
* File: Lab9_Functions.h
* Description: .h file for lab 9
**************************************************************************************/

#ifndef __LAB11_FUNCTIONS_H__
#define __LAB11_FUNCTIONS_H__

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

void TimerA_setPulses();
void TimerA_init();
void LED_init();
void delayMs(unsigned ms);
void TimerA_capture();

#endif

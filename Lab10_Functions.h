/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 4/1/2021
* Project: Lab 10
* File: Lab10_Functions.h
* Description: Header file for functions used in Lab 10
**************************************************************************************/

#ifndef __LAB10_FUNCTIONS_H__
#define __LAB10_FUNCTIONS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "msp.h"
#include <limits.h>
#include <float.h>
#include <math.h>

static volatile uint16_t result;
volatile uint8_t pressed;

void LCD_init(void);            

void delayMicro(unsigned microsec);   

void delayMs(unsigned ms);      

void PulseEnablePin(void);          

void pushNibble(uint8_t nibble);    

void pushByte(uint8_t byte,uint8_t control);             

void commandWrite(uint8_t command);     

void dataWrite(uint8_t data);       

void printString(char str[]);      

void MEM1_init(void);

void MEM0_init(void);

void bufferPrint(float temp);

void setupPort6Interrupt();

#endif
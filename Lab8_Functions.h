#ifndef __LAB8_FUNCTIONS_H__
#define __LAB8_FUNCTIONS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "msp.h"
#include <limits.h>
#include <float.h>
#include <math.h>

void TimerA_init();
void TimerA_setPeriod(uint16_t p);
void TimerA_setDutyCycle(uint16_t p,uint8_t cycle);
void TimerA_setMotorSpeed(uint8_t c);
void TimerA_stopMotor();
uint8_t Read_Keypad(void);
void keypad_init(void);
void  SysTick_Init();
void SysTick_Delay(uint16_t d);
void systickPWM_High(uint8_t dutyCycle);
void systickPWM_Low(uint8_t dutyCycle);

#endif

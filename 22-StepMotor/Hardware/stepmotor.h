/*
@file stepmotor.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for stepmotor.c
*/

#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#include "stm32f10x.h"

//@def define port and gpio pin for LED1
#define STEPMOTOR_PORT GPIOB
#define STEPMOTOR_Pin_A GPIO_Pin_3
#define STEPMOTOR_Pin_B GPIO_Pin_4
#define STEPMOTOR_Pin_NA GPIO_Pin_8
#define STEPMOTOR_Pin_NB GPIO_Pin_9

#define STEP_PER_LOOP 4076

void STEPMOTOR_Init(void);
void STEPMOTOR_OFF(void);
void STEPMOTOR_Run_Steps(uint8_t dir, uint64_t step, uint16_t speed);
void STEPMOTOR_Run_Loops(uint8_t dir, uint64_t loop, uint16_t speed);
void stepmotor_4_step(uint8_t step, uint16_t speed);
void stepmotor_8_step(uint8_t step, uint16_t speed);

#endif

/*
@file relay.h
@version 0.1
@author magic.liu
@date Jan-22-2023
@brief head file for relay.c
*/

#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"

//@def define port and gpio pin for LED1
#define RELAY_PORT GPIOA
#define RELAY1_Pin GPIO_Pin_14
#define RELAY2_Pin GPIO_Pin_13

void RELAY_Init(void);
void set_relay1(FunctionalState state);
void set_relay2(FunctionalState state);

#endif

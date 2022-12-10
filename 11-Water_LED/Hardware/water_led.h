/*
@file water_led.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for water_led.c
*/
#include "stm32f10x.h"

#ifndef __WATER_LED_H
#define __WATER_LED_H

#define WATER_LED_PORT GPIOA

void Water_LED_Init(void);
void Water_LED_Run(void);

#endif

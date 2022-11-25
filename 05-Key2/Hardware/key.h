/*
@file key.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for key function
*/

#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY_PORT GPIOA
#define KEY1_Pin GPIO_Pin_0
#define KEY2_Pin GPIO_Pin_1

void Key_Init(void);
#endif

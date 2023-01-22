/*
@file touchkey.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for touch key function
*/

#ifndef __TOUCHKEY_H
#define __TOUCHKEY_H

#include "stm32f10x.h"

#define RCC_TOUCHKEY_SOURCE RCC_APB2Periph_GPIOA
#define TOUCHKEY_PORT GPIOA
#define TOUCHKEY1_Pin GPIO_Pin_0
#define TOUCHKEY2_Pin GPIO_Pin_1
#define TOUCHKEY3_Pin GPIO_Pin_2
#define TOUCHKEY4_Pin GPIO_Pin_3

void TOUCHKey_Init(void);

#endif

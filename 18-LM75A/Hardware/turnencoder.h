/*
@file turnencoder.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief hear file for driver of turn encoder 
*/

#ifndef __TURNENCODER__
#define    __TURNENCODER__

#include "stm32f10x.h"
#define RCC_TurnEncoder_1 RCC_APB2Periph_GPIOA
#define RCC_TurnEncoder_2 RCC_APB2Periph_GPIOB
#define Port_TurnEncoder_1 GPIOA
#define Port_TurnEncoder_2 GPIOB
#define KEY1_Pin GPIO_Pin_7
#define KEY2_Pin GPIO_Pin_6
#define KEY3_Pin GPIO_Pin_2

void TurnEncoder_Init(void);
uint8_t Get_Encoder(void);

#endif

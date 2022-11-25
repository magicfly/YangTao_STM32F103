/*
@file key.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief c source file for key function
*/

#include "key.h"

void Key_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY1_Pin | KEY2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);
}

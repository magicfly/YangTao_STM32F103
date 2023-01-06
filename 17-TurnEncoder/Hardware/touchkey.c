/*
@file touchkey.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief c source file for touch key function
*/

#include "touchkey.h"

void TOUCHKey_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_TOUCHKEY_SOURCE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TOUCHKEY1_Pin | TOUCHKEY2_Pin | TOUCHKEY3_Pin | TOUCHKEY4_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TOUCHKEY_PORT, &GPIO_InitStructure);
}

/*
@file LM75A.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for LM75A.c
*/

#ifndef __LM75A_H
#define __LM75A_H

#include "stm32f10x.h"
#include "I2C_1.h"

#define LM75A_ADDRESS 0x9e

double LM75A_GetTemp(void);
void LM75A_PwrDown(void);
void LM75A_Set_Conf_Register(uint8_t conf_mask);
uint8_t LM75A_Get_Conf_Register(void);
#endif

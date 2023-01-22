/*
@file utils.h
@version 0.1
@author magic.liu
@date 11-12-2011
@brief heard file for common functions for user

version details:
v0.1: add delay function

*/

#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"

void delay_us(uint32_t tims_us);
void delay_ms(uint32_t time_ms);
void delay_s(uint32_t time_s);

#endif

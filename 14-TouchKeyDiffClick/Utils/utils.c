/*
@file utils.c
@version 0.1
@author magic.liu
@date 11-12-2011
@brief common functions for user

version details:
v0.1: add delay_us,delay_ms,delay_s function

*/

#include "utils.h"
#include "stm32f10x.h"

#define AHB_INPUT 72

void delay_us(uint32_t time_us){
	//@brief delay some us
	//@param time_us time in us
	SysTick->LOAD = AHB_INPUT * time_us; //set inital value
	SysTick->VAL = 0x00; // clear counter
	SysTick->CTRL = 0x00000005; // enable counter
	while(!(SysTick->CTRL & 0x00010000)); //waiting counter to zero
	SysTick->CTRL = 0X00000004; // disable counter
}

void delay_ms(uint32_t time_ms){
	//@brief delay some micro seconds
	//@param time_ms time in ms
	while(time_ms--){
		delay_us(1000);
	}
}

void delay_s(uint32_t time_s){
	////@brief delay some seconds
	//@param time_s time in s
	while(time_s--){
		delay_ms(1000);
	}
}

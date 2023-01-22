/*
@file relay.c
@version 0.1
@author magic.liu
@date Jan-22-2023
@brief c sorce file for relay function
*/
#include "relay.h"
#include "utils.h"
#include "stm32f10x_gpio.h"

void RELAY_Init(void){
	//@brief intial LED port and LED pin
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  //enable AFIO clock so that PA13/PA14 can be remaped
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //remap JTAG Pin
	GPIO_InitStructure.GPIO_Pin = RELAY1_Pin | RELAY2_Pin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RELAY_PORT, &GPIO_InitStructure);
	// default disable relay in initalization
	GPIO_WriteBit(RELAY_PORT, RELAY1_Pin, (BitAction) (0));
	GPIO_WriteBit(RELAY_PORT, RELAY2_Pin, (BitAction) (0));
}

void set_relay1(FunctionalState state){
	//@brief turn on or off relay1
	//@param state on or off to be set to relay1
	if(state == ENABLE){
		GPIO_WriteBit(RELAY_PORT, RELAY1_Pin, (BitAction) (1));
	} else {
		GPIO_WriteBit(RELAY_PORT, RELAY1_Pin, (BitAction) (0));
	}
}

void set_relay2(FunctionalState state){
	//@brief turn on or off relay2
	//@param state on or off to be set to relay2
	if(state == ENABLE){
		GPIO_WriteBit(RELAY_PORT, RELAY2_Pin, (BitAction) (1));
	} else {
		GPIO_WriteBit(RELAY_PORT, RELAY2_Pin, (BitAction) (0));
	}
}

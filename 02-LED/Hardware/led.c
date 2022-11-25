/*
@file led.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief c sorce file for led function
*/

#include "led.h"
#include "utils.h"
#include "stm32f10x_gpio.h"

void delay(uint32_t count){
	//@brief delay some time
	//@param count number of steps
	while (--count);
}

void LED_Init(void){
	//@brief intial LED port and LED pin
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_Pin | LED2_Pin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void set_led1(FunctionalState state){
	//@brief turn on or off led1
	//@param state on or off to be set to led1
	if(state == ENABLE){
		GPIO_WriteBit(LED_PORT, LED1_Pin, (BitAction) (1));
	} else {
		GPIO_WriteBit(LED_PORT, LED1_Pin, (BitAction) (0));
	}
}

void set_led2(FunctionalState state){
	//@brief turn on or off led1
	//@param state on or off to be set to led1
	if(state == ENABLE){
		GPIO_WriteBit(LED_PORT, LED2_Pin, (BitAction) (1));
	} else {
		GPIO_WriteBit(LED_PORT, LED2_Pin, (BitAction) (0));
	}
}

void twinkle_led(uint32_t count, uint32_t time){
	//@brief twinkle led1 and led2 in count times
	//@param count twinkle times
	//@param time delay times between each one twinkle
		while(--count){
			set_led1(ENABLE);
			set_led2(DISABLE);
			delay(time);
			set_led1(DISABLE);
			set_led2(ENABLE);
			delay(time);
		}
}

void twinkle_led_second(uint32_t count, uint32_t time_s){
	//@brief twinkle led1 and led2 in count times
	//@param count twinkle times
	//@param time delay times between each one twinkle
		while(--count){
			set_led1(ENABLE);
			set_led2(DISABLE);
			delay_s(time_s);
			set_led1(DISABLE);
			set_led2(ENABLE);
			delay_s(time_s);
		}
}

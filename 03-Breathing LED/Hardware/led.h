/*
@file led.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for led.c
*/
#include "stm32f10x.h"

#ifndef __LED_H
#define __LED_H
//@def define port and gpio pin for LED1
#define LED_PORT GPIOB
#define LED1_Pin GPIO_Pin_0
#define LED2_Pin GPIO_Pin_1

void LED_Init(void);
void twinkle_led(uint32_t count, uint32_t time);
void twinkle_led_second(uint32_t count, uint32_t time_s);
void set_led1(FunctionalState state);
void set_led2(FunctionalState state);
void breathing_led(uint32_t count);

#endif

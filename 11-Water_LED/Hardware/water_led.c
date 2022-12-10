/***
* @file water_led.c
* @version 0.1
* @author magic.liu
* @date 11-21-2022
* @brief c sorce file for water led function
***/

#include "water_led.h"
#include "utils.h"
#include "stm32f10x_gpio.h"

void Water_LED_Init(void){
	/***@brief inital GPIO Pins for water led***/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(WATER_LED_PORT, &GPIO_InitStructure);
	GPIO_Write(WATER_LED_PORT, 0xFFFF);
}

void Water_LED_Run(void){
	int8_t i;
	for(i = 0; i < 8; i++){
		GPIO_Write(WATER_LED_PORT, ~(1<<i));
		delay_ms(100);
	}
	for(i = 1; i < 9; i++){
		GPIO_Write(WATER_LED_PORT, ~(0x80>>i));
		delay_ms(100);
	}
	uint8_t b[4] = {0x81, 0xc3, 0xe7, 0xff};
	for(i = 0; i < 4; i++){
		GPIO_Write(WATER_LED_PORT, b[i]);
		delay_ms(100);
	}
	for(i = 3; i >= 0; i--){
		GPIO_Write(WATER_LED_PORT, b[i]);
		delay_ms(100);
	}
	for(i = 0; i < 4; i++){
		GPIO_Write(WATER_LED_PORT, ~b[i]);
		delay_ms(100);
	}
	for(i = 3; i >= 0; i--){
		GPIO_Write(WATER_LED_PORT, ~b[i]);
		delay_ms(100);
	}
	int8_t a[4] = {0x81, 0x42, 0x24, 0x18};
	for(i = 0; i < 4; i++){
		GPIO_Write(WATER_LED_PORT, a[i]);
		delay_ms(100);
	}
	for(i = 3; i >= 0; i--){
		GPIO_Write(WATER_LED_PORT, a[i]);
		delay_ms(100);
	}
	for(i = 0; i < 4; i++){
		GPIO_Write(WATER_LED_PORT, ~a[i]);
		delay_ms(100);
	}
	for(i = 3; i >= 0; i--){
		GPIO_Write(WATER_LED_PORT, ~a[i]);
		delay_ms(100);
	}
}

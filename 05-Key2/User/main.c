/*
@file maic.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief main function for led_demo project
*/
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "utils.h"
#include "stm32f10x_gpio.h"



void RCC_Configuration(void){
	//@brief inital RCC
	ErrorStatus HSEStartUpStatus;   
	RCC_DeInit();               
	RCC_HSEConfig(RCC_HSE_ON);  
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS){    
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);    
			RCC_HCLKConfig(RCC_SYSCLK_Div1);   

			RCC_PCLK1Config(RCC_HCLK_Div2);  
			RCC_PCLK2Config(RCC_HCLK_Div1);  

			FLASH_SetLatency(FLASH_Latency_2); 

			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 
			RCC_PLLCmd(ENABLE);
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); 
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
			while(RCC_GetSYSCLKSource() != 0x08);   
	}
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |   
//    RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);     
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);        
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
}  

int main(void){
	//@brief main function
	RCC_Configuration();
	LED_Init();
	Key_Init();
	//uint8_t MENU = 6;
	uint8_t debounce_ms = 10;
	set_led1((FunctionalState) 0);
	set_led2((FunctionalState) 0);
	uint8_t key_number = 0;
	while(1){
//		switch (MENU){
//			case 0: set_led1(ENABLE); break;
//			case 1: set_led1(DISABLE); break;
//			case 2: set_led2(ENABLE); break;
//			case 3: set_led2(DISABLE); break;
//			case 4:	twinkle_led(1000, 5000000); break;
//			case 5: twinkle_led_second(1000, 1); break;
//			case 6: breathing_led(500000); break;
//			default: break;
//		}
		if(!GPIO_ReadInputDataBit(KEY_PORT, KEY1_Pin)){ // key is closed
			delay_ms(debounce_ms); //debounce key
			if(!GPIO_ReadInputDataBit(KEY_PORT, KEY1_Pin)){ //key is still closed after debounce time
				key_number++;
				if(key_number > 3){
					key_number = 0;
				}
				switch (key_number){
					case 0: set_led1(DISABLE); set_led2(DISABLE); break;
					case 1: set_led1(ENABLE); set_led2(DISABLE); break;
					case 2: set_led1(ENABLE); set_led2(ENABLE); break;
					case 3: set_led1(ENABLE); set_led2(DISABLE); break;
					default: break;
				}
				while(!GPIO_ReadInputDataBit(KEY_PORT, KEY1_Pin)); // waiting key to release.
			}
		}
	}
}

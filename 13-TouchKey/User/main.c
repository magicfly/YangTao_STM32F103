/*
@file maic.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief main function for led_demo project
*/
#include "stm32f10x.h"
#include "led.h"
#include "touchkey.h"
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
	TOUCHKey_Init();
	//uint8_t MENU = 6;
	uint8_t key1_flag = 0;
	uint8_t key2_flag = 0;
	uint8_t key3_flag = 0;
	uint8_t key4_flag = 0;
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
			if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE){
				while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE);
				if(key1_flag ==0){
					set_led1(ENABLE);
					key1_flag = 1;
				}else{
					set_led1(DISABLE);
					key1_flag = 0;
				}
			}
			if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY2_Pin) == DISABLE){
				while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY2_Pin) == DISABLE);
				if(key2_flag ==0){
					set_led2(ENABLE);
					key2_flag = 1;
				}else{
					set_led2(DISABLE);
					key2_flag = 0;
				}
			}
			if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY3_Pin) == DISABLE){
				while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY3_Pin) == DISABLE);
				if(key3_flag ==0){
					set_led1(ENABLE);
					set_led2(DISABLE);
					key3_flag = 1;
				}else{
					set_led1(DISABLE);
					set_led2(ENABLE);
					key3_flag = 0;
				}
			}
			if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY4_Pin) == DISABLE){
				while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY4_Pin) == DISABLE);
				if(key4_flag ==0){
					set_led1(ENABLE);
					set_led2(ENABLE);
					key4_flag = 1;
				}else{
					set_led1(DISABLE);
					set_led2(DISABLE);
					key4_flag = 0;
				}
			}
		}
	}

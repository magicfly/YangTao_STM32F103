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
	uint8_t long_push_limitation = 200;
	uint8_t second_push_max_interval = 10;
	uint8_t long_push_count = 0;
	uint8_t twice_click_flag = 0;

	while(1){
			if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE){
				delay_ms(20); //debounce
				if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE){
					while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE && long_push_count < long_push_limitation){
						delay_ms(10);
						long_push_count++;
					}
				}
				// if key is release or long_push_count >= 200(2000 ms)
				if(long_push_count >= long_push_limitation){
					// push time longger than limitation, it is a long push, Turn off both LEDs
					while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE);
					set_led1(ENABLE);
					set_led2(ENABLE);
				}else{
					// it is not a long push
					for(uint8_t i =0; i <= second_push_max_interval; i++){
						delay_ms(20);
						if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE){
							delay_ms(20); //debounce
							if((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE){
								twice_click_flag = 1;
								set_led1(DISABLE);
								set_led2(DISABLE);
								while((FunctionalState)GPIO_ReadInputDataBit(TOUCHKEY_PORT, TOUCHKEY1_Pin) == DISABLE);
							}
						}
					}
					if(twice_click_flag == 0){
						FunctionalState current_state = (FunctionalState)GPIO_ReadOutputDataBit(LED_PORT, LED1_Pin);
						if(current_state == DISABLE){
							set_led1(ENABLE);
						}else set_led1(DISABLE);
					}
				}
			}
			long_push_count = 0;
			twice_click_flag = 0;
		}
	}

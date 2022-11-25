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
#include "flash.h"
#include "buzzer.h"
#include "usart.h"
#include "utils.h"
#include "stm32f10x_gpio.h"

#define STORED_ADDRESS 0x0801f000
#define BANDRATE 115200

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

void select_key_operation(uint8_t key){
	switch (key){
			case 0: set_led1(DISABLE); set_led2(DISABLE); break;
			case 1: set_led1(ENABLE); set_led2(DISABLE); break;
			case 2: set_led1(ENABLE); set_led2(ENABLE); break;
			case 3: set_led1(DISABLE); set_led2(ENABLE); break;
			default: break;
		}
}
int main(void){
	//@brief main function
	RCC_Configuration();
	LED_Init();
	Key_Init();
	Buzzer_Init();
	USART1_Init(BANDRATE);
	//uint8_t MENU = 6;
	uint8_t debounce_ms = 10;
	set_led1((FunctionalState) 0);
	set_led2((FunctionalState) 0);
	uint8_t key_number = (uint8_t) Flash_R_HalfWord(STORED_ADDRESS);
	select_key_operation(key_number);
	
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
		//printf("%c", 0x55);
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET){
			uint8_t byte_received = USART_ReceiveData(USART1);
			switch (byte_received){
				case '0': set_led1(DISABLE); printf("0:LED1 OFF \n\r"); break;
				case '1': set_led1(ENABLE); printf("1:LED1 ON \n\r"); break;
				case '2': set_led2(DISABLE);printf("2:LED2 OFF \n\r"); break;
				case '3': set_led2(ENABLE); printf("3:LED2 ON \n\r"); break;
				case '4': Buzzer_Khz(200, 1); printf("4:Buzzer 200 times at 1khz \n\r"); break;
				case '5': Buzzer_Hz(5000, 5000); printf("5:Buzzer 5000 times at 5000hz \n\r"); break;
				default: break;
			}
		}
		if(!GPIO_ReadInputDataBit(KEY_PORT, KEY1_Pin)){ // key is closed
			delay_ms(debounce_ms); //debounce key
			if(!GPIO_ReadInputDataBit(KEY_PORT, KEY1_Pin)){ //key is still closed after debounce time
				key_number++;
				if(key_number > 3){
					key_number = 0;
				}
				select_key_operation(key_number);
				Buzzer_Khz(200, 1);
				while(!GPIO_ReadInputDataBit(KEY_PORT, KEY1_Pin)); // waiting key to release.
				Buzzer_Hz(500, 5000);
			}
		}
	}
}

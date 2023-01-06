/*
@file maic.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief main function for led_demo project
*/
#include "stm32f10x.h"
#include "tm1640.h"
#include "rtc.h"
#include "utils.h"
#include "stm32f10x_gpio.h"
#include "turnencoder.h"

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
}  

int main(void){
	//@brief main function
	RCC_Configuration();
	TM1640_Init();
	TM1640_Clear_All();
	TM1640_Display_off();
	TurnEncoder_Init();
	uint8_t counter = 0;
	TM1640_Display_Number_With_Address(GRID1, counter / 10, DISABLE, 5);
	TM1640_Display_Number_With_Address(GRID2, counter % 10, DISABLE, 5);
	while(1){
		uint8_t code = Get_Encoder();
		if(code == 3){
			counter = 0;
		}else if(code == 1){
			if(counter <= 0){
				counter = 0;
			}else{
				counter -= 1;
			}
			
		}else if(code == 2){
			if(counter >= 99){
				counter = 99;
			}else{
				counter += 1;
			}
		}else{
			__nop();
		}
		TM1640_Display_Number_With_Address(GRID1, counter / 10, DISABLE, 5);
		TM1640_Display_Number_With_Address(GRID2, counter % 10, DISABLE, 5);
	}
}

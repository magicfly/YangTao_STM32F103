/*
@file maic.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief main function for led_demo project
*/
#include "stm32f10x.h"
#include "oled0561.h"
#include "rtc.h"
#include "utils.h"
#include "stm32f10x_gpio.h"
#include "LM75A.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define NEG 0x02
#define DOT 0x01
#define LIGHTNESS 5

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
	char buf[100];
	char str_temp[13] = "Temperature: ";
	RCC_Configuration();
	I2C1_Configration();
	delay_s(1);
	OLED_Init();
	while(1){
		double temp = LM75A_GetTemp();
		sprintf(buf, "%.3f", temp);
		OLED_Display_8x16_Buffer(0, str_temp);
		OLED_Display_8x16_Buffer(2, buf);
		delay_s(1);
	}
}

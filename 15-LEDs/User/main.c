/*
@file maic.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief main function for led_demo project
*/
#include "stm32f10x.h"
#include "tm1640.h"
#include "utils.h"
#include "stm32f10x_gpio.h"

#define COMCATHODE

#ifdef COMANODE
	unsigned char const DispCode[10] = {
		0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
	};
#endif 

#ifdef COMCATHODE
	unsigned char const DispCode[10] = {
		0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
	};
#endif

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
	uint8_t sec_display[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x8, 0x09};
	uint8_t count = 0;
	while(1){
		TM1640_Clear_All();
		uint8_t start_number = count;
		for(uint8_t i = GRID1; i <= GRID8; i++){
			TM1640_Fix_Address_Display(GRID1 + i, DispCode[sec_display[start_number]], 5);
			start_number++;
			if(start_number >= 10) start_number = 0;
		}
		for(uint8_t j = 0; j < 8; j++){
			TM1640_LED_Display(0x01 << j, 5);
			delay_ms(200);
		}
		count++;
		if(count >= 10) count = 0;
	}
}

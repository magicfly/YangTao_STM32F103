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
#include "LM75A.h"
#include "stdlib.h"

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
	RCC_Configuration();
	TM1640_Init();
	TM1640_Clear_All();
	TM1640_Display_off();
	I2C1_Configration();
	while(1){
		double temp = LM75A_GetTemp();
		uint8_t grid_start = GRID1;
		if(temp < 0.0){
			TM1640_Fix_Address_Display(GRID1, NEG, LIGHTNESS);
			grid_start++;
		}
		uint16_t int_temp = abs((int)temp);
		uint8_t individual = int_temp % 10;
		uint8_t ten = (int_temp / 10) % 10;
		uint8_t hundred = (int_temp / 100) % 10;
		if(hundred != 0){
			TM1640_Display_Number_With_Address(grid_start, hundred, DISABLE, LIGHTNESS);
			grid_start++;
			TM1640_Display_Number_With_Address(grid_start, ten, DISABLE, LIGHTNESS);
			grid_start++;
			TM1640_Display_Number_With_Address(grid_start, individual, ENABLE, LIGHTNESS);
			grid_start++;
		}else if(ten !=0){
			TM1640_Display_Number_With_Address(grid_start, ten, DISABLE, LIGHTNESS);
			grid_start++;
			TM1640_Display_Number_With_Address(grid_start, individual, ENABLE, LIGHTNESS);
			grid_start++;
		}else{
			TM1640_Display_Number_With_Address(grid_start, individual, ENABLE, LIGHTNESS);
			grid_start++;
		}
		uint8_t dot_temp = ((int)(temp * 10)) % 10;
		TM1640_Display_Number_With_Address(grid_start, dot_temp, DISABLE, LIGHTNESS);
		grid_start++;
		dot_temp = ((int)(temp * 100)) % 10;
		TM1640_Display_Number_With_Address(grid_start, dot_temp, DISABLE, LIGHTNESS);
		grid_start++;
		dot_temp = ((int)(temp * 1000)) % 10;
		TM1640_Display_Number_With_Address(grid_start, dot_temp, DISABLE, LIGHTNESS);
		grid_start++;
		delay_s(1);
	}
}

/*
@file turnencoder.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief source file for driver of turn encoder 
*/
#include "turnencoder.h"
#include "utils.h"

uint8_t KEY_STUCK_FLAG;

void TurnEncoder_Init(void){
	
	/***@brief initial the ports which are used by turning encoder***/
	RCC_APB2PeriphClockCmd(RCC_TurnEncoder_1 | RCC_TurnEncoder_2, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = KEY1_Pin | KEY2_Pin;
	GPIO_Init(Port_TurnEncoder_1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = KEY3_Pin;
	GPIO_Init(Port_TurnEncoder_2, &GPIO_InitStructure);
	KEY_STUCK_FLAG = 0;
}

uint8_t Get_Encoder(void){
	/***@brief get encoder data from turning encoder
	*@return 3-key 3 is pushed, 1-key is turned left, 2-key is turned right, 0-nothing is happend
	***/
	uint16_t timeout_counter = 0;
	if(!GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) || !GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin)) KEY_STUCK_FLAG = 0;
	if(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY1_Pin) == RESET){
		delay_ms(2); //debounce
		if(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY1_Pin) == RESET){
			while(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY1_Pin) == RESET);
			return 3;
		};
	}else{
		if(GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin) == RESET && KEY_STUCK_FLAG == 0){
			delay_ms(2); //debounce
			if(GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin) == RESET){
				while(GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin) == RESET){
					if(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) == RESET){
						delay_ms(2); //debounce
						if(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) == RESET){
							timeout_counter = 0;
							while(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) == RESET && timeout_counter < 60000){
								timeout_counter++;
								delay_us(20);
							}
							if(timeout_counter >= 60000) KEY_STUCK_FLAG = 1;
							return 1;
						}
					}
				}
			}
		}
		if(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) == RESET && KEY_STUCK_FLAG == 0){
			delay_ms(2); //debounce
			if(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) == RESET){
				while(GPIO_ReadInputDataBit(Port_TurnEncoder_1, KEY2_Pin) == RESET){
					if(GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin) == RESET){
						delay_ms(2); //debounce
						if(GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin) == RESET){
							timeout_counter = 0;
							while(GPIO_ReadInputDataBit(Port_TurnEncoder_2, KEY3_Pin) == RESET && timeout_counter < 60000){
								timeout_counter++;
								delay_us(20);
							}
							if(timeout_counter >= 60000) KEY_STUCK_FLAG = 1;
							return 2;
						}
					}
				}
			}
		}
	}
	return 0;
}

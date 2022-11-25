/*
@file buzzer.c
@version 0.1
@author magic.liu
@date 11-24-2022
@brief source file for buzzer functions
*/
#include "utils.h"
#include "buzzer.h"

void Buzzer_Init(void){
	/*@brief initial buzzer port PB5
	*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = Buzzer_Pin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
	
	GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 1);
}

void Buzzer_Khz(uint32_t count, uint32_t freq_khz){
	/*@brief buzze the buzzer serial times in the specify frequency
	@param [in] count times to buzzer
	@param [in] freq_khz frequency in khz to buzzer
	*/
	float delay_time = (1.0 / freq_khz ) / 2.0 * 1000;
	uint64_t delay_time_us = (uint64_t) delay_time;
	while(count--){
		GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 0);
		delay_us(delay_time_us);
		GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 1);
		delay_us(delay_time_us);
	}
	GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 1);
}

void Buzzer_Hz(uint32_t count, uint32_t freq_hz){
	/*@brief buzze the buzzer serial times in the specify frequency
	@param [in] count times to buzzer
	@param [in] freq_hz frequency in hz to buzzer
	*/
	float delay_time = ((1.0 / freq_hz ) / 2.0) * 1000 * 1000;
	uint32_t delay_time_us = (uint32_t) delay_time;
	while(count--){
		GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 0);
		delay_us(delay_time_us);
		GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 1);
		delay_us(delay_time_us);
	}
	GPIO_WriteBit(BUZZER_PORT, Buzzer_Pin, (BitAction) 1);
}

void Play_MIDI(uint16_t data[]){
	/*@brief play MIDI via buzzer
	@param [in] MIDI data in format:[frequency in hz, play time in ms,
																	 frequency in hz, play time in ms,......]
	*/
	uint16_t array_length = 0;
	while(*data){
		data++;
		array_length++;
	}
	data = data - array_length; //set point of arrary to the start of arrary again
	uint16_t half_length = array_length / 2;
	for(uint16_t i = 0; i < half_length; i++){
		uint32_t freq_hz = data[2 * i];
		uint32_t time_ms = data[2 * i + 1];
		uint32_t count = (uint32_t) (time_ms * freq_hz / 1000);
		Buzzer_Hz(count, freq_hz);
	}
	
}

/*
@file buzzer.h
@version 0.1
@author magic.liu
@date 11-24-2022
@brief head file for buzzer.c
*/

#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"

#define BUZZER_PORT GPIOB
#define Buzzer_Pin GPIO_Pin_5

void Buzzer_Init(void);
void Buzzer_Khz(uint32_t count, uint32_t freq_khz);
void Buzzer_Hz(uint32_t count, uint32_t freq_hz);
void Play_MIDI(uint16_t data[]);

#endif

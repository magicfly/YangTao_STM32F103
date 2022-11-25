/*
@file usart.h
@version 0.1
@author magic.liu
@date 11-24-2022
@brief head file for usart.c
*/

#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define USART_n USART1
/*buffer length for different USART interface*/
#define USART1_REC_LEN 200
#define USART2_REC_LEN 200
#define USART3_REC_LEN 200
/*enable or disable USART interface*/
#define EN_USART1 1
#define EN_USART2 0
#define EN_USART3 0
/*defince buffer for different USART interface*/
extern uint8_t USART1_RX_BUF[USART1_REC_LEN];
extern uint8_t USART2_RX_BUF[USART1_REC_LEN];
extern uint8_t USART3_RX_BUF[USART1_REC_LEN];

extern uint16_t USART1_RX_STA;
extern uint16_t USART2_RX_STA;
extern uint16_t USART3_RX_STA;

void USART1_Init(u32 bound);//initial usart1
void USART2_Init(u32 bound);//initial usart2
void USART3_Init(u32 bound);//initial usart3
void USART1_printf(char* fmt,...); //printf for usart1
void USART2_printf(char* fmt,...); //printf for usart2
void USART3_printf(char* fmt,...); //printf for usart3

#endif

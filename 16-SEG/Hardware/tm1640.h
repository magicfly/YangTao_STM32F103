/*
@file tm1640.h
@version 0.1
@author magic.liu
@date 12-17-2022
@brief head file for tm1640.c
*/

#ifndef __TM1640_H
#define __TM1640_H

#include "stm32f10x.h"

#define RCC_TM1640 RCC_APB2Periph_GPIOA
#define TM1640_Port GPIOA
#define SCLK GPIO_Pin_11
#define DIN GPIO_Pin_12

#define tSETUP_us 1
#define tWAIT_us 10
#define tHOLD_us 1

#define DATA_CMD_ADDRESS_AUTO_ADD 0x40
#define DATA_CMD_FIX_ADDRESS 0x44
#define GRID1 0xc0
#define GRID2 0xc1
#define GRID3 0xc2
#define GRID4 0xc3
#define GRID5 0xc4
#define GRID6 0xc5
#define GRID7 0xc6
#define GRID8 0xc7
#define GRID9 0xc8
#define GRID10 0xc9
#define GRID11 0xca
#define GRID12 0xcb
#define GRID13 0xcc
#define GRID14 0xcd
#define GRID15 0xce
#define GRID16 0xcf

#define DIS_CMD_OFF 0x80
#define DIS_CMD_ON_0 0x88
#define DIS_CMD_ON_1 0x89
#define DIS_CMD_ON_2 0x8a
#define DIS_CMD_ON_3 0x8b
#define DIS_CMD_ON_4 0x8c
#define DIS_CMD_ON_5 0x8d
#define DIS_CMD_ON_6 0x8e
#define DIS_CMD_ON_7 0x8f

#define LEDS_GRID GRID9

void TM1640_Init(void);
void TM1640_Clear_All(void);
void TM1640_Display_off(void);
void TM1640_LED_Display(uint8_t dis_num, uint8_t lightness);
void TM1640_Fix_Address_Display(uint8_t sec, uint8_t data, uint8_t lightness);
void TM1640_Auto_Display(uint8_t sec, uint8_t data[], uint8_t data_length, uint8_t lightness);
void TM1640_Display_Number_With_Address(uint8_t sec, unsigned char number, FunctionalState dot, uint8_t lightness);
#endif

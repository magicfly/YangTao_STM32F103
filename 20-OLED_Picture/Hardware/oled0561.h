/*
@file oled0561.h
@version 0.1
@author magic.liu
@date 01-07-2023
@brief head file for oled0561.c
*/

#ifndef __OLED_H
#define __OLED_H

#include "I2C_1.h"

#define OLED_ADDRESS 0x78
#define OLED_COMMAND 0x00
#define OLED_DATA 0x40

void OLED_Init(void);
void OLED_Display_ON(void);
void OLED_Display_OFF(void);
void OLED_Display_Lightness(uint8_t lightness);
void OLED_Display_Clear(void);
void OLED_Display_8x16(uint8_t page_x, uint8_t col_y, uint16_t word);
void OLED_Display_8x16_Buffer(uint8_t row_page, uint8_t* str);
void OLED_Display_Pic(uint8_t * nBitmapDot);
void OLED_Display_16x16(uint8_t page_x, uint8_t col_y, uint16_t word);

#endif

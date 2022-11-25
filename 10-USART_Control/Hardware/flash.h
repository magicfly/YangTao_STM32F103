/*
@file flash.h
@version 0.1
@author magic.liu
@date 11-23-2022
@brief head file for flash.c
*/

#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f10x.h"

void Flash_W_HalfWord(uint32_t address, uint16_t data);
uint16_t Flash_R_HalfWord(uint32_t address);
void Flash_W_Word(uint32_t address, uint32_t data);
uint32_t Flash_R_Word(uint32_t address);

#endif

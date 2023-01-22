/*
@file I2C_1.h
@version 0.1
@author magic.liu
@date 11-21-2022
@brief head file for I2C_1.c
*/

#ifndef __I2C_1_H
#define __I2C_1_H

#include "stm32f10x.h"

#define RCC_I2C1 RCC_APB2Periph_GPIOB
#define I2C1_Port GPIOB
#define SCL GPIO_Pin_6
#define SDA GPIO_Pin_7

#define i2c1_speed 100000; //100khz
#define default_i2c1_address 0xc0; //default i2c master address

void I2C1_Configration(void);
void I2C1_Send_Byte(uint8_t slaveAddress, uint8_t regAddress, uint8_t byte);
void I2C1_Send_Buffer(uint8_t slaveAddress, uint8_t regAddress, uint8_t* buffer, uint16_t byte_length);
uint8_t I2C1_Read_Byte(uint8_t slaveAddress, uint8_t regAddress);
void I2C1_Read_Buffer(uint8_t slaveAddress, uint8_t regAddress, uint8_t* buffer, uint16_t byte_length_to_read);
#endif

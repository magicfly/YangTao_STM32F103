/*
@file LM75A.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief c source file for LM75A(temperature sensor) function
*/

#include "LM75A.h"

double LM75A_GetTemp(void){
	/***@brief get temperature data from LM75A
	*@return a double type data which is the temperature read from LM75A
	***/
	double sign_flag;
	uint8_t buffer[2];
	I2C1_Read_Buffer(LM75A_ADDRESS, 0x00, buffer, 2);
	uint8_t signed_data = buffer[0];
	sign_flag = +1.0;
	if(signed_data & 0x80){
		sign_flag = -1.0;
		signed_data = ~signed_data;
		signed_data++;
	}
	return sign_flag * (signed_data + (buffer[1] >> 5) * 0.125);
}

void LM75A_PwrDown(void){
	/***@brief set LM75A to power down mode***/
	uint8_t get_setting = LM75A_Get_Conf_Register();
	get_setting = get_setting | 0x01;
	LM75A_Set_Conf_Register(get_setting);
}

void LM75A_Set_Conf_Register(uint8_t conf_mask){
	/***@brief write setting to configration register of LM75A
	*@param conf_mask configration data which you want to write into LM75A
	***/
	I2C1_Send_Byte(LM75A_ADDRESS, 0x01, conf_mask);
}

uint8_t LM75A_Get_Conf_Register(void){
	/***@brief get setting from configration register of LM75A***/
	return I2C1_Read_Byte(LM75A_ADDRESS, 0x01);
}

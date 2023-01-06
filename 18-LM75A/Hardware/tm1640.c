/*
@file tm1640.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief c source file for driver of TM1640
*/

#include "tm1640.h"
#include "utils.h"

#define COMCATHODE

#ifdef COMANODE
	unsigned char const DispCode[10] = {
		0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
	};
#endif 

#ifdef COMCATHODE
	unsigned char const DispCode[10] = {
		0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
	};
#endif
	
void TM1640_Init(void){
	/***@brief initial SCLK AND DIN pin for TM1640***/
	RCC_APB2PeriphClockCmd(RCC_TM1640, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = SCLK | DIN;
	GPIO_Init(TM1640_Port, &GPIO_InitStructure);
}

void Set_SCLK(void){
	/***@brief set SCLK pin to 1b***/
	GPIO_WriteBit(TM1640_Port, SCLK, (BitAction) 1);
}

void Release_SCLK(void){
	/***@brief release SCLK pin to 0b***/
	GPIO_WriteBit(TM1640_Port, SCLK, (BitAction) 0);
}

void Set_DIN(void){
	/***@brief set DIN pin to 1b***/
	GPIO_WriteBit(TM1640_Port, DIN, (BitAction) 1);
}

void Release_DIN(void){
	/***@brief release DIN pin to 0b***/
	GPIO_WriteBit(TM1640_Port, DIN, (BitAction) 0);
}

void TM1640_Start(void){
	/***@brief start the frame to send data to TM1640***/
	delay_us(tWAIT_us);
	Set_DIN();
	Set_SCLK();
	delay_us(tWAIT_us);
	Set_DIN();
	delay_us(tSETUP_us);
	Release_DIN();
	delay_us(tHOLD_us);
	Release_SCLK();
}

void TM1640_End(void){
	/***@brief end the frame***/
	Release_DIN();
	delay_us(tWAIT_us);
	Set_SCLK();
	delay_us(tWAIT_us);
	Set_DIN();
}

void TM1640_Write_Byte(unsigned char byte){
	/***@brief write one byte to TM1640, LSB first***/
	for(uint8_t i = 0; i < 8; i++){
		Release_SCLK();
		if(byte&0x01){
			Set_DIN();
		}else{
			Release_DIN();
		}
		delay_us(tSETUP_us);
		Set_SCLK();
		delay_us(tWAIT_us);
		Release_SCLK();
		delay_us(tHOLD_us);
		byte >>= 1;
	}
	Release_DIN();
}

void TM1640_Display_off(void){
	/***@brief send command to turn off TM1640***/
	TM1640_Start();
	TM1640_Write_Byte(DIS_CMD_OFF);
	TM1640_End();
}

void TM1640_Display_on(uint8_t britness){
	/***@brief send command to turn on TM1640 with the setting brightness
	*@param britness [in] the setting brightness
	***/
	if(britness > 7) britness = 7;
	britness = DIS_CMD_ON_0 + britness;
	TM1640_Start();
	TM1640_Write_Byte(britness);
	TM1640_End();
}

void TM1640_Fix_Address_Display(uint8_t sec, uint8_t data, uint8_t lightness){
	/***@brief send display data to TM1640 with the given address
	*@param sec [in] the address of the section to display
	*@param data [in] display data
	*@param lightness [in] the brightness
	***/
	TM1640_Start();
	TM1640_Write_Byte(DATA_CMD_FIX_ADDRESS);
	TM1640_End();
	delay_us(tWAIT_us);
	TM1640_Start();
	TM1640_Write_Byte(sec);
	TM1640_Write_Byte(data);
	TM1640_End();
	delay_us(tWAIT_us);
	TM1640_Display_on(lightness);
}

void TM1640_Auto_Display(uint8_t sec, uint8_t data[], uint8_t data_length, uint8_t lightness){
	/***@brief send display data to TM1640 with automatic adding the address
	*@param sec [in] the start address
	*@param data[] [in] display data arrary
	*@param data_length [in] the length of data arrary
	*@param lightness [in] the brightness
	***/
	TM1640_Start();
	TM1640_Write_Byte(DATA_CMD_ADDRESS_AUTO_ADD);
	TM1640_End();
	delay_us(tWAIT_us);
	TM1640_Start();
	TM1640_Write_Byte(sec);
	for(uint8_t i = 0; i < data_length; i++){
		TM1640_Write_Byte(*data);
		data++;
	}
	TM1640_End();
	delay_us(tWAIT_us);
	TM1640_Display_on(lightness);
}

void TM1640_Clear_All(void){
	/***@brief clear the display of all section, write 0 to turn off all***/
	uint8_t data[16] = {0x00};
	TM1640_Auto_Display(GRID1, data, 16, 0);
}

void TM1640_LED_Display(uint8_t dis_num, uint8_t lightness){
	/***@brief set the LEDs display data***/
	TM1640_Fix_Address_Display(LEDS_GRID, dis_num, lightness);
}

void TM1640_Display_Number_With_Address(uint8_t sec, unsigned char number, FunctionalState dot, uint8_t lightness){
	/***@brief send display number to TM1640 with the given address
	*@param sec [in] the address of the section to display
	*@param data [in] display number
	*@param lightness [in] the brightness
	***/
	uint8_t data = 0x00;
	switch(number){
		case 0: {data = DispCode[0]; break;}
		case 1: {data = DispCode[1]; break;}
		case 2: {data = DispCode[2]; break;}
		case 3: {data = DispCode[3]; break;}
		case 4: {data = DispCode[4]; break;}
		case 5: {data = DispCode[5]; break;}
		case 6: {data = DispCode[6]; break;}
		case 7: {data = DispCode[7]; break;}
		case 8: {data = DispCode[8]; break;}
		case 9: {data = DispCode[9]; break;}
		default: {data= 0x00; break;}
	}
	if(dot == ENABLE){
		data += 0x80;
	}
	TM1640_Start();
	TM1640_Write_Byte(DATA_CMD_FIX_ADDRESS);
	TM1640_End();
	delay_us(tWAIT_us);
	TM1640_Start();
	TM1640_Write_Byte(sec);
	TM1640_Write_Byte(data);
	TM1640_End();
	delay_us(tWAIT_us);
	TM1640_Display_on(lightness);
}

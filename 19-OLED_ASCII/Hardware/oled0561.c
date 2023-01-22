/*
@file oled0561.c
@version 0.1
@author magic.liu
@date 01-07-2023
@brief head file for oled0561 driver
*/
#include "oled0561.h"
#include "ASCII_8x16.h"
#include "utils.h"

void OLED_Init(void){
	/***@brief initial OLED0561***/
	uint8_t INIT_DATA[24] = {
		0x00, 0x10, //start adress, 0x00-4b Lower column address, 0x10-4b Higher column address, MSB=0000B LSB=0000B
		0xd5, 0x80, //Set Display Clock Divide Ratio
		0xa8, 0x3f, //Set Multiplex Ratio
		0xd3, 0x00, //Set Display Offset
		0x40,       //Set Display Start Line
		0xb0,       //set page address
		0x8d, 0x14, //VCC power
		0xA1,       //Set Segment Re-Map
		0xC8,       //Set COM Output Scan Direction
		0xDA, 0x12, //Set COM Pins Hardware Configuration
		0x81, 0xff, //Set Contrast Control
		0xD9, 0xf1, //Set Pre-Charge Period
		0xDB, 0x30, //Set VCOMH Deselect Level
		//0x20, 0x00,
		0xa4,       //set normal display status
		0xa6,       //set normal display
	};
	OLED_Display_OFF();
	OLED_Display_Clear();
	I2C1_Send_Buffer(OLED_ADDRESS, OLED_COMMAND, INIT_DATA, 24);
	OLED_Display_ON();
}

void OLED_Display_OFF(void){
	/***@brief turn off the display of OLED0561***/
	uint8_t off_data[3] = {0xae, 0x8d, 0x10};
	I2C1_Send_Buffer(OLED_ADDRESS, OLED_COMMAND, off_data, 3);
	delay_ms(100);
}

void OLED_Display_ON(void){
	/***@brief turn on the display of OLED0561***/
	uint8_t off_data[1] = {0xaf};
	I2C1_Send_Buffer(OLED_ADDRESS, OLED_COMMAND, off_data, 1);
	delay_ms(100);
}

void OLED_Display_Lightness(uint8_t lightness){
	/***@brief set display Contrast of OLED0561
	*@param lightness the contrast to set
	***/
	I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, 0x81);
	I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, lightness);
}

void OLED_Display_Clear(void){
	/***@brief clear display of OLED0561***/
	uint8_t page;
	uint8_t cols;
	for(page=0xb0; page <= 0xb7; page++){
		I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, page); //send page address to oled
		I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, 0x10); //4 bit MSB of column address 0000
		I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, 0x00); //4 bit LSB of column address 0000
		for(cols = 0; cols <= 131; cols++){
			I2C1_Send_Byte(OLED_ADDRESS, OLED_DATA, 0x00); // write 0x00 to all register
		}
	}
}

void OLED_Display_8x16(uint8_t page_x, uint8_t col_y, uint16_t word){
	/***@brief display a 8*16 ascii code on OLED0561
	*@param page_x display start at the page: 0~7 which means 0xb0~0xb7
	*@param col_y display start at the column 
	*@param word ascii code of the display char
	***/
	col_y += 0x02; //the oled display start at column 2
	uint8_t ascii_offset, total_pages, total_cols = 0;
	for(total_pages = 0; total_pages < 2; total_pages++){ //8*16, ocupy 16 rows which means 2 pages
		I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, 0xb0 + page_x); //send page address to oled
		I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, col_y / 16 + 0x10); //4 bit MSB of column address 0000
		I2C1_Send_Byte(OLED_ADDRESS, OLED_COMMAND, col_y % 16); //4 bit LSB of column address 0000
		for(total_cols = 0; total_cols < 8; total_cols++){//send display data per column
			I2C1_Send_Byte(OLED_ADDRESS, OLED_DATA, ASCII_8x16[word * 16 + ascii_offset - 512]);
			ascii_offset++;
		}
		page_x++;
	}
}

void OLED_Display_8x16_Buffer(uint8_t row_page, uint8_t* str){
	/***@brief display a 8*16 ascii code on OLED0561
	*@param row_page display start at the row of pages
	*@param str a string contains display char
	***/
	uint8_t col_mul = 0; // 8 column per char so each char ocupy 8 column, the number is used to record how many 8 column are ocpupied
	while(*str != '\0'){ //string is not at the end
		OLED_Display_8x16(row_page, col_mul*8, *str);
		str++;
		col_mul++;
	}
}

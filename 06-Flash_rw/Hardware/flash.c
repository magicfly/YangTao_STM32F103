/*
@file flash.c
@version 0.1
@author magic.liu
@date 11-23-2022
@brief source file for read and write flash function
*/

#include "flash.h"

void Flash_W_HalfWord(uint32_t address, uint16_t data){
	//@brief write data(half word) into flash at the specify address
	//@param data the data to be writen
	FLASH_Unlock(); // need unlock FLASH first before doing any operation
	FLASH_ClearFlag(FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_EOP); // clear all falsh flags
	FLASH_ErasePage(address); //erase the page which conten the address
	FLASH_ProgramHalfWord(address, data);
	FLASH_Lock();
}

uint16_t Flash_R_HalfWord(uint32_t address){
	//@brief read a half word from flash at the specify address
	//@param address the specify address to read
	return *(uint16_t*) address;
}

void Flash_W_Word(uint32_t address, uint32_t data){
	//@brief write data(word) into flash at the specify address
	//@param data the data to be writen
	FLASH_Unlock(); // need unlock FLASH first before doing any operation
	FLASH_ClearFlag(FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_EOP); // clear all falsh flags
	FLASH_ErasePage(address); //erase the page which conten the address
	FLASH_ProgramWord(address, data);
	FLASH_Lock();
}

uint32_t Flash_R_Word(uint32_t address){
	//@brief read a word from flash at the specify address
	//@param address the specify address to read
	return *(uint32_t*) address;
}

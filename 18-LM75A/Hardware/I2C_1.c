/*
@file I2C_1.c
@version 0.1
@author magic.liu
@date 11-21-2022
@brief c source file for I2C_1 function
*/

#include "I2C_1.h"

void I2C1_Configration(void){
	/***@brief initial/enable gpio port and clock for i2c1***/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_I2C1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SCL | SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(I2C1_Port, &GPIO_InitStructure);
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_ClockSpeed = i2c1_speed;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = default_i2c1_address;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_Init(I2C1, &I2C_InitStructure);
	
	I2C_Cmd(I2C1, ENABLE);
}

void I2C1_Send_Byte(uint8_t slaveAddress, uint8_t regAddress, uint8_t byte){
	/***@brief send one byte to i2c1
	*@param slaveAddress address of slave i2c device
	*@param regAddress register address of i2c device to be write
	*@param byte one byte data to be write
	***/
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); // wait until i2c1 is not busy.
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // Step 1: generate i2c start and wait done
	
	I2C_Send7bitAddress(I2C1, slaveAddress, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Step 2: send slave address and write operation flag, then wait done
	
	I2C_SendData(I2C1, regAddress);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Step 3: send register address and wait done
	
	I2C_SendData(I2C1, byte);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Step 4: send write byte data and wait done
	
	I2C_GenerateSTOP(I2C1, ENABLE); // Step 5: generate i2c stop
}

void I2C1_Send_Buffer(uint8_t slaveAddress, uint8_t regAddress, uint8_t* buffer, uint16_t byte_length){
	/***@brief send multi-bytes to i2c1
	*@param slaveAddress address of slave i2c device
	*@param regAddress register address of i2c device to be write
	*@param buffer a buffer which contains multi-ytes data to be write
	*@param byte_length the length of bytes to write
	***/
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); // wait until i2c1 is not busy.
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // Step 1: generate i2c start and wait done
	
	I2C_Send7bitAddress(I2C1, slaveAddress, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Step 2: send slave address and write operation flag, then wait done
	
	I2C_SendData(I2C1, regAddress);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Step 3: send register address and wait done
	
	for(uint16_t i = 0; i < byte_length; i++){
		I2C_SendData(I2C1, *buffer);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Step 4: send data to device byte by byte and wait done
		buffer++;
	}
	I2C_GenerateSTOP(I2C1, ENABLE); // Step 5: generate i2c stop
}

uint8_t I2C1_Read_Byte(uint8_t slaveAddress, uint8_t regAddress){
	/***@brief read one byte from i2c1
	*@param slaveAddress address of slave i2c device
	*@param regAddress register address of i2c device to be write
	*@return one byte data read from i2c device
	***/
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); // wait until i2c1 is not busy.
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // Step 1: generate i2c start and wait done
	
	I2C_Send7bitAddress(I2C1, slaveAddress, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Step 2: send slave address and write operation flag, then wait done
	
	I2C_SendData(I2C1, regAddress);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Step 3: send register address and wait done
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // Step 4: generate i2c start again and wait done
	
	I2C_Send7bitAddress(I2C1, slaveAddress, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // Step 5: send slave address and read operation flag, then wait done
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); // Step 6: generate the non-ack bit to mark the read end
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET); // Step 7: wait data is received
	
	uint8_t read_byte = I2C_ReceiveData(I2C1); // Step 8: get the received byte from i2c device
	
	I2C_GenerateSTOP(I2C1, ENABLE); // Step 9: generate an i2c stop
	
	return read_byte;
}

void I2C1_Read_Buffer(uint8_t slaveAddress, uint8_t regAddress, uint8_t* buffer, uint16_t byte_length_to_read){
	/***@brief read multi-bytes from i2c1
	*@param slaveAddress address of slave i2c device
	*@param regAddress register address of i2c device to be write
	*@param buffer one buffer which contains datas read from i2c device
	*@param byte_length_to_read length of bytes to read
	***/
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); // wait until i2c1 is not busy.
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // Step 1: generate i2c start and wait done
	
	I2C_Send7bitAddress(I2C1, slaveAddress, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Step 2: send slave address and write operation flag, then wait done
	
	I2C_SendData(I2C1, regAddress);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Step 3: send register address and wait done
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // Step 4: generate i2c start again and wait done
	
	I2C_Send7bitAddress(I2C1, slaveAddress, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // Step 5: send slave address and read operation flag, then wait done
	for(uint16_t i = 0; i < (byte_length_to_read - 1); i++){
		I2C_AcknowledgeConfig(I2C1, ENABLE); // Step 6: generate the ack bit to mark the read is not the last
		while(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET); // Step 7: wait data is received
		*buffer = I2C_ReceiveData(I2C1);
		buffer++;
	}
	I2C_AcknowledgeConfig(I2C1, DISABLE); // Step 8: generate the non-ack bit to mark the last read
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET); // Step 9: wait data is received
	
	*buffer = I2C_ReceiveData(I2C1); // Step 10: get the received byte from i2c device
	
	I2C_GenerateSTOP(I2C1, ENABLE); // Step 11: generate an i2c stop
}

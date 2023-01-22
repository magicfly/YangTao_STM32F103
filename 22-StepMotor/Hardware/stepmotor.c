/*
@file stepmotor.c
@version 0.1
@author magic.liu
@date Jan-22-2023
@brief c sorce file for stepmotor function
*/
#include "stepmotor.h"
#include "utils.h"
#include "stm32f10x_gpio.h"

uint8_t CURRENT_STEP = 0;

void STEPMOTOR_Init(void){
	//@brief intial stepmotor port and stepmotor pin
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //enable AFIO clock so that PA13/PA14 can be remaped
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //remap JTAG Pin
	GPIO_InitStructure.GPIO_Pin = STEPMOTOR_Pin_A | STEPMOTOR_Pin_NA | STEPMOTOR_Pin_B | STEPMOTOR_Pin_NB; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(STEPMOTOR_PORT, &GPIO_InitStructure);
	// default turn off stepmotor in initalization
	STEPMOTOR_OFF();
}

void STEPMOTOR_OFF(void){
	/***@brief turn off step motor***/
	GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
	GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
	GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
	GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
}

void stepmotor_4_step(uint8_t step, uint16_t speed){
	/***@brief run a step for step motor in 4 step mode
	@param step the step of 4 step mode
	***/
	switch(step){
		case 0:{
			// step 0: A/B = 1, NA/NA = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (1));
			break;
		}
		case 1:{
			// step 1: B/NA = 1, NB/A = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (1));
			break;
		}
		case 2:{
			// step 2: NA/NB = 1, B/A = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (1));
			break;
		}
		case 3:{
			// step 3: NB/A = 1, B/NA = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (1));
			break;
		}
		default:
			break;
	}
	delay_ms(speed);
	STEPMOTOR_OFF();
}

void stepmotor_8_step(uint8_t step, uint16_t speed){
	/***@brief run a step for step motor in 8 step mode
	@param step the step of 8 step mode
	***/
	switch(step){
		case 0:{
			// step 0: A = 1, B/NA/NB = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (1));
			break;
		}
		case 1:{
			// step 1: A/B = 1, NA/NB = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (1));
			break;
		}
		case 2:{
			// step 2: B = 1, NA/NB/A = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (1));
			break;
		}
		case 3:{
			// step 3: B/NA = 1, NB/A = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (1));
			break;
		}
		case 4:{
			// step 4: NA = 1, NB/A/B = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (1));
			break;
		}
		case 5:{
			// step 5: NA/NB = 1, A/B = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (1));
			break;
		}
		case 6:{
			// step 6: NB = 1, A/B/NA = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (1));
			break;
		}
		case 7:{
			// step 7: NB/A = 1, B/NA = 0.
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NA, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_B, (BitAction) (0));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_A, (BitAction) (1));
			GPIO_WriteBit(STEPMOTOR_PORT, STEPMOTOR_Pin_NB, (BitAction) (1));
			break;
		}
		default:
			break;
	}
	delay_ms(speed);
	STEPMOTOR_OFF();
}

void STEPMOTOR_Run_Steps(uint8_t dir, uint64_t step, uint16_t speed){
	/***@brief run specified step in the defination direction for step motor 
	@param dir the dirrection, 0:left, 1: right
	@param step spicify the steps to run
	***/
	for(uint64_t i = 0; i < step; i++){
		if(dir == 1){
			CURRENT_STEP++;
			if(CURRENT_STEP > 7) CURRENT_STEP = 0;
		}else{
			if(CURRENT_STEP == 0) CURRENT_STEP = 8;
			CURRENT_STEP--;
		}
		stepmotor_8_step(CURRENT_STEP, speed);
	}
}

void STEPMOTOR_Run_Loops(uint8_t dir, uint64_t loop, uint16_t speed){
	/***@brief run specified loops in the defination direction for step motor 
	@param dir the dirrection, 0:left, 1: right
	@param loop spicify the loops to run
	***/
	STEPMOTOR_Run_Steps(dir, loop * STEP_PER_LOOP, speed);
}

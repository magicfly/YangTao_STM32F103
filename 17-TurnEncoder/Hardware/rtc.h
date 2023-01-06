/*
@file rtc.h
@version 0.1
@author magic.liu
@date 12-08-2022
@brief head file for rtc.c
*/

#ifndef __RTC_H
#define __RTC_H

#include "stm32f10x.h"

typedef struct{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint16_t year;
	uint8_t month;
	uint8_t date;
	uint8_t week;
}_calendar_obj;

extern _calendar_obj calendar;
extern uint8_t const mon_table[12];

uint8_t RTC_Init(void);
uint8_t Is_Leap_Year(uint16_t year);
uint8_t RTC_Get(void);
uint8_t RTC_Set(uint16_t syear, uint8_t smonth, uint8_t sday, uint8_t shour, uint8_t smin, uint8_t ssec);
uint8_t RTC_Get_Week(uint16_t year, uint8_t month, uint8_t day);

#endif

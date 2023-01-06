/*
@file rtc.c
@version 0.1
@author magic.liu
@date 12-08-2022
@brief c sorce file for RTC function
*/
#include "rtc.h"
#include "utils.h"
#include "stdio.h"
#include "tm1640.h"

_calendar_obj calendar;
const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5};

uint8_t RTC_Init(void){
	/***@brief initial RTC
	* @return 0: ok, 1: error
	***/
	uint8_t temp_counter = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x5a5a){
		RCC_DeInit();
		RCC_LSEConfig(RCC_LSE_ON); // use LSE clock source
		
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && temp_counter < 250){
			temp_counter++;
			delay_ms(10);
		}
		if(temp_counter >= 250) return 1;
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForLastTask();
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IRQn, ENABLE);
		RTC_WaitForLastTask();
		RTC_EnterConfigMode();
		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();
		RTC_ExitConfigMode();
		BKP_WriteBackupRegister(BKP_DR1, 0x5a5a);
	}else{
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		RTC_WaitForLastTask();
	}
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	return 0;
}

void RTC_IRQHandler(void){
	/***@brief IRQ handler for RTC***/
	if(RTC_GetITStatus(RTC_IT_SEC) != RESET){					
		RTC_Get(); 
  	//printf("Current Time:%d-%d-%d %d:%d:%d\r\n", calendar.year, calendar.month, calendar.date, calendar.hour, calendar.min, calendar.sec);
		TM1640_Display_Number_With_Address(GRID1, calendar.hour / 10, DISABLE, 5);
		TM1640_Display_Number_With_Address(GRID2, calendar.hour % 10, DISABLE, 5);
		TM1640_Fix_Address_Display(GRID3, 0x40, 5);
		TM1640_Display_Number_With_Address(GRID4, calendar.min / 10, DISABLE, 5);
		TM1640_Display_Number_With_Address(GRID5, calendar.min % 10, DISABLE, 5);
		TM1640_Fix_Address_Display(GRID6, 0x40, 5);
		TM1640_Display_Number_With_Address(GRID7, calendar.sec / 10, DISABLE, 5);
		TM1640_Display_Number_With_Address(GRID8, calendar.sec % 10, DISABLE, 5);
	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC | RTC_IT_OW);
	RTC_WaitForLastTask();	  	    						 	   	 
}

uint8_t Is_Leap_Year(uint16_t year){
	/***@brief check if the year is a leap year
	* @param year [in] the year to be checked
	* @return 1: the year is a leap year, 0: the year is not a leap year
	***/
	if(year%4 == 0){
		if(year%100 == 0){
			if(year%400 == 0){
				return 1;
			}else return 0;
		}else return 1;
	}else return 0;
}

uint8_t RTC_Get(void){
	static u16 daycnt = 0;
	uint32_t time_count = 0;
	uint32_t temp = 0;
	uint16_t temp1 = 0;
	
	time_count = RTC_GetCounter();
	temp = time_count / (24 * 60 * 60); // get how many days in counter
	if(daycnt != temp){ // if days >= 1 days
		daycnt = temp;
		temp1 = 1970; // calculate year from 1970
		while(temp >= 365){
			if(Is_Leap_Year(temp1)){
				if(temp >= 366) temp -= 366; // if is a leap year the year has 366 days
				else{
					temp1++;
					break; // if it is a leap year but remain days less than 366 then year calculation is done
				}
			}else temp -= 365;
			temp1++;
		}
		calendar.year = temp1;
		temp1 = 0;
		while(temp >= 28){
			if(Is_Leap_Year(calendar.year) && temp1 == 1){ // if a year is leap year, only in feb days is 29.
				if(temp >= 29) temp -= 29;
				else break;
			}else{
				if(temp >= mon_table[temp1]) temp -= mon_table[temp1];
				else break;
			}
			temp1++;
		}
		calendar.month=temp1 + 1; // get month
		calendar.date=temp + 1; // get date
	}
	temp = time_count % 86400; // get remain seconds less than 1 day
	calendar.hour = temp / 3600;
	calendar.min = (temp % 3600) / 60;
	calendar.sec = (temp % 3600) % 60;
	calendar.week = RTC_Get_Week(calendar.year, calendar.month, calendar.date);
	return 0;
}

uint8_t RTC_Get_Week(uint16_t year, uint8_t month, uint8_t day){	
	uint16_t temp2;
	uint8_t yearH, yearL;
	
	yearH = year / 100;	
	yearL = year % 100; 
	if(yearH > 19) yearL += 100;
	temp2 = yearL + yearL / 4;
	temp2 = temp2 % 7; 
	temp2 = temp2 + day + table_week[month-1];
	if (yearL % 4 == 0 && month < 3) temp2--;
	return (temp2 % 7);
}		

uint8_t RTC_Set(uint16_t syear, uint8_t smonth, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec){
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099) return 1;	   
	for(t=1970;t<syear;t++)
	{
		if(Is_Leap_Year(t)) seccount += 31622400;
		else seccount += 31536000;
	}
	smonth -= 1;
	for(t=0; t < smonth; t++)
	{
		seccount += (u32)mon_table[t] * 86400;
		if(Is_Leap_Year(syear) && t==1) seccount += 86400;	   
	}
	seccount += (u32)(sday-1) * 86400;
	seccount += (u32)hour * 3600;
  seccount += (u32)min * 60;
	seccount += sec;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	RTC_SetCounter(seccount);
 
	RTC_WaitForLastTask();
	return 0;
}

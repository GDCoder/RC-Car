/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: drv_timer.c
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2015.02.01
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            drv_timer.c
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stc15.h>
#include "drv_timer.h"

/*****************************************************************************
 Constants   宏定义
*****************************************************************************/
#define TIMER_START			1
#define TIMER_STOP			0

#define CPU_CLK_HZ			12000000
#define	CLOCK_PERIOD		(0x10000 - INT_PERIOD)

#define TIMER0_MODE			0x01		//定义定时器0为16位定时模式1
#define TIMER1_MODE			0x10		//定义定时器1为16位定时模式1

/*****************************************************************************
 Struct
*****************************************************************************/


/*****************************************************************************
 Global Data
*****************************************************************************/


/*****************************************************************************
 Extern functions
*****************************************************************************/


/*****************************************************************************
 Local variables 
*****************************************************************************/
static u8 u8T3Count1 = 0;
static u8 u8T3Count2 = 0;
static u16 u16T0Count = 0;
static u16 u16T1Count = 0;

/*****************************************************************************
 Local functions
****************************************************************************/


/*****************************************************************************
 implement begin 
*****************************************************************************/
void DRV_Timer3_Int(void) interrupt 19			//Int Vector at 009BH
{
	u16 u16ClockPeriod = CLOCK_PERIOD;

	//停止Timer3(T3R = 0)
	T4T3M &= 0xF7;

	u8T3Count1++;
	if(u8T3Count1 >= 100)
	{
		u8T3Count1 = 0;
	}

	u8T3Count2++;
	if(u8T3Count2 >= 100)
	{
		u8T3Count2 = 0;
	}

	//重新启动Timer3(T3R = 1)
	T4T3M |= 0x08;
}

void DRV_Timer0_Init(void)
{
	u16 u16ClockPeriod = 0;

	//关闭Timer0的中断，停止Timer0计数
	ET0 = TIMER_STOP;
	TR0 = TIMER_STOP;

	//设置Timer0的工作模式
	TMOD |= TIMER0_MODE;

	//设置Timer0的计数初值
	TH0 = u16ClockPeriod >> 8;
	TL0 = u16ClockPeriod & 0xFF;

	//清0 Timer0的中断标志
	TF0 = 0;
}

void DRV_Timer1_Init(void)
{
	u16 u16ClockPeriod = 0;

	//关闭Timer1的中断，停止Timer1计数
	ET1 = TIMER_STOP;
	TR1 = TIMER_STOP;

	//设置Timer1的工作模式
	TMOD |= TIMER1_MODE;

	//设置Timer1的计数初值
	TH1 = u16ClockPeriod >> 8;
	TL1 = u16ClockPeriod & 0xFF;

	//清0 Timer1的中断标志
	TF1 = 0;
}

void DRV_Timer2_Init(void)
{
	//关闭Timer2的中断(ET2 = 0)
	IE2 &= 0xFB;

	//关闭Timer2计数(T2R = 0)
	AUXR &= 0xEF;

	//设置Timer2做串口1的波特率发生器(S1ST2 = 1)
	AUXR &= 0xFE;

	//设置Timer0的计数初值
	T2H = 0xFF;
	T2L = 0xFC;
}

void DRV_Timer3_Init(void)
{
	u16 u16ClockPeriod = CLOCK_PERIOD;

	//关闭Timer3的中断(ET3 = 0)
	IE2 &= 0xDF;

	//停止Timer3计数(T3R = 0)
	T4T3M &= 0xF7;

	//设置Timer3的计数初值
	T3H = u16ClockPeriod >> 8;
	T3L = u16ClockPeriod & 0xFF;

	//开放Timer3的中断(ET3 = 1)
	IE2 |= 0x20;

	//然后允许Timer3计数(T3R = 1)
	T4T3M |= 0x08;
}

void DRV_Timer0_Start(bool b8Enable)
{
	if(TRUE == b8Enable)
	{
		TR0 = TIMER_START;
	}
	else
	{
		TR0 = TIMER_STOP;
	}
}

void DRV_Timer1_Start(bool b8Enable)
{
	if(TRUE == b8Enable)
	{
		TR1 = TIMER_START;
	}
	else
	{
		TR1 = TIMER_STOP;
	}
}

u16 DRV_Timer0_CountGet(void)
{
	u16T0Count = TH0;
	u16T0Count = u16T0Count << 8;
	u16T0Count |= TL0;

	return u16T0Count;
}

u16 DRV_Timer1_CountGet(void)
{
	u16T1Count = TH1;
	u16T1Count = u16T1Count << 8;
	u16T1Count |= TL1;

	return u16T1Count;
}

u8 DRV_Timer3_Count1Get(void)
{
	return u8T3Count1;
}

u8 DRV_Timer3_Count2Get(void)
{
	return u8T3Count2;
}

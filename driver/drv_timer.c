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
 Constants   �궨��
*****************************************************************************/
#define TIMER_START			1
#define TIMER_STOP			0

#define CPU_CLK_HZ			12000000
#define	CLOCK_PERIOD		(0x10000 - INT_PERIOD)

#define TIMER0_MODE			0x01		//���嶨ʱ��0Ϊ16λ��ʱģʽ1
#define TIMER1_MODE			0x10		//���嶨ʱ��1Ϊ16λ��ʱģʽ1

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

	//ֹͣTimer3(T3R = 0)
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

	//��������Timer3(T3R = 1)
	T4T3M |= 0x08;
}

void DRV_Timer0_Init(void)
{
	u16 u16ClockPeriod = 0;

	//�ر�Timer0���жϣ�ֹͣTimer0����
	ET0 = TIMER_STOP;
	TR0 = TIMER_STOP;

	//����Timer0�Ĺ���ģʽ
	TMOD |= TIMER0_MODE;

	//����Timer0�ļ�����ֵ
	TH0 = u16ClockPeriod >> 8;
	TL0 = u16ClockPeriod & 0xFF;

	//��0 Timer0���жϱ�־
	TF0 = 0;
}

void DRV_Timer1_Init(void)
{
	u16 u16ClockPeriod = 0;

	//�ر�Timer1���жϣ�ֹͣTimer1����
	ET1 = TIMER_STOP;
	TR1 = TIMER_STOP;

	//����Timer1�Ĺ���ģʽ
	TMOD |= TIMER1_MODE;

	//����Timer1�ļ�����ֵ
	TH1 = u16ClockPeriod >> 8;
	TL1 = u16ClockPeriod & 0xFF;

	//��0 Timer1���жϱ�־
	TF1 = 0;
}

void DRV_Timer2_Init(void)
{
	//�ر�Timer2���ж�(ET2 = 0)
	IE2 &= 0xFB;

	//�ر�Timer2����(T2R = 0)
	AUXR &= 0xEF;

	//����Timer2������1�Ĳ����ʷ�����(S1ST2 = 1)
	AUXR &= 0xFE;

	//����Timer0�ļ�����ֵ
	T2H = 0xFF;
	T2L = 0xFC;
}

void DRV_Timer3_Init(void)
{
	u16 u16ClockPeriod = CLOCK_PERIOD;

	//�ر�Timer3���ж�(ET3 = 0)
	IE2 &= 0xDF;

	//ֹͣTimer3����(T3R = 0)
	T4T3M &= 0xF7;

	//����Timer3�ļ�����ֵ
	T3H = u16ClockPeriod >> 8;
	T3L = u16ClockPeriod & 0xFF;

	//����Timer3���ж�(ET3 = 1)
	IE2 |= 0x20;

	//Ȼ������Timer3����(T3R = 1)
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

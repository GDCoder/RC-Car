/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: drv_exten.c
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2015.02.02
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            drv_exten.c
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stc15.h>
#include "drv_timer.h"
#include "drv_exten.h"

/*****************************************************************************
 Constants   宏定义
*****************************************************************************/
#define INT0 P32
#define INT1 P33

#define EXTEN_INT_START			1
#define EXTEN_INT_STOP			0

#define EXTEN_INT_RD_EDGE		0
#define EXTEN_INT_D_EDGE		1

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
static bool b8Int0Flag = TRUE;
static bool b8Int1Flag = TRUE;
static u16 u16ThrottlePulseWidth = 1500;
static u16 u16AileronPluseWidth = 1500;

/*****************************************************************************
 Local functions
*****************************************************************************/


/*****************************************************************************
 implement begin 
*****************************************************************************/
void DRV_ExtenInt0_Int(void) interrupt 0	 		//Int Vector at 0003H
{
	bool b8Int0Flag = TRUE;

	//停止Int0中断
	EX0 = EXTEN_INT_STOP;
	
	//保存INT0口的值,用于判定是上升沿中断还是下降沿中断
	b8Int0Flag = INT0;
	if(TRUE == b8Int0Flag)
	{
		DRV_Timer0_Start(TRUE);
	}
	else
	{
		DRV_Timer0_Start(FALSE);
		u16ThrottlePulseWidth = DRV_Timer0_CountGet();
		DRV_Timer0_Init();
	}

	//开放Int0的中断
	EX0 = EXTEN_INT_START;
}

void DRV_ExtenInt1_Int(void) interrupt 2			//Int Vector at 0013H
{
	bool b8Int1Flag = TRUE;

	//停止Int1中断
	EX1 = EXTEN_INT_STOP;
	
	//保存INT1口的值,用于判定是上升沿中断还是下降沿中断
	b8Int1Flag = INT1;	//保存INT0口的值,用于判定是上升沿中断还是下降沿中断
	if(1 == b8Int1Flag)
	{
		DRV_Timer1_Start(TRUE);
	}
	else
	{
		DRV_Timer1_Start(FALSE);
		u16AileronPluseWidth = DRV_Timer1_CountGet();
		DRV_Timer1_Init();
	}

	//开放Int1的中断
	EX1 = EXTEN_INT_START;
}

void DRV_ExtenInt0_Init(void)
{
	//停止Int0中断
	EX0 = EXTEN_INT_STOP;

	//设置Int0的工作模式为上升沿/下降沿触发
	IT0 = EXTEN_INT_RD_EDGE;

	//设置INT0端口为高电平,准备读取电平状态
	INT0 = 1;

	//开放Int0的中断
	EX0 = EXTEN_INT_START;
}

void DRV_ExtenInt1_Init(void)
{
	//停止Int1中断
	EX1 = EXTEN_INT_STOP;

	//设置Int1的工作模式为上升沿/下降沿触发
	IT1 = EXTEN_INT_RD_EDGE;

	//设置INT1端口为高电平,准备读取电平状态
	INT1 = 1;

	//开放Int1的中断
	EX1 = EXTEN_INT_START;
}

void DRV_ExtenInt0_Start(bool b8Enable)
{
	if(TRUE == b8Enable)
	{
		EX0 = EXTEN_INT_START;
	}
	else
	{
		EX0 = EXTEN_INT_STOP;
	}
}

void DRV_ExtenInt1_Start(bool b8Enable)
{
	if(TRUE == b8Enable)
	{
		EX1 = EXTEN_INT_START;
	}
	else
	{
		EX1 = EXTEN_INT_STOP;
	}
}

u16 DRV_ExtenInt0_PulseWidthGet(void)
{
	return u16ThrottlePulseWidth;
}

u16 DRV_ExtenInt1_PulseWidthGet(void)
{
	return u16AileronPluseWidth;
}


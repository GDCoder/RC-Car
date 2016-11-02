/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: drv_timer.h
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2009.03.26
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            drv_timer.h
***************************************************************************/
#ifndef _DRV_TIMER_H_
#define _DRV_TIMER_H_

#include "..\inc\common.h"
#include "..\inc\config.h"

#ifdef  __cplusplus
	extern "C" {
#endif

/*****************************************************************************
 Constants   ∫Í∂®“Â
*****************************************************************************/
#define INT_PERIOD				100			// timer0 interrupt: unit = us

/*****************************************************************************
 Struct
*****************************************************************************/


/*****************************************************************************
functions prototype
*****************************************************************************/
void DRV_Timer3_Int(void);
void DRV_Timer0_Init(void);
void DRV_Timer1_Init(void);
void DRV_Timer2_Init(void);
void DRV_Timer3_Init(void);
void DRV_Timer0_Start(bool b8Enable);
void DRV_Timer1_Start(bool b8Enable);
u16 DRV_Timer0_CountGet(void);
u16 DRV_Timer1_CountGet(void);
u8 DRV_Timer3_Count1Get(void);
u8 DRV_Timer3_Count2Get(void);

/*****************************************************************************/
#ifdef  __cplusplus
	}
#endif

#endif	//_DRV_TIMER_H_

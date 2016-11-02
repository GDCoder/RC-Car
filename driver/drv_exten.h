/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: drv_exten.h
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2015.02.02
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            drv_exten.h
***************************************************************************/
#ifndef _DRV_EXTEN_H_
#define _DRV_EXTEN_H_

#include "..\inc\common.h"
#include "..\inc\config.h"

#ifdef  __cplusplus
	extern "C" {
#endif

/*****************************************************************************
 Constants   ∫Í∂®“Â
*****************************************************************************/


/*****************************************************************************
 Struct
*****************************************************************************/


/*****************************************************************************
functions prototype
*****************************************************************************/
void DRV_ExtenInt0_Int(void);
void DRV_ExtenInt1_Int(void);
void DRV_ExtenInt0_Init(void);
void DRV_ExtenInt1_Init(void);
void DRV_ExtenInt0_Start(bool b8Enable);
void DRV_ExtenInt1_Start(bool b8Enable);
u16 DRV_ExtenInt0_PulseWidthGet(void);
u16 DRV_ExtenInt1_PulseWidthGet(void);

/*****************************************************************************/
#ifdef  __cplusplus
	}
#endif

#endif	//_DRV_EXTEN_H_

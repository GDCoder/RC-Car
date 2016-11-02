/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: drv_sys.h
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2009.03.26
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            drv_sys.h
***************************************************************************/
#ifndef _DRV_SYS_H_
#define _DRV_SYS_H_

#include "drv_exten.h"
#include "drv_io.h"
#include "drv_i2c.h"
#include "drv_keyboard.h"
#include "drv_serial.h"
#include "drv_spi.h"
#include "drv_timer.h"

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
void DRV_Sys_IntEnable(bool bEnable);
void DRV_Sys_Init(void);

/*****************************************************************************/
#ifdef  __cplusplus
	}
#endif

#endif	//_DRV_SYS_H_
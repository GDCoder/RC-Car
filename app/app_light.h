/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: app_light.h
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2015.02.01
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            app_light.h
***************************************************************************/
#ifndef _APP_LIGHT_H_
#define _APP_LIGHT_H_

#include "..\inc\common.h"
#include "..\inc\config.h"

#ifdef  __cplusplus
	extern "C" {
#endif

/*****************************************************************************
 Constants   �궨��
*****************************************************************************/


/*****************************************************************************
 Struct
*****************************************************************************/


/*****************************************************************************
functions prototype
*****************************************************************************/
#ifdef LIGHT_ENABLE
	void APP_Light_Test(void);
#endif

/*****************************************************************************/
#ifdef  __cplusplus
	}
#endif

#endif	//_APP_LIGHT_H_
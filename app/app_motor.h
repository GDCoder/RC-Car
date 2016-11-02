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
#ifndef _APP_MOTOR_H_
#define _APP_MOTOR_H_

#include "..\inc\common.h"
#include "..\inc\config.h"

#ifdef  __cplusplus
	extern "C" {
#endif

/*****************************************************************************
 Constants   ∫Í∂®“Â
*****************************************************************************/


/*****************************************************************************
 Enum & Struct
*****************************************************************************/
typedef enum
{
	EN_RUNNING_FORWARD,
	EN_RUNNING_STOP,
	EN_RUNNING_BACKWARD
}EN_RUNNING_TYPE;

typedef enum
{
	EN_DIRECTION_LEFT,
	EN_DIRECTION_MIDDLE,
	EN_DIRECTION_RIGHT
}EN_DIRECTION_TYPE;

/*****************************************************************************
functions prototype
*****************************************************************************/
#ifdef MOTOR_ENABLE
	EN_RUNNING_TYPE APP_Motor_GetForwardAndBackward(void);
	EN_DIRECTION_TYPE APP_Motor_GetDirection(void);
	u8 APP_Motor_GetFbSpeed(void);
	u8 APP_Motor_GetLrSpeed(void);
	void APP_Motor_Control(EN_RUNNING_TYPE enRunning, EN_DIRECTION_TYPE enDirection, u8 u8FbSpeed, u8 u8LrSpeed);
#endif

/*****************************************************************************/
#ifdef  __cplusplus
	}
#endif

#endif	//_APP_MOTOR_H_

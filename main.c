/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: app_main.c
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2015.02.02
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            app_main.c
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include ".\driver\drv_sys.h"

#include ".\inc\common.h"
#include ".\inc\config.h"

#include ".\app\app_light.h"
#include ".\app\app_motor.h"

/*****************************************************************************
 Constants   宏定义
*****************************************************************************/
#ifdef SERIAL_ENABLE
	#define MAIN_DEBUG_MSG(p)		printf p
#else
	#define MAIN_DEBUG_MSG(p)
#endif

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


/*****************************************************************************
 Local functions
*****************************************************************************/
void main(void);


/*****************************************************************************
 implement begin 
*****************************************************************************/
void main()
{
	u8 u8FbSpeed = 0;
	u8 u8LrSpeed = 0;
	EN_RUNNING_TYPE enRunning = EN_RUNNING_STOP;
	EN_DIRECTION_TYPE enDirection = EN_DIRECTION_MIDDLE;

	//关闭中断
	DRV_Sys_IntEnable(FALSE);
	
	//初始化Driver
	DRV_Sys_Init();

	//开放中断
	DRV_Sys_IntEnable(TRUE);
	
	//主循环
	while(1)
	{
		#ifdef LIGHT_ENABLE
			APP_Light_Test();
		#endif

		#ifdef MOTOR_ENABLE
			enRunning = APP_Motor_GetForwardAndBackward();
			enDirection = APP_Motor_GetDirection();
			u8FbSpeed = APP_Motor_GetFbSpeed();
			u8LrSpeed = APP_Motor_GetLrSpeed();
			APP_Motor_Control(enRunning, enDirection, u8FbSpeed, u8LrSpeed);
		#endif
	}
}


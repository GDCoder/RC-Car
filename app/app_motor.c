/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: app_motor.c
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2015.02.01
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            app_motor.c
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stc15.h>

#include ".\driver\drv_sys.h"
#include "app_motor.h"


#ifdef MOTOR_ENABLE
/*****************************************************************************
 Constants   �궨��
*****************************************************************************/
#ifdef SERIAL_ENABLE
	#define APP_MOTOR_DEBUG_MSG(p)		printf p
#else
	#define APP_MOTOR_DEBUG_MSG(p)
#endif

#define Lin1	P00   	//Lin1�߼������
#define Lin2	P01  	//Lin2�߼������
#define Lin3	P02  	//Lin3�߼������
#define Lin4	P03 	//Lin4�߼������

#define Rin1	P04   	//Rin1�߼������
#define Rin2	P05  	//Rin2�߼������
#define Rin3	P06  	//Rin3�߼������
#define Rin4	P07 	//Rin4�߼������

#define FB_DEAD_ZONE	20	//ǰ���ͺ��˵�ҡ������
#define LR_DEAD_ZONE	20	//���ҷ����ҡ������

/*****************************************************************************
 Enum & Struct
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
static u16 u16PulseWidthMax = 1800;
static u16 u16PulseWidthMid = 1500;
static u16 u16PulseWidthMin = 1200;

/*****************************************************************************
 Local functions
*****************************************************************************/
static void leftWheelForward();
static void leftWheelStop();
static void leftWheelBackward();
static void rightWheelForward();
static void rightWheelStop();
static void rightWheelBackward();

/*****************************************************************************
 implement begin 
*****************************************************************************/
static void leftWheelForward()
{
	Lin1 = 0;
	Lin2 = 1;
	Lin3 = 0;
	Lin4 = 1;
}

static void leftWheelStop()
{
	Lin1 = 0;
	Lin2 = 0;
	Lin3 = 0;
	Lin4 = 0;
}

static void leftWheelBackward()
{
	Lin1 = 1;
	Lin2 = 0;
	Lin3 = 1;
	Lin4 = 0;
}

static void rightWheelForward()
{
	Rin1 = 1;
	Rin2 = 0;
	Rin3 = 1;
	Rin4 = 0;
}

static void rightWheelStop()
{
	Rin1 = 0;
	Rin2 = 0;
	Rin3 = 0;
	Rin4 = 0;
}

static void rightWheelBackward()
{
	Rin1 = 0;
	Rin2 = 1;
	Rin3 = 0;
	Rin4 = 1;
}

EN_RUNNING_TYPE APP_Motor_GetForwardAndBackward(void)
{
	u16 u16PulseWidth = 0;
	EN_RUNNING_TYPE enRunning = EN_RUNNING_STOP;

	u16PulseWidth = DRV_ExtenInt0_PulseWidthGet();
	if(u16PulseWidth < (u16PulseWidthMid - FB_DEAD_ZONE))
	{
		enRunning = EN_RUNNING_BACKWARD;
	}
	else if(u16PulseWidth > (u16PulseWidthMid - FB_DEAD_ZONE - 1))
	{
		if(u16PulseWidth <= (u16PulseWidthMid + FB_DEAD_ZONE))
		{
			enRunning = EN_RUNNING_STOP;
		}
		else
		{
			enRunning = EN_RUNNING_FORWARD;
		}
	}

	return enRunning;
}

EN_DIRECTION_TYPE APP_Motor_GetDirection(void)
{
	u16 u16PulseWidth = 0;
	EN_DIRECTION_TYPE enDirection = EN_DIRECTION_MIDDLE;

	u16PulseWidth = DRV_ExtenInt1_PulseWidthGet();
	if(u16PulseWidth < (u16PulseWidthMid - LR_DEAD_ZONE))
	{
		enDirection = EN_DIRECTION_LEFT;
	}
	else if(u16PulseWidth > (u16PulseWidthMid - LR_DEAD_ZONE - 1))
	{
		if(u16PulseWidth <= (u16PulseWidthMid + LR_DEAD_ZONE))
		{
			enDirection = EN_DIRECTION_MIDDLE;
		}
		else
		{
			enDirection = EN_DIRECTION_RIGHT;
		}
	}

	return enDirection;
}

u8 APP_Motor_GetFbSpeed(void)
{
	u8 u8Speed = 0;
	u16 u16PulseWidth = 0;

	// �õ�ǰ������������, �����������Сֵ�޶�
	u16PulseWidth = DRV_ExtenInt0_PulseWidthGet();
	if(u16PulseWidth < u16PulseWidthMin)
	{
		u16PulseWidth = u16PulseWidthMin;
	}
	else if(u16PulseWidth > u16PulseWidthMax)
	{
		u16PulseWidth = u16PulseWidthMax;
	}

	// ����ǰ�������ٶ�
	if(u16PulseWidth < (u16PulseWidthMid - FB_DEAD_ZONE))
	{
		u8Speed = (u8)((u16PulseWidthMid - u16PulseWidth) / 3);
	}
	else if(u16PulseWidth > (u16PulseWidthMid - FB_DEAD_ZONE - 1))
	{
		if(u16PulseWidth <= (u16PulseWidthMid + FB_DEAD_ZONE))
		{
			u8Speed = 0;
		}
		else
		{
			u8Speed = (u8)((u16PulseWidth - u16PulseWidthMid) / 3);
		}
	}
	
	return u8Speed;
}

u8 APP_Motor_GetLrSpeed(void)
{
	u8 u8Speed = 0;
	u16 u16PulseWidth = 0;
	
	// �õ�ת��������, �����������Сֵ�޶�
	u16PulseWidth = DRV_ExtenInt1_PulseWidthGet();
	if(u16PulseWidth < u16PulseWidthMin)
	{
		u16PulseWidth = u16PulseWidthMin;
	}
	else if(u16PulseWidth > u16PulseWidthMax)
	{
		u16PulseWidth = u16PulseWidthMax;
	}

	// ����ת���ٶ�
	if(u16PulseWidth < (u16PulseWidthMid - LR_DEAD_ZONE))
	{
		u8Speed = (u8)((u16PulseWidthMid - u16PulseWidth) / 3);
	}
	else if(u16PulseWidth > (u16PulseWidthMid - LR_DEAD_ZONE - 1))
	{
		if(u16PulseWidth <= (u16PulseWidthMid + LR_DEAD_ZONE))
		{
			u8Speed = 0;
		}
		else
		{
			u8Speed = (u8)((u16PulseWidth - u16PulseWidthMid) / 3);
		}
	}

	return u8Speed;
}

void APP_Motor_Control(EN_RUNNING_TYPE enRunning, EN_DIRECTION_TYPE enDirection, u8 u8FbSpeed, u8 u8LrSpeed)
{
	u8 u8FbCount = 0;
	u8 u8LrCount = 0;

	u8FbCount = DRV_Timer3_Count1Get();
	u8LrCount = DRV_Timer3_Count2Get();

	// ��ת��
	if(EN_DIRECTION_LEFT == enDirection)
	{
		// ��תǰ��: ���ֺ���, ����ǰ��
		if(EN_RUNNING_FORWARD == enRunning)
		{
			if(u8LrCount <= u8LrSpeed)
			{
				leftWheelBackward();
			}
			else
			{
				leftWheelStop();
			}

			if(u8FbCount <= u8FbSpeed)
			{
				rightWheelForward();
			}
			else
			{
				rightWheelStop();
			}
		}
		// ��ת����: ����ǰ��, ���ֺ���
		else if(EN_RUNNING_BACKWARD == enRunning)
		{
			if(u8LrCount <= u8LrSpeed)
			{
				leftWheelForward();
			}
			else
			{
				leftWheelStop();
			}

			if(u8FbCount <= u8FbSpeed)
			{
				rightWheelBackward();
			}
			else
			{
				rightWheelStop();
			}
		}
		// ԭ����ת
		else
		{
			// ԭ����תʱ, ���ֺ���, ����ǰ��
			if(u8LrCount <= u8LrSpeed)
			{
				leftWheelBackward();
				rightWheelForward();
			}
			else
			{
				leftWheelStop();
				rightWheelStop();
			}
		}
	}
	// ֱ��
	else if(EN_DIRECTION_MIDDLE == enDirection)
	{
		// ǰ��
		if(EN_RUNNING_FORWARD == enRunning)
		{
			if(u8FbCount <= u8FbSpeed)
			{
				leftWheelForward();
				rightWheelForward();
			}
			else
			{
				leftWheelStop();
				rightWheelStop();
			}
		}
		// ����
		else if(EN_RUNNING_BACKWARD == enRunning)
		{
			if(u8FbCount <= u8FbSpeed)
			{
				leftWheelBackward();
				rightWheelBackward();
			}
			else
			{
				leftWheelStop();
				rightWheelStop();
			}
		}
		// ֹͣ
		else
		{
			leftWheelStop();
			rightWheelStop();
		}
	}
	// ��ת��
	else
	{
		// ��תǰ��: ����ǰ��, ���ֺ���
		if(EN_RUNNING_FORWARD == enRunning)
		{
			if(u8FbCount <= u8FbSpeed)
			{
				leftWheelForward();
			}
			else
			{
				leftWheelStop();
			}

			if(u8LrCount <= u8LrSpeed)
			{
				rightWheelBackward();
			}
			else
			{
				rightWheelStop();
			}
		}
		// ��ת����: ���ֺ���, ����ǰ��
		else if(EN_RUNNING_BACKWARD == enRunning)
		{
			if(u8FbCount <= u8FbSpeed)
			{
				leftWheelBackward();
			}
			else
			{
				leftWheelStop();
			}

			if(u8LrCount <= u8LrSpeed)
			{
				rightWheelForward();
			}
			else
			{
				rightWheelStop();
			}
		}
		// ԭ����ת
		else
		{
			// ԭ����תʱ, ���ֺ���, ����ǰ��
			if(u8LrCount <= u8LrSpeed)
			{
				leftWheelForward();
				rightWheelBackward();
			}
			else
			{
				leftWheelStop();
				rightWheelStop();
			}
		}
	}
}

/*****************************************************************************/
#endif	//MOTOR_ENABLE


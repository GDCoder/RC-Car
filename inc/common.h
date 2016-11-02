/***************************************************************************
	(C)Copyright Logic Inc. 2008, Logic all rights reserved.

	Product	: STC MCU Firmware
	Date		: 2009.03.26
	Purpose	: 
	Sources	: common.h
***************************************************************************/

//Modification use :
/***************************************************************************
	Update

	Date  	: 2009.03.26
	Name	: Logic
	Description	: 

	Item			                  Source
	----------------------------------------		-------------------
	. create 					            common.h
***************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_


#ifdef  __cplusplus
	extern "C" {
#endif

/*****************************************************************************
 Constants   ∫Í∂®“Â
*****************************************************************************/
typedef		bit				bool;
typedef		unsigned char	u8;	
typedef		unsigned short	u16;
typedef		unsigned long	u32;

typedef		signed char		s8;	
typedef		signed short	s16;
typedef		signed long		s32;

typedef		volatile unsigned char		vu8;
typedef		volatile unsigned short		vu16;
typedef		volatile unsigned long		vu32;

#define	TRUE					1
#define	FALSE					0

#define	HIGH					1
#define	LOW						0

/*****************************************************************************
 Struct
*****************************************************************************/


/*****************************************************************************
functions prototype
*****************************************************************************/


/*****************************************************************************/
#ifdef  __cplusplus
	}
#endif

#endif	//_COMMON_H_


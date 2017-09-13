/*
 *	File			:	Data_0_0_101.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for Data
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER_0_0_101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	dataLoad
 *	Purpose	:	Load data from flash
 *	Input	:	ePage_: What data is? (Alarm or Focus)
 *	Output	:	None
 */
void dataLoad (status_Page ePage_)
{
	/* Load Alarm */
	if		(ePage_ == ePageAlarm)
	{
		// Create buffer
		char arrBuff[FLASH_ALARM_NUM_BYTE];

		// Read from flash
		flashReadBlock(FLASH_SEGMENT, (unsigned char*)arrBuff, FLASH_ALARM_POSITION, FLASH_ALARM_NUM_BYTE);
		sAlarm.varHour 		= 	arrBuff[0];
		sAlarm.varMinute 	= 	arrBuff[1];
	}

	/* Load Focus */
	else
	{
		// Read from flash
		flashReadByte(FLASH_SEGMENT, (unsigned char*)&sFocus.varInterval, FLASH_FOCUS_POSITION);
	}
}
//-------------------------------------------------------------------------------------------------

/*
 *	Function:	dataSave
 *	Purpose	:	Save data into flash
 *	Input	:	ePage_: What data is? (Alarm or Focus)
 *	Output	:	None
 */
void dataSave (status_Page ePage_)
{
	/* Save Alarm */
	if		(ePage_ == ePageAlarm)
	{
		// Create buffer
		char arrBuff[FLASH_ALARM_NUM_BYTE];
		arrBuff[0] = sAlarm.varHour;
		arrBuff[1] = sAlarm.varMinute;

		// Write to flash
		flashWriteBlock(FLASH_SEGMENT, (unsigned char*)arrBuff, FLASH_ALARM_POSITION, FLASH_ALARM_NUM_BYTE);
	}

	/* Save Focus */
	else
	{
		// Write to flash
		flashWriteByte(FLASH_SEGMENT, sFocus.varInterval, FLASH_FOCUS_POSITION);
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Data_0_0_101.c
 *************************************************************************************************/

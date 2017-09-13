/*
 *	File			:	Data_1_0_1.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Source for Data
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "../Header.h"


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
		unsigned char arrBuff[6];

		// Read from flash
		flashReadBlock(FLASH_SEGMENT, arrBuff, FLASH_ALARM_POSITION, FLASH_ALARM_NUM_BYTE);

		// Unite data
		sAlarm.varHour 		= 	byteToUint(arrBuff[0], arrBuff[1]);
		sAlarm.varMinute 	= 	byteToUint(arrBuff[2], arrBuff[3]);
		sAlarm.varSecond 	= 	byteToUint(arrBuff[4], arrBuff[5]);
	}

	/* Load Focus */
	else if	(ePage_ == ePageFocus)
	{
		// Create buffer
		unsigned char arrBuff[6];

		// Read from flash
		flashReadBlock(FLASH_SEGMENT, arrBuff, FLASH_FOCUS_POSITION, FLASH_FOCUS_NUM_BYTE);

		// Unite data
		sFocus.varHour 		= 	byteToUint(arrBuff[5], arrBuff[4]);
		sFocus.varMinute 	= 	byteToUint(arrBuff[3], arrBuff[2]);
		sFocus.varSecond 	= 	byteToUint(arrBuff[1], arrBuff[0]);
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
		unsigned char arrBuff[6];

		// Split data
		uintToByte(sAlarm.varHour, &arrBuff[5], &arrBuff[4]);
		uintToByte(sAlarm.varMinute, &arrBuff[3], &arrBuff[2]);
		uintToByte(sAlarm.varSecond, &arrBuff[1], &arrBuff[0]);

		// Write to flash
		flashWriteBlock(FLASH_SEGMENT, arrBuff, FLASH_ALARM_POSITION, FLASH_ALARM_NUM_BYTE);
	}

	/* Save Focus */
	else if (ePage_ == ePageFocus)
	{
		// Create buffer
		unsigned char arrBuff[6];

		// Split data
		uintToByte(sFocus.varHour, &arrBuff[5], &arrBuff[4]);
		uintToByte(sFocus.varMinute, &arrBuff[3], &arrBuff[2]);
		uintToByte(sFocus.varSecond, &arrBuff[1], &arrBuff[0]);

		// Write to flash
		flashWriteBlock(FLASH_SEGMENT, arrBuff, FLASH_FOCUS_POSITION, FLASH_FOCUS_NUM_BYTE);
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Data_1_0_1.c
 *************************************************************************************************/

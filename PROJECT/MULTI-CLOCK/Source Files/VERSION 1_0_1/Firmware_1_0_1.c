/*
 *	File			:	Firmware_1_0_1.c
 *	Date created	:	17/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Source for Firmware
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "../Header.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Status register */
volatile 	status_Register 	sStatusRegister;


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	firmPageNormal
 *	Purpose	:	Display current time
 *	Input	:	None
 *	Output	:	None
 */
void firmPageNormal (void)
{
	/* Print the number of Hour of current time */
	displayNumer(eComponentHour, sTime.varHour);

	/* Print the number of Minute of current time */
	displayNumer(eComponentMinute, sTime.varMinute);

	/* Print the number of Second of current time */
	displayNumer(eComponentSecond, sTime.varSecond);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	firmPageTime
 *	Purpose	:	Page for calibrating time for Clock
 *	Input	:	None
 *	Output	:	None
 */
void firmPageTime (void)
{
	/* Toogle 7-seg LED to identify position of selection (Put at while(1) of main function) */

	/* Set Hour */
	if		(sStatusRegister.bComponent == eComponentHour)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sTime.varHour++;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			sTime.varHour--;
		}
		else if	(sStatusRegister.bControl == eControlConfirm)
		{
			sStatusRegister.bComponent = eComponentMinute;
		}
	}

	/* Set Minute */
	else if	(sStatusRegister.bComponent == eComponentMinute)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sTime.varMinute++;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			sTime.varMinute--;
		}
		else if	(sStatusRegister.bControl == eControlConfirm)
		{
			sStatusRegister.bComponent = eComponentSecond;
		}
	}

	/* Set Second */
	else if	(sStatusRegister.bComponent == eComponentSecond)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sTime.varSecond++;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			sTime.varSecond--;
		}
		else if	(sStatusRegister.bControl == eControlConfirm)
		{
			// Exit to Normal page
			sStatusRegister.bPage = ePageNormal;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	firmPageAlarm
 *	Purpose	:	Page for setting Alarm
 *	Input	:	None
 *	Output	:	None
 */
void firmPageAlarm (void)
{
	/* Toogle 7-seg LED to identify position of selection (Put at while(1) of main function) */

	/* Set Hour */
	if		(sStatusRegister.bComponent == eComponentHour)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sAlarm.varHour++;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			sAlarm.varHour--;
		}
		else if (sStatusRegister.bControl == eControlConfirm)
		{
			sStatusRegister.bComponent = eComponentMinute;
		}
	}

	/* Set Minute */
	else if	(sStatusRegister.bComponent == eComponentMinute)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sAlarm.varMinute++;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			sAlarm.varMinute--;
		}
		else if	(sStatusRegister.bControl == eControlConfirm)
		{
			// Save into flash
			dataSave(ePageAlarm);

			// Exit to Normal page
			sStatusRegister.bPage = ePageNormal;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	firmPageFocus
 *	Purpose	:	Page for setting Focus
 *	Input	:	None
 *	Output	:	None
 */
void firmPageFocus (void)
{
	/* Toogle 7-seg LED to identify position of selection (Put at while(1) of main function) */

	/* Set minute */
	if		(sStatusRegister.bComponent == eComponentMinute)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sFocus.varMinute++;
		}
		else if (sStatusRegister.bControl == eControlDown)
		{
			sFocus.varMinute--;
		}
		else if (sStatusRegister.bControl == eControlConfirm)
		{
			// Save into flash
			dataSave(ePageFocus);

			// Exit to Normal page
			sStatusRegister.bPage = ePageNormal;
		}
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Firmware_1_0_1.c
 *************************************************************************************************/

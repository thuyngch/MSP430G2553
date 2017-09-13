/*
 *	File			:	Firmware_0_0_101.c
 *	Date created	:	17/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for Firmware
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER_0_0_101.h"


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
void firmPageNormalDisplay (void)
{
	/* Print the number of Hour of current time */
	displayHour(sTime.varHour);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	/* Print the number of Minute of current time */
	displayMinute(sTime.varMinute);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	/* Print the number of Second of current time */
	displaySecond(sTime.varSecond);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
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
			sTimeSet.varHour++;
			if(sTimeSet.varHour == 24) sTimeSet.varHour = 0;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			if(sTimeSet.varHour == 0) sTimeSet.varHour = 23;
			else sTimeSet.varHour--;
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
			sTimeSet.varMinute++;
			if(sTimeSet.varMinute == 60) sTimeSet.varMinute = 0;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			if(sTimeSet.varMinute == 0) sTimeSet.varMinute = 59;
			else sTimeSet.varMinute--;
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
			sTimeSet.varSecond++;
			if(sTimeSet.varSecond == 60) sTimeSet.varSecond = 0;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			if(sTimeSet.varSecond == 0) sTimeSet.varSecond = 59;
			else sTimeSet.varSecond--;
		}
		else if	(sStatusRegister.bControl == eControlConfirm)
		{
			// Synch time
			ds1307Setup(sTimeSet.varHour, sTimeSet.varMinute, sTimeSet.varSecond,
						4, 19, 10, 16);											// Initial DS1307

			// Exit to Normal page
			sStatusRegister.bPage = ePageNormal;
			sStatusRegister.bControl = eControlNone;
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
	/* Turn off SPEAKER */
	speakerTurnOff();
	sStatusRegister.bSpkAlarm = 0;

	/* Toogle 7-seg LED to identify position of selection (Put at while(1) of main function) */

	/* Set Hour */
	if		(sStatusRegister.bComponent == eComponentHour)
	{
		if		(sStatusRegister.bControl == eControlUp)
		{
			sAlarm.varHour++;
			if(sAlarm.varHour == 24) sAlarm.varHour = 0;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			if(sAlarm.varHour == 0) sAlarm.varHour = 23;
			else sAlarm.varHour--;
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
			if(sAlarm.varMinute == 60) sAlarm.varMinute = 0;
		}
		else if	(sStatusRegister.bControl == eControlDown)
		{
			if(sAlarm.varMinute == 0) sAlarm.varMinute = 59;
			else sAlarm.varMinute--;
		}
		else if	(sStatusRegister.bControl == eControlConfirm)
		{
			// Save into flash
			dataSave(ePageAlarm);

			// Exit to Normal page
			sStatusRegister.bPage = ePageNormal;
			sStatusRegister.bControl = eControlNone;
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
			sFocus.varInterval++;
			if(sFocus.varInterval == 100) sFocus.varInterval = 1;
		}
		else if (sStatusRegister.bControl == eControlDown)
		{
			if(sFocus.varInterval == 1) sFocus.varInterval = 99;
			else if (sFocus.varInterval == 0) sFocus.varInterval = 99;
			else sFocus.varInterval--;
		}
		else if (sStatusRegister.bControl == eControlConfirm)
		{
			// Get current time
			sFocus.varHour = sTime.varHour;
			sFocus.varMinute = sTime.varMinute;

			// Save into flash
			dataSave(ePageFocus);

			// Exit to Normal page
			sStatusRegister.bPage = ePageNormal;
			sStatusRegister.bControl = eControlNone;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
firmPageTimeDisplay	(void)
{
	/* Print the number of Hour of setting time */
	displayHour(sTimeSet.varHour);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	/* Print the number of Minute of setting time */
	displayMinute(sTimeSet.varMinute);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	/* Print the number of Second of setting time */
	displaySecond(sTimeSet.varSecond);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
firmPageAlarmDisplay(void)
{
	/* Print the number of Hour of alarm time */
	displayHour(sAlarm.varHour);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	/* Print the number of Minute of alarm time */
	displayMinute(sAlarm.varMinute);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
firmPageFocusDisplay(void)
{
	/* Print the number of Minute of focus time */
	displayMinute(sFocus.varInterval);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Firmware_0_0_101.c
 *************************************************************************************************/

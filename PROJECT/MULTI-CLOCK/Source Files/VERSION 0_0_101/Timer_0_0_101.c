/*
 *	File			:	Timer_0_0_101.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for Timer
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER_0_0_101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Time */
volatile 	system_Time 	sTime;
volatile 	system_Time 	sTimeSet;
volatile 	alarm_Time	 	sAlarm;
volatile 	focus_Time	 	sFocus;


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	timerGetCurrent
 *	Purpose	:	Get current time form DS1307
 *	Input	:	None
 *	Output	:	None
 */
void timerGetCurrent (void)
{
	ds1307Read();
	sTime.varHour 	= sDS1307Time.varHour;
	sTime.varMinute = sDS1307Time.varMinute;
	sTime.varSecond = sDS1307Time.varSecond;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
timerAlarm	(char varHr, char varMin, char varSec)
{
	if(sTime.varHour == varHr)
	{
		if(sTime.varMinute == varMin)
		{
			if(sTime.varSecond == 0)
			{
				sStatusRegister.bSpkAlarm = 1;
				speakerPlay(SPEAKER_ALARM);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	timerFocus
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
timerFocus (char varInterval)
{
	if(sFocus.varInterval != 0)
	{
		unsigned char varTimeDiffer;
		varTimeDiffer = ((sTime.varHour - sFocus.varHour) * 60 + (sTime.varMinute - sFocus.varMinute));
		if(varTimeDiffer == varInterval)
		{
			speakerPlay(SPEAKER_FOCUS);			// Notify to focus

			sFocus.varHour = sTime.varHour;		// Update current time
			sFocus.varMinute = sTime.varMinute;
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
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Timer_0_0_101.c
 *************************************************************************************************/

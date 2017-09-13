/*
 *	File			:	LCD.c
 *	Date created	:	10/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Source for LCD
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "main.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void lcdNotifyOverFlowDigit (unsigned int varPeDu)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Digit Overflow?!");
	__delay_cycles(DL_1S);
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Mode "); LCD_Display(varFirmMode); LCD_Display(':');
	LCD_Goto(2, 2);
	if(varPeDu == FIRM_STT_PERIOD)
	{
		LCD_PrintString("Period=");
		LCD_Display((unsigned char)mathBcdThou(regFirmTimeOn) + 48);
		LCD_Display((unsigned char)mathBcdHund(regFirmTimeOn) + 48);
		LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOn) + 48);
		LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOn) + 48);
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
		LCD_PrintString("Duty=");
		LCD_Display((unsigned char)mathBcdThou(regFirmTimeOff) + 48);
		LCD_Display((unsigned char)mathBcdHund(regFirmTimeOff) + 48);
		LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOff) + 48);
		LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOff) + 48);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void lcdNotifyNullValue (unsigned int varPeDu)
{
	LCD_Clear();
	LCD_Home();
	if(varPeDu == FIRM_STT_PERIOD)
	{
		LCD_PrintString("Period=0?!");
		__delay_cycles(DL_1S);
		LCD_Clear();
		LCD_Home();
		LCD_PrintString("Mode "); LCD_Display(varFirmMode); LCD_Display(':');
		LCD_Goto(2, 2);
		LCD_PrintString("Period=");
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
		LCD_PrintString("Duty=0?!");
		__delay_cycles(DL_1S);
		LCD_Clear();
		LCD_Home();
		LCD_PrintString("Mode "); LCD_Display(varFirmMode); LCD_Display(':');
		LCD_Goto(2, 2);
		LCD_PrintString("Duty=");
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void lcdNotifyViolateTime (void)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Period < Duty ?!");
	__delay_cycles(DL_1S);
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Mode "); LCD_Display(varFirmMode); LCD_Display(':');
	LCD_Goto(2, 2);
	LCD_PrintString("Duty=");
	LCD_Display((unsigned char)mathBcdThou(regFirmTimeOff) + 48);
	LCD_Display((unsigned char)mathBcdHund(regFirmTimeOff) + 48);
	LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOff) + 48);
	LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOff) + 48);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void lcdNotifyExit (void)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Select a mode...");
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void lcdNotifyMode (unsigned char varMode)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Mode ");
	LCD_Display(varMode);
	LCD_Display(':');
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	lcdNotifyConfirm
 *	Purpose	:	Notify confirm completely
 * 	Input	:	None
 * 	Output	:	None
 */
void lcdNotifyConfirm (void)
{
	LCD_Clear();
	LCD_Home();

	LCD_PrintString("  Period=");
	LCD_Display((unsigned char)mathBcdThou(regFirmTimeOn) + 48);
	LCD_Display((unsigned char)mathBcdHund(regFirmTimeOn) + 48);
	LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOn) + 48);
	LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOn) + 48);

	LCD_Goto(2,1);

	LCD_PrintString("   Duty=");
	LCD_Display((unsigned char)mathBcdThou(regFirmTimeOff) + 48);
	LCD_Display((unsigned char)mathBcdHund(regFirmTimeOff) + 48);
	LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOff) + 48);
	LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOff) + 48);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF LCD.c
 *************************************************************************************************/

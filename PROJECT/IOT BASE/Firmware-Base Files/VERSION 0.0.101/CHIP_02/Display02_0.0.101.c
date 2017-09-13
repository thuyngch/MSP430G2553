/*
 *	File			:	Display02_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for Display of Second Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER02_0.0.101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
char			arrButtonRxData[4];


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	displayTotal
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
displayTotal (char varNo, uint8_t varRxData)
{
	displayName(varNo);
	displayPassword();
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	displayName
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
displayName	(char varNo)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString((char*)sMember02[varNo].strName);
	LCD_Goto(2,1);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	displayPassword
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
displayPassword	(void)
{
	switch (sRegisterStatus02.bButtonNumOfDigit)
	{
		case eButtonNumOfDigit_1:
			LCD_PrintString("Password:");
			LCD_Display(arrButtonRxData[0]);
			break;
		case eButtonNumOfDigit_2:
			LCD_PrintString("Password:");
			LCD_Display(arrButtonRxData[0]);
			LCD_Display(arrButtonRxData[1]);
			break;
		case eButtonNumOfDigit_3:
			LCD_PrintString("Password:");
			LCD_Display(arrButtonRxData[0]);
			LCD_Display(arrButtonRxData[1]);
			LCD_Display(arrButtonRxData[2]);
			break;
		case eButtonNumOfDigit_4:
			LCD_PrintString("Password:");
			LCD_Display(arrButtonRxData[0]);
			LCD_Display(arrButtonRxData[1]);
			LCD_Display(arrButtonRxData[2]);
			LCD_Display(arrButtonRxData[3]);
			break;
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
displayOverFlow (void)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Digit Overflow?!");
	__delay_cycles(DL_1S * FREQUENCY);
	displayTotal(varNoCurrent, varI2C02Data);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
displayNull (void)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Null?!");
	__delay_cycles(DL_1S * FREQUENCY);
	displayTotal(varNoCurrent, varI2C02Data);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
displayError (void)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Error Password");
	__delay_cycles(DL_1S * FREQUENCY);
	displayTotal(varNoCurrent, varI2C02Data);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
displayClear (void)
{
	LCD_Clear();
	LCD_Home();
	displayName(varNoCurrent);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
displayErrCard (void)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Error CARD!");
	__delay_cycles(DL_1S * FREQUENCY);
	LCD_Clear();
	LCD_Home();
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
displaySuccess (char varNo)
{
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Hello");
	LCD_Goto(2,1);
	LCD_PrintString((char*)sMember02[varNo].strName);
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
 *	END OF Display02_0.0.101.c
 *************************************************************************************************/

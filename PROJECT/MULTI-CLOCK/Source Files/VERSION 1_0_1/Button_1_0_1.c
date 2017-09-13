/*
 *	File			:	Button_1_0_1.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Source for Button
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
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void buttonIdentify (void)
{
	switch (P2IFG & PIN_GPIO_IN_PORT2)
	{
		case PIN_BTN_UP:
			sStatusRegister.bControl 	= eControlUp;
			break;
		case PIN_BTN_DOWN:
			sStatusRegister.bControl	= eControlDown;
			break;
		case PIN_BTN_CONFIRM:
			sStatusRegister.bControl 	= eControlConfirm;
			break;
		case PIN_BTN_EN_TIME:
			sStatusRegister.bPage 		= ePageTime;
			sStatusRegister.bComponent 	= eComponentHour;
			break;
		case PIN_BTN_EN_ALARM:
			sStatusRegister.bPage 		= ePageAlarm;
			sStatusRegister.bComponent 	= eComponentHour;
			break;
		case PIN_BTN_EN_FOCUS:
			sStatusRegister.bPage 		= ePageFocus;
			sStatusRegister.bComponent 	= eComponentMinute;
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
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Button_1_0_1.c
 *************************************************************************************************/

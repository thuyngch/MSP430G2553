/*
 *	File			:	Button_0_0_101.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for Button
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
//#define	TEST_UART_BUTTON


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
 *	Function:	buttonIdentify
 *	Purpose	: 	Set bits in statusRegister coresponding to which button is pressed
 *	Input	: 	None
 *	Output	: 	None
 */
void buttonIdentify (void)
{

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	switch (P2IFG & PIN_GPIO_IN_PORT2)
	{
		case PIN_BTN_UP:
			sStatusRegister.bControl 	= eControlUp;
#ifdef TEST_UART_BUTTON
			testUart(MODULE_BUTTON, COMPONENT_BTN_UP);
#endif	/* TEST_UART_BUTTON */
			break;
		//=========================================================================================
		case PIN_BTN_DOWN:
			sStatusRegister.bControl	= eControlDown;
#ifdef TEST_UART_BUTTON
			testUart(MODULE_BUTTON, COMPONENT_BTN_DOWN);
#endif	/* TEST_UART_BUTTON */
			break;
		//=========================================================================================
		case PIN_BTN_CONFIRM:
			sStatusRegister.bControl 	= eControlConfirm;
#ifdef TEST_UART_BUTTON
			testUart(MODULE_BUTTON, COMPONENT_BTN_CONFIRM);
#endif	/* TEST_UART_BUTTON */
			break;
		//=========================================================================================
		case PIN_BTN_EN_TIME:
			sStatusRegister.bPage 		= ePageTime;
			sStatusRegister.bComponent 	= eComponentHour;
			sStatusRegister.bControl 	= 0;
#ifdef TEST_UART_BUTTON
			testUart(MODULE_BUTTON, COMPONENT_BTN_EN_TIME);
#endif	/* TEST_UART_BUTTON */
			break;
		//=========================================================================================
		case PIN_BTN_EN_ALARM:
			sStatusRegister.bPage 		= ePageAlarm;
			sStatusRegister.bComponent 	= eComponentHour;
			sStatusRegister.bControl 	= 0;
#ifdef TEST_UART_BUTTON
			testUart(MODULE_BUTTON, COMPONENT_BTN_EN_ALARM);
#endif	/* TEST_UART_BUTTON */
			break;
		//=========================================================================================
		case PIN_BTN_EN_FOCUS:
			sStatusRegister.bPage 		= ePageFocus;
			sStatusRegister.bComponent 	= eComponentMinute;
			sStatusRegister.bControl 	= 0;
#ifdef TEST_UART_BUTTON
			testUart(MODULE_BUTTON, COMPONENT_BTN_EN_FOCUS);
#endif	/* TEST_UART_BUTTON */
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
 *	END OF Button_0_0_101.c
 *************************************************************************************************/

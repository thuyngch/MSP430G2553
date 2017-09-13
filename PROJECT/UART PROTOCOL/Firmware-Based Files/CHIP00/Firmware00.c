/*
 *	File			:	Firmware00.c
 *	Date created	:	26/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER00.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
register_Status_00		sRegisterStatus00;	// Status register of Chip00


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
void
fw00DetectButton(uint8_t* arrBuff)
{
	/* Declare */
	char* pAddrOfData;

	/* Find address of needed data */
	pAddrOfData = wifi00FindDataFromBuffer((const char*)arrUART00);
	pAddrOfData += 2;

	/* Detect which button is pressed */
	switch (*pAddrOfData)
	{
		case '1':
			sRegisterStatus00.bButton = 1; break;
		case '2':
			sRegisterStatus00.bButton = 2; break;
		case '3':
			sRegisterStatus00.bButton = 3; break;
		case '4':
			sRegisterStatus00.bButton = 4; break;
		case '5':
			sRegisterStatus00.bButton = 5; break;
		case '6':
			sRegisterStatus00.bButton = 6; break;
		case '7':
			sRegisterStatus00.bButton = 7; break;
		case '8':
			sRegisterStatus00.bButton = 8; break;
		default:
			sRegisterStatus00.bButton = 0; break;
	}

	/* Detect status of button */
	pAddrOfData++;
	if(*pAddrOfData == 49) 	sRegisterStatus00.bIsButtonTurnOn = true;
	else					sRegisterStatus00.bIsButtonTurnOn = false;
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
 *	END OF Firmware00.c
 *************************************************************************************************/

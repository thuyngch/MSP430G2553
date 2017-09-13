/*
 *	File			:	Wifi03_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for Wifi of Third Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER03_0.0.101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
uint8_t			varUART03;				// Store temporary data RXD
uint16_t		varCountUARTData03;		// Count number of received UART byte
uint8_t			arrUARTBuff03[256];		// Buffer of RX UART


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
bool
wifi03CheckATCmdComplete(const char* strCheck)
{
	while(!sRegisterStatus03.bIsNullCharacter);	// While unless matching '\0'
	wifi03StopTimerCount();						// Stop Timer count
	sRegisterStatus03.bIsNullCharacter = false;	// Reset to false
	bool varCheck = wifi03FindStr((const char*)arrUARTBuff03, strCheck);
												// Check whether received data contains needed string
	wifi03ClearBuffer(arrUARTBuff03, 256);	// Clear Buffer
	varCountUARTData03 = 0;					// Reset Counter of UART
	return varCheck;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
wifi03StartTimerCount(uint16_t varTimeOut)
{
	TA0CCR0 = varTimeOut;		// Setup interval
	TA0R 	= 0;				// Reset timer count
	TA0CTL |= MC_1;				// Enable timer
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
wifi03StopTimerCount(void)
{
	timerAStop(TIMER_A_0);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
bool
wifi03FindStr(const char *strSource, const char *strNeed)
{
	if(strstr(strSource, strNeed)) return true;
	return false;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
wifi03ClearBuffer(uint8_t arrBuff[], uint16_t varLength)
{
	uint16_t i;
	for(i = 0; i < varLength; i++) arrBuff[i] = 1;	// Reset 256 bytes of UART buffer to 1
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
 *	END OF Wifi03_0.0.101.c
 *************************************************************************************************/

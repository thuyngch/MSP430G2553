/*
 *	File			:	Wifi00.c
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
uint8_t					varUART00;			// Temporary buffer of RXD
uint16_t				varCountUART00;		// Count number of received UART byte
uint8_t					arrUART00[256];		// Main buffer of RXD


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
wifi00CheckATCmdComplete(const char* strCheck)
{
	while(!sRegisterStatus00.bIsNullCharacter);	// While unless matching '\0'
	wifi00StopTimerCount();						// Stop Timer count
	sRegisterStatus00.bIsNullCharacter = false;	// Reset to false
	bool varCheck = wifi00FindStr((const char*)arrUART00, strCheck);
												// Check whether received data contains needed string
	wifi00ClearBuffer(arrUART00, 256);			// Clear Buffer
	varCountUART00 = 0;							// Reset Counter of UART
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
wifi00StartTimerCount(uint16_t varTimeOut)
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
wifi00StopTimerCount(void)
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
wifi00FindStr(const char *strSource, const char *strNeed)
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
wifi00ClearBuffer(uint8_t arrBuff[], uint16_t varLength)
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
char*
wifi00FindDataFromBuffer(const char *strSource)
{
	return strstr(strSource, "/<");
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
 *	END OF Wifi00.c
 *************************************************************************************************/

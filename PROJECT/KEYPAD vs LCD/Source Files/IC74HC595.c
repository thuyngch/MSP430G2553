/*
 *	File			:	IC74HC595.c
 *	Date created	:	13/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Source for IC 74HC595
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
 * 	Function:	ic74hc595GetData
 *	Purpose	:	Shift data into 74HC595
 * 	Input	:	varData: Data needed to shift
 * 	Output	:	None
 */
void ic74hc595GetData (unsigned char varData)
{
	unsigned char varCount;
	gpioLow(PORT1, PIN_74HC595_SHCP);
	for(varCount = 0; varCount < 8; varCount++)
	{
		if(varData & BIT7)
		{
			gpioHigh(PORT1, PIN_74HC595_DS);
		}
		else
		{
			gpioLow(PORT1, PIN_74HC595_DS);
		}
		varData = (varData << 1);
		gpioHigh(PORT1, PIN_74HC595_SHCP);
		gpioLow(PORT1, PIN_74HC595_SHCP);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ic74hc595Latch
 *	Purpose	:	Latch the output
 * 	Input	:	None
 * 	Output	:	None
 */
void ic74hc595Latch (void)
{
	gpioLow(PORT1, PIN_74HC595_STCP);
	__delay_cycles(5);
	gpioHigh(PORT1, PIN_74HC595_STCP);
	gpioLow(PORT1, PIN_74HC595_STCP);
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
 *	END OF IC74HC595.c
 *************************************************************************************************/

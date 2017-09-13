/*
 *	File			:	IC74HC595_1_0_1.c
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
#include "IC74HC595_1_0_1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
static unsigned char pinDS;		// Data input
static unsigned char pinSHCP;	// Clock
static unsigned char pinSTCP;	// Latch


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	ic74HC595Setup
 *	Purpose	:	Setup pins for IC74HC595
 * 	Input	:	pinDS_: Data input pin
 * 				pinSHCP_: Clock pin
 * 				pinSTCP_: Latch pin
 * 	Output	:	None
 */
 void ic74HC595Setup (unsigned char pinDS_, unsigned char pinSHCP_, unsigned char pinSTCP_)
 {
	 pinDS 		= 	pinDS_;
	 pinSHCP 	= 	pinSHCP_;
	 pinSTCP 	= 	pinSTCP_;
 }
 //-------------------------------------------------------------------------------------------------
 /*
 * 	Function:	ic74HC595GetData
 *	Purpose	:	Shift data into 74HC595
 * 	Input	:	varData: Data needed to shift
 * 	Output	:	None
 */
void ic74HC595Data (unsigned char varData)
{
	unsigned char varCount;
	gpioLow(PORT1, pinSHCP);
	for(varCount = 0; varCount < 8; varCount++)
	{
		if(varData & BIT7)
		{
			gpioHigh(PORT1, pinDS);
		}
		else
		{
			gpioLow(PORT1, pinDS);
		}
		varData = (varData << 1);
		gpioHigh(PORT1, pinSHCP);
		__delay_cycles(5);
		gpioLow(PORT1, pinSHCP);
	}
	ic74HC595Latch();
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ic74HC595Latch
 *	Purpose	:	Latch the output
 * 	Input	:	None
 * 	Output	:	None
 */
void ic74HC595Latch (void)
{
	gpioHigh(PORT1, pinSTCP);
	__delay_cycles(5);
	gpioLow(PORT1, pinSTCP);
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

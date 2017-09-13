/*
 *	File			:	CLOCK_1_0_1.c
 *	Date created	:	31/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct Clock library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "CLOCK_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	clkSetup
 *	Purpose	:	Setup clock module
 *	Input	:	CLK_: What oscillator is and what frequency is?
 *	Output	:	None
 */
void clkSetup (const unsigned int CLK_)
{
	switch (CLK_)
	{
		case CLK_DCO_1MHZ:
		{
			BCSCTL1  = CALBC1_1MHZ;
			DCOCTL   = CALDCO_1MHZ;
			break;
		}
		case CLK_DCO_8MHZ:
		{
			BCSCTL1  = CALBC1_8MHZ;
			DCOCTL   = CALDCO_8MHZ;
			break;
		}
		case CLK_DCO_12MHZ:
		{
			BCSCTL1  = CALBC1_12MHZ;
			DCOCTL   = CALDCO_12MHZ;
			break;
		}
		case CLK_DCO_16MHZ:
		{
	        BCSCTL1  =  CALBC1_16MHZ;
	        DCOCTL 	 =  CALDCO_16MHZ;
			break;
		}
		default:
		{
			break;
		}
	}
}


/**************************************************************************************************
 *	END OF CLOCK_1_0_1.c
 *************************************************************************************************/

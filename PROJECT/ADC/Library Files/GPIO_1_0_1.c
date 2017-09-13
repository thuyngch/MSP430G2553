/*
 *	File			:	GPIO_1_0_1.c
 *	Date created	:	28/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct GPIO library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "GPIO_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/

 
/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	gpioSetup
 *	Purpose	:	Setup GPIO for pins and set what pins are output
 * 	Input	:	PORT_: Port 1 or 2?
 * 				PIN_: Which will pins be setted?
 * 				OUTPUT_: Which will pins be setted as output?
 * 	Output	:	None
 */
void gpioSetup(const unsigned int PORT_, const unsigned int PIN_, const unsigned int OUTPUT_)
{
	if (PORT_ == PORT1)
	{
		P1SEL  &= ~PIN_;
		P1SEL2 &= ~PIN_;
		P1DIR  = OUTPUT_;
		P1OUT  = 0;
	}

	if (PORT_ == PORT2)
	{
		P2SEL  &= ~PIN_;
		P2SEL2 &= ~PIN_;
		P2DIR  = OUTPUT_;
		P2OUT  = 0;
	}

	P3SEL = 0;
	P3SEL2 = 0;
	P3DIR = 0;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	gpioIntSetup
 *	Purpose	:	Setup interrupt
 * 	Input	:	PORT_: Port 1 or 2?
 * 				IN_: Which will pins be setted as input?
 * 				PULL_UP_: Which will pins be pulled up?
 * 				INIT_PORT_: Enable interrupt?
 * 	Output	:	None
 */
void gpioIntSetup(const unsigned int PORT_, const unsigned int INPUT_, const unsigned int PULL_UP_, const unsigned int INT_PORT_)
{
	if (PORT_ == PORT1)
	{
		P1REN   = INPUT_;
		P1OUT  |= PULL_UP_;
		if(INT_PORT_ == INT_PORT_ON)
		{
			P1IE    = INPUT_;
			P1IES   = PULL_UP_;
			P1IFG  &= ~INPUT_;
			__bis_SR_register(GIE);
		}
	}
	if (PORT_ == PORT2)
	{
		P2REN   = INPUT_;
		P2OUT  |= PULL_UP_;
		if(INT_PORT_ == INT_PORT_ON)
		{
			P2IE    = INPUT_;
			P2IES   = PULL_UP_;
			P2IFG  &= ~INPUT_;
			__bis_SR_register(GIE);
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	gpioOn
 *	Pupose	:	Turn on pins
 * 	Input	:	What pins?
 * 	Output	:	None
 */
void gpioHigh (const unsigned int PORT_, const unsigned char PIN_)
{
	if (PORT_ == PORT1)
	{
		P1OUT |= PIN_;
	}
	if (PORT_ == PORT2)
	{
		P2OUT |= PIN_;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	gpioOff
 *	Pupose	:	Turn on pins
 * 	Input	:	What pins?
 * 	Output	:	None
 */
void gpioLow (const unsigned int PORT_, const unsigned char PIN_)
{
	if (PORT_ == PORT1)
	{
		P1OUT &= ~PIN_;
	}
	if (PORT_ == PORT2)
	{
		P2OUT &= ~PIN_;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	gpioToggle
 *	Pupose	:	Turn on pins
 * 	Input	:	What pins?
 * 	Output	:	None
 */
void gpioToggle (const unsigned int PORT_, const unsigned char PIN_)
{
	if (PORT_ == PORT1)
	{
		P1OUT ^= PIN_;
	}
	if (PORT_ == PORT2)
	{
		P2OUT ^= PIN_;
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF GPIO_1_0_1.c
 *************************************************************************************************/

/*
 *	File			:	GPIO_1_1_1.c
 *	Date created	:	28/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.1.1
 *	Description		:	Construct GPIO library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "GPIO_1_1_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Structs for gpioSetup function */
const gpio_Setup sGpioSetup[] =
{
		{// Mode 0
			PORT1,
			LED_RED + LED_GREEN + BUTTON,
			LED_RED + LED_GREEN
		},
		{// Mode 1
			PORT1,
			LED_RED + LED_GREEN,
			LED_RED + LED_GREEN
		},
		{// Mode 2
			PORT1,
			LED_RED,
			LED_RED
		},
		{// Mode 3
			PORT2,
			BIT0,
			BIT0
		}
};

/* Structs for gpioIntSetup function */
const gpio_Int_Setup sGpioIntSetup[] =
{
		{// Mode 0
			PORT1, 
			BUTTON, 
			BUTTON
		}
};

/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	gpioSetup
 *	Purpose	:	Setup GPIO for pins and set what pins are output
 * 	Input	:	Mode struct
 * 	Output	:	None
 */
void gpioSetup(const gpio_Setup sGpioSetup_)
{
	if (sGpioSetup_.PORT_ == PORT1)
	{
		P1SEL  &= ~sGpioSetup_.PIN_;
		P1SEL2 &= ~sGpioSetup_.PIN_;
		P1DIR  = sGpioSetup_.OUT_;
		P1OUT  = 0;
	}

	if (sGpioSetup_.PORT_ == PORT2)
	{
		P2SEL  &= ~sGpioSetup_.PIN_;
		P2SEL2 &= ~sGpioSetup_.PIN_;
		P2DIR  = sGpioSetup_.OUT_;
		P2OUT  = 0;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	gpioIntSetup
 *	Purpose	:	Setup interrupt
 * 	Input	:	Mode struct
 * 	Output	:	None
 */
void gpioIntSetup(const gpio_Int_Setup sGpioIntSetup_)
{
	if (sGpioIntSetup_.PORT_ == PORT1)
	{
		P1REN   = sGpioIntSetup_.IN_;
		P1OUT  |= sGpioIntSetup_.PULL_UP_;
		P1IE    = sGpioIntSetup_.IN_;
		P1IES   = sGpioIntSetup_.PULL_UP_;
		P1IFG  &= ~sGpioIntSetup_.IN_;
		_BIS_SR(GIE);
	}
	if (sGpioIntSetup_.PORT_ == PORT2)
	{
		P2REN   = sGpioIntSetup_.IN_;
		P2OUT  |= sGpioIntSetup_.PULL_UP_;
		P2IE    = sGpioIntSetup_.IN_;
		P2IES   = sGpioIntSetup_.PULL_UP_;
		P2IFG  &= ~sGpioIntSetup_.IN_;
		_BIS_SR(GIE);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ledOn
 *	Pupose	:	Turn on a LED (P1.0/P1.6)
 * 	Input	:	What LED will be turned on? (RED/GREEN)
 * 	Output	:	None
 */
void ledOn (const unsigned char LED_)
{
	if (LED_ == LED_RED)
	{
		P1OUT |= LED_RED;
	}
	if (LED_ == LED_GREEN)
	{
		P1OUT |= LED_GREEN;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ledOff
 *	Pupose	:	Turn off a LED (P1.0/P1.6)
 * 	Input	:	What LED will be turned off? (RED/GREEN)
 * 	Output	:	None
 */
void ledOff (const unsigned char LED_)
{
	if (LED_ == LED_RED)
	{
		P1OUT &= ~LED_RED;
	}
	if (LED_ == LED_GREEN)
	{
		P1OUT &= ~LED_GREEN;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ledToggle
 *	Purpose	:	Toggle a LED (P1.0/P1.6)
 * 	Input	:	What LED will be toggled? (RED/GREEN)
 * 	Output	:	None
 */
void ledToggle (const unsigned char LED_)
{
	if (LED_ == LED_RED)
	{
		P1OUT ^= LED_RED;
	}
	if (LED_ == LED_GREEN)
	{
		P1OUT ^= LED_GREEN;
	}
}


/**************************************************************************************************
 *	END OF GPIO_1_1_1.c
 *************************************************************************************************/

/*
 *	File			:	GPIO_1_3_1.c
 *	Date created	:	18/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.3.1
 *	Description		:	Construct GPIO library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "GPIO_1_3_1.h"


/**************************************************************************************************
 *	EXTERNALs
 *************************************************************************************************/
extern volatile gpio_Port sGpioPort1 = {ADDR_GPIO_P1_SEL, ADDR_GPIO_P1_SEL2, ADDR_GPIO_P1_DIR,
										ADDR_GPIO_P1_IN , ADDR_GPIO_P1_OUT , ADDR_GPIO_P1_REN,
										ADDR_GPIO_P1_IE , ADDR_GPIO_P1_IES , ADDR_GPIO_P1_IFG};

extern volatile gpio_Port sGpioPort2 = {ADDR_GPIO_P2_SEL, ADDR_GPIO_P2_SEL2, ADDR_GPIO_P2_DIR,
										ADDR_GPIO_P2_IN , ADDR_GPIO_P2_OUT , ADDR_GPIO_P2_REN,
										ADDR_GPIO_P2_IE , ADDR_GPIO_P2_IES , ADDR_GPIO_P2_IFG};

 
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
		sGpioPort1.puGpioSEL->regGpioSEL   &= ~PIN_;
		sGpioPort1.puGpioSEL2->regGpioSEL2 &= ~PIN_;
		sGpioPort1.puGpioDIR->regGpioDIR    = OUTPUT_;
		sGpioPort1.puGpioOUT->regGpioOUT    = 0;
	}

	if (PORT_ == PORT2)
	{
		sGpioPort2.puGpioSEL->regGpioSEL   &= ~PIN_;
		sGpioPort2.puGpioSEL2->regGpioSEL2 &= ~PIN_;
		sGpioPort2.puGpioDIR->regGpioDIR    = OUTPUT_;
		sGpioPort2.puGpioOUT->regGpioOUT    = 0;
	}
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
		sGpioPort1.puGpioREN->regGpioREN  = INPUT_;
		sGpioPort1.puGpioOUT->regGpioOUT |= PULL_UP_;
		if(INT_PORT_ == INT_PORT_ON)
		{
			sGpioPort1.puGpioIE->regGpioIE    =  INPUT_;
			sGpioPort1.puGpioIES->regGpioIES  =  PULL_UP_;
			sGpioPort1.puGpioIFG->regGpioIFG &= ~INPUT_;
			__bis_SR_register(GIE);
		}
	}
	if (PORT_ == PORT2)
	{
		sGpioPort2.puGpioREN->regGpioREN  = INPUT_;
		sGpioPort2.puGpioOUT->regGpioOUT |= PULL_UP_;
		if(INT_PORT_ == INT_PORT_ON)
		{
			sGpioPort2.puGpioIE->regGpioIE    =  INPUT_;
			sGpioPort2.puGpioIES->regGpioIES  =  PULL_UP_;
			sGpioPort2.puGpioIFG->regGpioIFG &= ~INPUT_;
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
 *	END OF GPIO_1_3_1.c
 *************************************************************************************************/

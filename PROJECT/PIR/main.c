/*
 *	File			:	main.c
 *	Date created	:	05/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Explore PIR sensor
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *					  PIN MAPPING
 *		PIR module					MSP430G2553				Warning module
 *		OUT1						P1.4
 *		OUT2						P1.5
 *									P1.0					LED_RED
 *************************************************************************************************/
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>
#include "VERSION 1_2_1/CLOCK_1_2_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_1/USCI_UART_1_2_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Pins */
#define			OUT		BIT4	// P1.4

/* Variables, arrays, structs */
char varRxd;
char varStatus = LOW;
char varCount;

/* Externals */
extern const clk_Setup sClkSetup;
extern const uart_Setup sUartSetup;


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
int main (void)
{
	/* SETUP */
	//-Clock and Watchdog timer-//
	clkSetup(sClkSetup.sDco1mhz.sSwdtOn);
	//-GPIO-//
	gpioSetup(PORT1, LED_RED + LED_GREEN + OUT, LED_RED + LED_GREEN);
	ledOn(LED_RED);
	for(varCount = 0; varCount < 2; varCount++)	// Delay 20s for preparing module PIR
	{
		__delay_cycles(DL_10S);
	}
	ledOff(LED_RED);
	gpioIntSetup(PORT1, OUT, 0, INT_PORT_OFF);
	ledOn(LED_GREEN);
	//-UART-//
	uartSetup(sUartSetup.sSmclk1Mhz.sBaud9600.sIntRxdOff);
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		if((P1IN & OUT))
		{
			ledOff(LED_GREEN);
			ledOn(LED_RED);
			__delay_cycles(DL_1S);
			__delay_cycles(DL_500MS);
			ledOff(LED_RED);
			ledOn(LED_GREEN);
		}
	}
//-------------------------------------------------------------------------------------------------
	/* FINISH */
	return 1;
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

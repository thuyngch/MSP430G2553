/*
 *	File			:	main.c
 *	Created date	:	13/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	IDE				:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct Watchdog Timer library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "VERSION 1_0_1/WATCHDOG_1_0_1.h"


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-CLK-//
	BCSCTL1  = CALBC1_1MHZ;
	DCOCTL   = CALDCO_1MHZ;

	//-Watchdog-//
	wdtSetup(WDT_ON, WDT_TIME_32MS);

	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);

	//-UART-//
//	uartSetup(CLKS_SMCLK_1MHZ, BAUD_9600, INT_RXD_ON);
//-------------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
		gpioToggle(PORT1, LED_RED);
		__delay_cycles(DL_10MS);
		wdtClear();
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/**/
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

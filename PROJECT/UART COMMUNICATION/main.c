/*
 *	File			:	main.c
 *	Date created	:	25/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.2.3
 *	Description		:	Explore UART communication between 2 chips
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include "VERSION 1_2_3/CLOCK_1_2_3.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
unsigned char varRxd;
unsigned char varAngle;
unsigned char varDirection;


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-Clock-//
	clkSetup(sClkSetup.sDco16mhz.sSwdtOn);

	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);

	//-UART-//
//	uartSetup(sUartSetup.sSmclk16Mhz.sBaud9600.sIntRxdOff);	// For transmitter chip
	uartSetup(sUartSetup.sSmclk16Mhz.sBaud9600.sIntRxdOn);	// For receiver chip
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		//-For transmitter chip-//
//		ledToggle(LED_RED);
//		txdChar(97);
//		__delay_cycles(DL_1S*16);

		//-For receiver chip-//
		ledToggle(LED_RED);
		__delay_cycles(DL_100MS*16);
		//txdStr("Chinh Thuy\n");
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	varRxd = rxdChar();
	txdChar(varRxd);
	txdChar(ENTER);
}


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

/*
 *	File			:	main.c
 *	Date created	:	24/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Explore SPI communication between 2 chips.
 *						CLK_DCO = 16Mhz. SPI_RATE = 4MHz.
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"
#include "VERSION 1_0_1/USCI_SPI_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
#define			FREQUENCY			16	// 16MHz
#define			CMD_TURN_ON_LED		1
#define			CMD_TURN_OFF_LED	0

/* Globals */
volatile char varRx;


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-Clock-//
	clkSetup(CLK_DCO_16MHZ);

	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);

	//-SPI-//
	spiA0Setup(SPI_SLAVE, 40, INT_SPIA0_RX_ON, INT_SPIA0_TX_OFF);	// For slave
	__bis_SR_register(GIE);
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		__delay_cycles(1);

		 if(varRx == 0)	spiA0MstWriteByte(20);
		 else if(varRx == 1)	spiA0MstWriteByte(10);
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxIsr(void)
{
	varRx = UCA0RXBUF;				// Get received data
}

/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

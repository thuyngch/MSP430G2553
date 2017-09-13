/*
 *	File			:	main.c
 *	Date created	:	21/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Explore Motor Encoder
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>
#include <stdio.h>
#include "VERSION 1_2_1/CLOCK_1_2_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_1/USCI_UART_1_2_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Pins */
#define			ENCODER			BIT4	// P1.4

/* Externals */
extern const clk_Setup sClkSetup;
extern const uart_Setup sUartSetup;

/* Variables, Arrays */
int varPulNumber = 0;
unsigned char strPulNumber[5];
char varCount;
char varRxd;


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void port1Int (void)
{
	if(P1IFG & ENCODER)
	{
		varPulNumber++;
		//-Exit ISR-//
		P1IFG &= ~ ENCODER;
	}
}

void rxdInt (void)
{
	varRxd = rxdChar();
	if(varRxd == '0')
	{
		sprintf(strPulNumber, "%d", varPulNumber);
		txdStr(strPulNumber);
		txdChar(10);
		varPulNumber = 0;
	}
}


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-Clock & Watchdog timer-//
	clkSetup(sClkSetup.sDco16mhz.sSwdtOn);

	//-GPIO-//
	gpioSetup(PORT1, ENCODER, 0);
	gpioIntSetup(PORT1, ENCODER, 0, INT_PORT_ON);

	//-UART-//
	uartSetup(sUartSetup.sSmclk16Mhz.sBaud9600.sIntRxdOn);
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
//		if((P1IN & ENCODER))
//		{
//			varPulNumber++;
//			sprintf(strPulNumber, "%d", varPulNumber);
//			txdStr(strPulNumber);
//			txdChar(10);
//		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
#pragma vector = PORT1_VECTOR
__interrupt void port1Isr (void)
{
	if(P1IFG & ENCODER)
	{
		varPulNumber++;
		//-Exit ISR-//
		P1IFG &= ~ ENCODER;
	}
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	rxdInt();
}


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

/*
 * 	File			:	main.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	04/06/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Bluetooth HC-05
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/USCI_UART_1_0_1.h"


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
unsigned char varRxd;


/****************************************************************************************
 *	SUB-ROUTINEs
 ***************************************************************************************/
void rxdInt (void)
{
	varRxd = rxdChar();
	txdChar(varRxd);
	ledOn(LED_RED);
	__delay_cycles(DL_500MS);
	ledOff(LED_RED);
}


/****************************************************************************************
 *	MAIN-ROUTINE
 ***************************************************************************************/
int main (void)
{
	/* SETUP */
	/* DCO, f = 1MHz, Stop watchdog timer */
	clkSetup(CLK_DCO_1MHZ, SWDT_ON);

	/* GPIO */
	gpioSetup(PORT1, LED_RED + LED_GREEN + BUTTON, LED_RED + LED_GREEN);
	ledOn(LED_RED);
	gpioIntSetup(PORT1, BUTTON, BUTTON);
	__delay_cycles(DL_2S);

	/* UART */
	uartSetup(CLKS_SMCLK_1MHZ, BAUD_9600, INT_RXD_ON);

	/* Prepare for system */
	ledOff(LED_RED);

//---------------------------------------------------------------------------------------

	/* PROCESS */
	while(1)
	{
		ledToggle(LED_GREEN);
		__delay_cycles(DL_1S);
	}
	return 1;
}

/****************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 ***************************************************************************************/
/* RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	rxdInt();
}


/****************************************************************************************
 *	END OF main.c
 ***************************************************************************************/

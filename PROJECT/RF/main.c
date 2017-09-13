/*
 * 	File			:	main.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	28/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct SRF-05 module
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>
#include "VERSION 1_0_1\GPIO_1_0_1.h"
#include "VERSION 1_0_1\USCI_UART_1_0_1.h"

/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
unsigned char varData;


/****************************************************************************************
 *	SUB-ROUTINEs
 ***************************************************************************************/


/****************************************************************************************
 *	MAIN-ROUTINE
 ***************************************************************************************/
int main (void)
{
	/* SETUP */
	WDTCTL   = WDTPW + WDTHOLD;

	// DCO_CLK(1MHz) //
	BCSCTL1  = CALBC1_1MHZ;
	DCOCTL   = CALDCO_1MHZ;

	// UART //
	uartSetup();

	// GPIO //
	gpioSetup(PORT1, LED_RED + LED_GREEN, LED_RED + LED_GREEN);
	ledOn(LED_RED);

	// Prepare //
	__delay_cycles(1000000);
	_BIS_SR(GIE);
	ledOff(LED_RED);


	/* PROCESS */
	while(1)
	{
		txdStr("Nguyen Chinh Thuy\n");
		__delay_cycles(1000000);
	}
	return 1;
}


/****************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 ***************************************************************************************/
/* RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdInt (void)
{
	varData = rxd();
	txdStr("PC respond: ");
	txdChar(varData);
	txdChar('\n');
}


/****************************************************************************************
 *	END OF main.c
 ***************************************************************************************/

/*
 *	File			:	main.c
 *	Date created	:	09/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Library of DMA
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include <stdio.h>

#include "Source Files/Header.h"
#include "Library Files/CLOCK_1_0_1.h"
#include "Library Files/WATCHDOG_1_0_1.h"
#include "Library Files/GPIO_1_0_1.h"
#include "Library Files/USCI_UART_1_0_1.h"


/**************************************************************************************************
 *	DECLAREs
 *************************************************************************************************/
unsigned char varRxd;
unsigned int varADC;
unsigned char strBuff[50];
unsigned int varChannel;


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-Clock-//
	clkSetup(CLK_DCO_8MHZ);

	//-Watchdog-//
	wdtSetup(WDT_OFF, WDT_TIME_32MS);

	//-GPIO-//
	gpioSetup(PORT1, LED_GREEN, LED_GREEN);

	//-UART-//
	uartSetup(CLKS_SMCLK_8MHZ, BAUD_9600, INT_RXD_ON);

	//-ADC10-//
	adc10Setup(ADC10_VREF_VCC, ADC10_RATE_X64, ADC10_BUFF_200, ADC10_INT_OFF);
	varChannel = ADC10_IN_A0;
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		varADC = adc10Read(varChannel);

		sprintf((char*)strBuff, "%d", varADC);
		txdStr(strBuff);
		txdChar(10);
		gpioToggle(PORT1, LED_GREEN);
		__delay_cycles(DL_1S);
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void RXD_ISR (void)
{
	varRxd = rxdChar();
	switch (varRxd)
	{
		case '0':
			varChannel = ADC10_IN_A0;
			break;
		case '1':
			varChannel = ADC10_IN_A1;
			break;
		case '2':
			varChannel = ADC10_IN_A2;
			break;
		case '3':
			varChannel = ADC10_IN_A3;
			break;
		case '4':
			varChannel = ADC10_IN_A4;
			break;
		case '5':
			varChannel = ADC10_IN_A5;
			break;
		case '6':
			varChannel = ADC10_IN_A6;
			break;
		case '7':
			varChannel = ADC10_IN_A7;
			break;
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

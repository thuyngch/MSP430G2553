/*
 * 	File			:	main.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct MFRC522 library
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/CLOCK_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/WATCHDOG_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/GPIO_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/USCI_SPI_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/MFRC522_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/CHECK_ID_1_0_1.h"


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
#define		FREQUENCY		16	// 16MHz

/* Variables */
unsigned char arrID[5];
unsigned char varStatus;
int varNo;
int varNoOld;

/* Struct */
extern person sMembers[5];


/****************************************************************************************
 *	MAIN ROUTINE
 ***************************************************************************************/
void main (void)
{
	/* SETUP */
	//-CLOCK & WDT-//
	clkSetup(CLK_DCO_16MHZ);
	wdtSetup(WDT_OFF, WDT_TIME_8MS);

	//-GPIO-//
	gpioSetup(PORT2, LED_RED, LED_RED);

	//-UART-//
//	uartSetup(sUartSetup.sSmclk16Mhz.sBaud9600.sIntRxdOff);
//	txdStr("Starting RFID-RC522 module...\n");

	//-SPI-//
	spiA0Setup(SPI_MASTER, 2, INT_SPIA0_RX_OFF, INT_SPIA0_TX_OFF);

	//-MFRC522-//
	rfidSetup(RFID_PORT_2, BIT2, BIT3);
	__delay_cycles(DL_2S * FREQUENCY);
//---------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		//-Detect card and get card's ID-//
		varStatus = rfidGetCardID(arrID);
		//-Process signal-//
		if (varStatus == MI_OK)
		{
			gpioHigh(PORT2, LED_RED);						// Card detected!
			varNo = checkID(arrID, sMembers);				// Check card
			//-If the card is repeated, don't show to screen-//
//			dispScreen(&varNo, &varNoOld, arrID, sMembers, REPEAT_NON);
			__delay_cycles(DL_1S * FREQUENCY);				// delay 1s
			gpioLow(PORT2, LED_RED);
		}
	}
}
/****************************************************************************************
 *	END OF main.c
 ***************************************************************************************/

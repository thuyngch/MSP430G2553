/*
 *	File			:	main.c
 *	Date created	:	12/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct Flash Memory library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include "VERSION 1_2_3/CLOCK_1_2_3.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"
#include "VERSION 1_0_1/FLASH_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define			FREQUENCY			1	// 1Mhz

/* Flash */
#define			POSITION			10	// Use for byte
#define			POSITION_INIT		20	// Use for array
#define			NUM_BYTE			5	// Use for array

/* Buffer */
#define			BUFF_LENGTH			50	// 50 bytes of buffer


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
unsigned char varFlashData;
unsigned char arrFlashData[NUM_BYTE];
unsigned char strBuff[BUFF_LENGTH];


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-Clock-//
	clkSetup(sClkSetup.sDco1mhz.sSwdtOn);

	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);

	//-UART-//
	uartSetup(sUartSetup.sSmclk1Mhz.sBaud9600.sIntRxdOff);

	//-FLASH-//
	flashSetup(CLK_DCO_1MHZ);
//	varFlashData = 'A';
//	arrFlashData[0] = 97; arrFlashData[1] = 98; arrFlashData[2] = 99; arrFlashData[3] = 100; arrFlashData[4] = 101;
	__delay_cycles(DL_1S * FREQUENCY);
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	//-Notify UART success-//
	txdStr("Initiate succesfully!\n");

	//-Write and read byte-//
//	flashWriteByte(segC, varFlashData, POSITION);
	flashReadByte(segC, &varFlashData, POSITION);
	sprintf((char*)strBuff, "Value: %c\n", varFlashData);
	txdStr(strBuff);
	__delay_cycles(DL_1S * FREQUENCY);

	//-Write and read block-//
//	flashWriteBlock(segC, arrFlashData, POSITION_INIT, NUM_BYTE);
	flashReadBlock(segC, arrFlashData, POSITION_INIT, NUM_BYTE);
	sprintf((char*)strBuff, "D1: %c, D2: %c, D3: %c, D4: %c, D5: %c\n",
			arrFlashData[0], arrFlashData[1], arrFlashData[2], arrFlashData[3], arrFlashData[4]);
	txdStr(strBuff);
	__delay_cycles(DL_1S * FREQUENCY);

	//-Loop-//
	while(1)
	{
		ledToggle(LED_RED);
		__delay_cycles(DL_1S * FREQUENCY);
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

/*
 *	File			:	main.c
 *	Date created	:	08/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Keypad 4x4
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>					// From producer
#include "VERSION 1_2_3/CLOCK_1_2_3.h"		// Struct inside struct
#include "VERSION 1_0_1/GPIO_1_0_1.h"		// Const parameters
#include "VERSION 1_2_3/TIMERA_1_2_3.h"		// Struct inside struct
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"	// Struct inside struct


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Clock of system */
#define			FREQUENCY			8	// 8MHz

/* Delay interval */
#define			DL_ANTI_NOISE		120000	// 120ms
#define			DL_OUT				200000	// 200ms
#define			DL_UART_TXD			50000	// 50ms

/* Keypad pins */
#define			KEYPAD_IN			0x0F	// P2.0 -> P2.3
#define			KEYPAD_IN_1			BIT0	// P2.0
#define			KEYPAD_IN_2			BIT1	// P2.1
#define			KEYPAD_IN_3			BIT2	// P2.2
#define			KEYPAD_IN_4			BIT3	// P2.3

#define			KEYPAD_OUT			0xF0	// P2.4 -> P2.7
#define			KEYPAD_OUT_1		BIT4	// P2.4
#define			KEYPAD_OUT_2		BIT5	// P2.5
#define			KEYPAD_OUT_3		BIT6	// P2.6
#define			KEYPAD_OUT_4		BIT7	// P2.7


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
volatile unsigned char varCount;
unsigned char arrOut[4] = {0xEF, 0xDF, 0xBF, 0x7F};
unsigned char strBuff[7];


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
	//-CLK & WDT-//
	clkSetup(sClkSetup.sDco8mhz.sSwdtOn);	// DCO = 8MHz, Stop watchdog timer

	//-GPIO-//
	gpioSetup(PORT1, LED_RED + LED_GREEN, LED_RED + LED_GREEN);
	gpioSetup(PORT2, 0xFF, KEYPAD_OUT);
	gpioIntSetup(PORT2, KEYPAD_IN, KEYPAD_IN, INT_PORT_ON);

	//-UART-//
	uartSetup(sUartSetup.sSmclk8Mhz.sBaud9600.sIntRxdOff);
//-------------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
		for(varCount = 0; varCount < 4; varCount++)
		{
			ledToggle(LED_GREEN);
			P2OUT = arrOut[varCount];
			__delay_cycles(DL_OUT);
		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* PORT2 */
#pragma vector = PORT2_VECTOR
__interrupt void port2Isr (void)
{
	ledToggle(LED_RED);
	switch (P2IFG & KEYPAD_IN)
	{
		case KEYPAD_IN_1:
		{
			switch (varCount)
			{
				case 0:
					txdStr("1\n");
					break;
				case 1:
					txdStr("2\n");
					break;
				case 2:
					txdStr("3\n");
					break;
				case 3:
					txdStr("A\n");
					break;
				default:
					break;
			}
			break;
		}
		case KEYPAD_IN_2:
		{
			switch (varCount)
			{
				case 0:
					txdStr("4\n");
					break;
				case 1:
					txdStr("5\n");
					break;
				case 2:
					txdStr("6\n");
					break;
				case 3:
					txdStr("B\n");
					break;
				default:
					break;
			}
			break;
		}
		case KEYPAD_IN_3:
		{
			switch (varCount)
			{
				case 0:
					txdStr("7\n");
					break;
				case 1:
					txdStr("8\n");
					break;
				case 2:
					txdStr("9\n");
					break;
				case 3:
					txdStr("C\n");
					break;
				default:
					break;
			}
			break;
		}
		case KEYPAD_IN_4:
		{
			switch (varCount)
			{
				case 0:
					txdStr("*\n");
					break;
				case 1:
					txdStr("0\n");
					break;
				case 2:
					txdStr("#\n");
					break;
				case 3:
					txdStr("D\n");
					break;
				default:
					break;
			}
			break;
		}
		default:
			sprintf((char*)strBuff, "%x", P2IFG);
			txdStr(strBuff);
			txdChar(ENTER);
			break;
	}
	__delay_cycles(DL_ANTI_NOISE * FREQUENCY);
	P2IFG  = 0;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

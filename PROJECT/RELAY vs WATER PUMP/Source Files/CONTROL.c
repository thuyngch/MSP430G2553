/*
 *	File			:	COMMUNICATION.c
 *	Date created	:	10/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Source for communication (I2C)
 *	Target object	:	MSP430G2553
 */
#define	USE_KEYPAD_LCD
#define	USE_CLOCK_1_2_3
#define	USE_USCI_UART_1_2_3
#define USE_TIMERA_1_2_3
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "main.h"


/**************************************************************************************************
 *	EXTERNs
 *************************************************************************************************/
extern unsigned char varCountData;
extern unsigned char varRx;
extern unsigned char arrCommunication[I2C_NUM_BYTE];

extern unsigned int regFirmPeriod;
extern unsigned int regFirmDuty;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	controlRelay
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void controlRelayOn (unsigned char varPort1, unsigned char varPort2)
{
	P1OUT |= (varPort1 & IO_PORT1_PIN);
	P2OUT |= (varPort2 & IO_PORT2_PIN);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void controlRelayOff (unsigned char varPort1, unsigned char varPort2)
{
	P1OUT &= ~(varPort1 & IO_PORT1_PIN);
	P2OUT &= ~(varPort2 & IO_PORT2_PIN);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF COMMUNICATION.c
 *************************************************************************************************/

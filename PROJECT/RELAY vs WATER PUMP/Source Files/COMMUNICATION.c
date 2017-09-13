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
 * 	Function:	communicationDecode
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void communicationDecode (void)
{
	regFirmPeriod = (arrCommunication[0] | (arrCommunication[1] << 8));
	regFirmDuty   = (arrCommunication[2] | (arrCommunication[3] << 8));
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	communicationConvertDCB
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void communicationConvertDCB (unsigned int *pNumber)
{
	unsigned char varUnit, varDecimal, varHundred, varThousand;
	varUnit     = ((*pNumber & BCD_UNIT) >> 0);
	varDecimal  = ((*pNumber & BCD_DECI) >> 4);
	varHundred  = ((*pNumber & BCD_HUND) >> 8);
	varThousand = ((*pNumber & BCD_THOU) >> 12);
	*pNumber    = (1000*varThousand + 100*varHundred + 10*varDecimal + varUnit);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void communicationTestRXData (void)
{
	if(varCountData == 6)
	{
		sprintf((char*)strBuff, "%d", regFirmPeriod);
		txdStr("Period = ");	txdStr(strBuff);	txdChar(SPACE);		// Print Period
		sprintf((char*)strBuff, "%d", regFirmDuty);
		txdStr("Duty = ")  ;	txdStr(strBuff);	txdChar(ENTER);		// Print Duty
		__delay_cycles(DL_500MS * FREQUENCY);							// Safe delay
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF COMMUNICATION.c
 *************************************************************************************************/

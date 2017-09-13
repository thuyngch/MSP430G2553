/*
 *	File			:	DS1307_1_0_3.c
 *	Date created	:	23/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.3
 *	Description		:	Construct DS1307 library
 *	Target object	:	MSP430G2553
 */
#define USE_DS1307_1_0_3
#define USE_USCI_UART_1_2_3
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "DS1307_1_0_3.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Externals */
extern unsigned char varSecond, varMinute, varHour, varDay, varDate, varMonth, varYear;
extern unsigned char arrRtcData[DS1307_BYTE_OF_DATA];


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	ds1307Setup
 *	Purpose	:	Setup original time for DS1307
 * 	Input	:	varHr: Hour
 * 				varMin: Minute
 * 				varSec: Second
 * 				varWd: Week day
 * 				varD: Date
 * 				varMth: Month
 * 				varYr: Year
 * 	Output	:	None
 */
void ds1307Setup(unsigned char varHr, unsigned char varMin, unsigned char varSec, // hh:mm:ss
				 unsigned char varWd,											  // Week day
				 unsigned char varD, unsigned char varMth, unsigned char varYr)   // dd/mm/yy
{
	arrRtcData[0] = ds1307DecBcd(varSec);
	arrRtcData[1] = ds1307DecBcd(varMin);
	arrRtcData[2] = ds1307DecBcd(varHr);
	arrRtcData[3] = ds1307DecBcd(varWd);
	arrRtcData[4] = ds1307DecBcd(varD);
	arrRtcData[5] = ds1307DecBcd(varMth);
	arrRtcData[6] = ds1307DecBcd(varYr);
	// Pointer register automatically increments after each data byte are written
	i2cMstWriteArray(DS1307_SECONDS, arrRtcData, DS1307_BYTE_OF_DATA);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ds1307Read
 *	Purpose	:	Read RTC data from DS1307
 * 	Input	:	None
 * 	Output	:	None
 */
void ds1307Read (void)
{
	i2cMstReadArray(DS1307_SECONDS, arrRtcData, DS1307_BYTE_OF_DATA);

	varSecond	= ds1307BcdDec(arrRtcData[1] & 0x7F);
	varMinute	= ds1307BcdDec(arrRtcData[2]);
	varHour		= ds1307BcdDec(arrRtcData[3] & 0x3F);		// 24h mode
	varDay		= ds1307BcdDec(arrRtcData[4]);
	varDate		= ds1307BcdDec(arrRtcData[5]);
	varMonth	= ds1307BcdDec(arrRtcData[6]);
	varYear		= ds1307BcdDec(arrRtcData[0]);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ds1307BcdDec
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
unsigned char ds1307BcdDec(unsigned char varNumber)
{
	return ((varNumber/16 * 10) + (varNumber % 16));
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ds1307DecBcd
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
unsigned char ds1307DecBcd(unsigned char varNumber)
{
	return ((varNumber/10 * 16) + (varNumber % 10));
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void ds1307Print(void)
{
	unsigned char strBuff[5];
	sprintf((char*)strBuff, "%d", varHour);
    txdStr(strBuff);
    txdChar(':');
    ds1307PrintDigit(varMinute);
    txdChar(':');
    ds1307PrintDigit(varSecond);
    txdChar(' ');
    switch (varDay)
    {
		case 1:
			txdStr("Sun");
			break;
		case 2:
			txdStr("Mon");
			break;
		case 3:
			txdStr("Tue");
			break;
		case 4:
			txdStr("Wed");
			break;
		case 5:
			txdStr("Thu");
			break;
		case 6:
			txdStr("Fri");
			break;
		case 7:
			txdStr("Sat");
			break;
		default:
			break;
	}
    txdChar(' ');
    sprintf((char*)strBuff, "%d", varDate);
    txdStr(strBuff);
    txdChar('/');
    sprintf((char*)strBuff, "%d", varMonth);
    txdStr(strBuff);
    txdChar('/');
    txdStr("20");
    ds1307PrintDigit(varYear);
    txdChar(10);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	ds1307PrintDigit
 *	Purpose	:	Print each digit of number (0 <= number <= 99)
 * 	Input	:	varNumber: Number needed to print its each digit
 * 	Output	:	None
 */
void ds1307PrintDigit(int varNumber)
{
	unsigned char strDigit[3];
	sprintf((char*)strDigit, "%d", varNumber);
    if(varNumber < 10)
    {
        txdChar('0');
    }
    txdStr(strDigit);
}


/**************************************************************************************************
 *	END OF DS1307_1_0_3.c
 *************************************************************************************************/

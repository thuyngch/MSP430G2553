/*
 *	File			:	Display_0_0_101.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for Display
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER_0_0_101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Describe each digit in terms of display segments */
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, none
static char arrNum7Seg[17] = {0b00000011, 0b10011111, 0b00100101, 0b00001101, 0b10011001,
		0b01001001, 0b01000001, 0b00011111, 0b00000001, 0b00001001, 0b00010001, 0b11000001,
		0b01100011, 0b10000101, 0b01100001, 0b01110001, 0b11111111};


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void displayHour (unsigned char varNumber)
{
	display4017Calib();
	ic74HC595Data(arrNum7Seg[16]);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	unsigned char varTenthDigit = 0, varUnitDigit = 0, varCount;
	digitDivide(varNumber, &varTenthDigit, &varUnitDigit);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[varTenthDigit]);	// Position S0 of 74HC4017
	__delay_cycles(500);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);

	P1OUT |= PIN_4017;					// Position S1 of 74HC4017
	__delay_cycles(10);
	ic74HC595Data(arrNum7Seg[varUnitDigit]);
	P1OUT &= ~PIN_4017;
	__delay_cycles(500);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);
	for(varCount = 0; varCount < 5; varCount++)		// Reset position of 74HC4017
	{
		P1OUT |= PIN_4017;
		__delay_cycles(1);
		P1OUT &= ~PIN_4017;
		__delay_cycles(1);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void displayMinute (unsigned char varNumber)
{
	display4017Calib();
	ic74HC595Data(arrNum7Seg[16]);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	unsigned char varTenthDigit = 0, varUnitDigit = 0, varCount;
	digitDivide(varNumber, &varTenthDigit, &varUnitDigit);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);
	for(varCount = 0; varCount < 1; varCount++)		// Move position of 74HC4017 to S2
	{
		P1OUT |= PIN_4017;
		__delay_cycles(1);
		P1OUT &= ~PIN_4017;
		__delay_cycles(1);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}

	P1OUT |= PIN_4017;			// Position S2 of 74HC4017
	__delay_cycles(10);
	ic74HC595Data(arrNum7Seg[varTenthDigit]);
	P1OUT &= ~PIN_4017;
	__delay_cycles(500);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);

	P1OUT |= PIN_4017;			// Position S3 of 74HC4017
	__delay_cycles(10);
	ic74HC595Data(arrNum7Seg[varUnitDigit]);
	P1OUT &= ~PIN_4017;
	__delay_cycles(500);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);
	for(varCount = 0; varCount < 3; varCount++)		// Reset position of 74HC4017
	{
		P1OUT |= PIN_4017;
		__delay_cycles(1);
		P1OUT &= ~PIN_4017;
		__delay_cycles(1);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void displaySecond (unsigned char varNumber)
{
	display4017Calib();
	ic74HC595Data(arrNum7Seg[16]);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	unsigned char varTenthDigit = 0, varUnitDigit = 0, varCount;
	digitDivide(varNumber, &varTenthDigit, &varUnitDigit);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	for(varCount = 0; varCount < 3; varCount++)		// Move position of 74HC4017 to S3
	{
		P1OUT |= PIN_4017;
		__delay_cycles(1);
		P1OUT &= ~PIN_4017;
		__delay_cycles(1);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}

	P1OUT |= PIN_4017;			// Position S4 of 74HC4017
	__delay_cycles(10);
	ic74HC595Data(arrNum7Seg[varTenthDigit]);
	P1OUT &= ~PIN_4017;
	__delay_cycles(500);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	P1OUT |= PIN_4017;			// Position S5 of 74HC4017
	__delay_cycles(10);
	ic74HC595Data(arrNum7Seg[varUnitDigit]);
	P1OUT &= ~PIN_4017;
	__delay_cycles(500);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	ic74HC595Data(arrNum7Seg[16]);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	P1OUT |= PIN_4017;
	__delay_cycles(1);
	P1OUT &= ~PIN_4017;
	__delay_cycles(1);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
display4017Calib (void)
{
	if(!(P1IN & PIN_READ_4017))
	{
		gpioHigh(PORT1, PIN_4017);
		__delay_cycles(10);
		gpioLow(PORT1, PIN_4017);
		__delay_cycles(10);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Display_0_0_101.c
 *************************************************************************************************/

/*
 *	File			:	Header.h
 *	Date created	:	09/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Library of ADC10
 */
#ifndef ADC10_1_0_1_H
#define ADC10_1_0_1_H
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include <msp430g2553.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Voltage reference */
#define		ADC10_VREF_VCC		SREF_0		// VCC = 3.3V
#define		ADC10_VREF_EXT		SREF_2		// External voltage

//-------------------------------------------------------------------------------------------------
/* Sampling rate */
#define		ADC10_RATE_X4		ADC10SHT_0	// 4*ADC10CLKs
#define		ADC10_RATE_X8		ADC10SHT_0	// 8*ADC10CLKs
#define		ADC10_RATE_X16		ADC10SHT_0	// 16*ADC10CLKs
#define		ADC10_RATE_X64		ADC10SHT_0	// 64*ADC10CLKs

//-------------------------------------------------------------------------------------------------
/* Buffer */
#define		ADC10_BUFF_200		0			// Support for up to ~200ksps
#define		ADC10_BUFF_50		0			// Support for up to ~50ksps

//-------------------------------------------------------------------------------------------------
/* Interrupt */
#define		ADC10_INT_OFF		0			// Disable ADC10 interrupt
#define		ADC10_INT_ON		ADC10IE		// Enable ADC interrupt

//-------------------------------------------------------------------------------------------------
/* Input channel */
#define		ADC10_IN_A0			INCH_0		// A0
#define		ADC10_IN_A1			INCH_1		// A1
#define		ADC10_IN_A2			INCH_2		// A2
#define		ADC10_IN_A3			INCH_3		// A3
#define		ADC10_IN_A4			INCH_4		// A4
#define		ADC10_IN_A5			INCH_5		// A5
#define		ADC10_IN_A6			INCH_6		// A6
#define		ADC10_IN_A7			INCH_7		// A7
#define		ADC10_IN_TEMP		INCH_10		// Temperature sensor

//-------------------------------------------------------------------------------------------------
/* Data Transfer Conversion */
#define		ADC10_DTC_OFF		0			// Disable DTC
#define		ADC10_DTC_ON

//-------------------------------------------------------------------------------------------------
/**/


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/**/
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void			adc10Setup		(unsigned int ADC10_VREF_, unsigned int ADC10_RATE_,
										unsigned int ADC10_BUFF_, unsigned int ADC10_INT_);
void			adc10Stop		(void);
void			adc10DTCSetup	(unsigned int ADC10_IN_, unsigned int arrValue[]); // Not completed

/* Conversion */
unsigned int	adc10Read		(unsigned int ADC10_IN_);


/**************************************************************************************************
 *	END OF Header.h
 *************************************************************************************************/
#endif /* ADC_1_0_1_H */

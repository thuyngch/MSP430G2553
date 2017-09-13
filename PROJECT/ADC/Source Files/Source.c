/*
 *	File			:	Source.c
 *	Date created	:	09/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Library of ADC
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "Header.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


 /**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	adcSetup
 *	Purpose	:	Setup ADC
 *	Input	:	ADC_VREF_: Voltage reference
 *				ADC_RATE_: Sampling rate
 *				ADC_BUFF_: Buffer enough for sampling rate
 *				ADC10_DTC_:
 *				ADC10_INT_:
 *	Output	:	None
 */
void adc10Setup (unsigned int ADC10_VREF_, unsigned int ADC10_RATE_, unsigned int ADC10_BUFF_,
							unsigned int ADC10_INT_)
{
	ADC10CTL0 &= ~ENC;									// Disable conversion
	while(ADC10CTL1 & ADC10BUSY);						// Wait for ADC free

	ADC10CTL0 = ADC10_VREF_ | ADC10_RATE_ | ADC10_BUFF_ | MSC | ADC10ON | ADC10_INT_;

	if (ADC10_VREF_ == ADC10_VREF_EXT)
	{
		ADC10CTL0 |= REFOUT;
	}

	ADC10CTL1 = CONSEQ_0;								// Single-channel-single-conversion

	ADC10DTC0 = 0;										// Disable DTC
	ADC10DTC1 = 0;										// Disable DTC

    ADC10CTL0 |= ENC;									// Enable conversion
    ADC10CTL0 |= ADC10SC;								// Start conversion
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	adc10Stop
 *	Purpose	:	Stop ADC10
 *	Input	:	None
 *	Output	:	None
 */
void adc10Stop (void)
{
	ADC10CTL0 &= ~ADC10ON;		// Disable ADC10
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	adc10DTCSetup
 *	Purpose	:	Setup Data Conversion Transfer
 *	Input	:
 *	Output	:	None
 */
void adc10DTCSetup (unsigned int ADC10_IN_, unsigned int arrValue[])
{
	ADC10CTL0 &= ~ENC;									// Disable conversion
	while(ADC10CTL1 & ADC10BUSY);						// Wait for ADC free

	// Reduce consumption
    P1DIR &= ~ADC10_IN_;
    P1OUT &= ~ADC10_IN_;
    P1REN &= ~ADC10_IN_;

    ADC10DTC0 = ADC10CT;								// ADC10 continuous transfer
    ADC10SA = ((unsigned int)arrValue);					//

    ADC10CTL0 |= ENC;									// Enable conversion
    ADC10CTL0 |= ADC10SC;								// Start conversion
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	adc10Read
 *	Purpose	:	Read ADC10 value from a channel
 *	Input	:	ADC10_IN_: ADC10 Channel
 *	Output	:	Value of ADC10
 */
unsigned int adc10Read (unsigned int ADC10_IN_)
{
	if((ADC10CTL1 & 0xF000) != ADC10_IN_)	// Different channel
	{
		ADC10CTL0 &= ~( ADC10SC + ENC);			// Disable conversion

		ADC10AE0 = ADC10_IN_;					// Enable analog input pin
		ADC10CTL1 &= 0x0FFF;					// Erase 4-highest bits
		ADC10CTL1 |= ADC10_IN_;					// Change channel

		ADC10CTL0 &= ~ADC10IFG;					// Disable interrupt flag
		ADC10CTL0 |=  ADC10SC + ENC;			// Enable and start conversion

		while(!(ADC10CTL0 & ADC10IFG));			// Wait until conversion completely
		return ADC10MEM;						// Return value of ADC10
	}
	else									// Same channel
	{
		ADC10CTL0 &= ~ADC10IFG;					// Disable interrupt flag
		ADC10CTL0 |=  ADC10SC + ENC;			// Enable and start conversion
		while(!(ADC10CTL0 & ADC10IFG));			// Wait until conversion completely
		return ADC10MEM;						// Return value of ADC10
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
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Source.c
 *************************************************************************************************/

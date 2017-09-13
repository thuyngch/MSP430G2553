/*
 *	File			:	CLOCK_1_0_1.h
 *	Date created	:	31/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct Clock library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about Clock.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
#ifndef CLOCK_1_0_1_H_
#define CLOCK_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* DCO Oscillator and frequency */
#define		CLK_DCO_1MHZ		1
#define		CLK_DCO_8MHZ		2
#define		CLK_DCO_12MHZ		3
#define		CLK_DCO_16MHZ		4

/* Some special delay interval */
//-(Base on frequency = 1MHz)-//
//-s-//
#define		DL_10S				10000000
#define		DL_5S				5000000
#define		DL_2S				2000000
#define		DL_1S				1000000
//-ms-//
#define		DL_500MS			500000
#define		DL_100MS			100000
#define		DL_50MS				50000
#define		DL_10MS				10000
#define		DL_5MS				5000
#define		DL_1MS				1000


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void clkSetup (const unsigned int CLK_);


/**************************************************************************************************
 *	END OF CLOCK_1_0_1.h
 *************************************************************************************************/
#endif /* CLOCK_1_0_1_H_ */

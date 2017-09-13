/*
 *	File			:	GPIO_1_0_1.h
 *	Date created	:	28/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct GPIO library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about GPIO.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
/**************************************************************************************************
 *
 *************************************************************************************************/
#ifndef GPIO_1_0_1_H_
#define GPIO_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Logical levels */
#define		HIGH			1
#define		LOW				0

/* GPIO ports */
#define		PORT1			1
#define		PORT2			2

/* Special pins of Port 1 */
#define		LED_RED			BIT0	// P1.0
#define		BUTTON			BIT3	// P1.3
#define		LED_GREEN		BIT6	// P1.6

/* Enable interrupt */
#define		INT_PORT_ON		1
#define		INT_PORT_OFF	0


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void gpioSetup(const unsigned int PORT_, const unsigned int PIN_, const unsigned int OUTPUT_);
//-vector = PORT1_VECTOR or vector = PORT2_VECTOR-//
void gpioIntSetup(const unsigned int PORT_, const unsigned int INPUT_, const unsigned int PULL_UP_, const unsigned int INT_PORT_);

/* Basic states */
void gpioHigh (const unsigned int PORT_, const unsigned char PIN_);
void gpioLow (const unsigned int PORT_, const unsigned char PIN_);
void gpioToggle (const unsigned int PORT_, const unsigned char PIN_);


/**************************************************************************************************
 *	END OF GPIO_1_0_1.h
 *************************************************************************************************/
#endif /* GPIO_1_0_1_H_ */

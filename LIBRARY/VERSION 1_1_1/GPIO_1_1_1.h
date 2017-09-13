/*
 *	File			:	GPIO_1_1_1.h
 *	Date created	:	28/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.1.1
 *	Description		:	Construct GPIO library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *						PROGRESS
 *		This is the version 1.1.1 of this library about GPIO.
 *		In the version 1.0.1, functions operate with parameters as const unsigned char/int numbers.
 *		This version is released at 02/06/2016. In this version, all const parameters, which are t-
 *	ransfered into functions, are replaced by structs. In file source, we provide some structs that
 *	contain usual modes of configuration, users just need to declare them by key-word "extern" in -
 *	main.c file for taking these ones. Otherwise, people can also create new structs and transfer -
 *	them into functions. We recommend that if your purpose is variable, you should use version 1.0-
 *	.1, and if you want to operate your chip in some specific modes, you should create structs and
 *	version 1.1.1 is the better choice for you.
 *************************************************************************************************/
#ifndef GPIO_1_1_1_H_
#define GPIO_1_1_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* GPIO ports */
#define		PORT1			1
#define		PORT2			2

/* Special pins of Port 1 */
#define		LED_RED			BIT0	// P1.0
#define		BUTTON			BIT3	// P1.3
#define		LED_GREEN		BIT6	// P1.6

/* Struct for gpioSetup function */
typedef struct
{
	const unsigned int PORT_;	// Port 1 or 2?
	const unsigned int PIN_;	// Which will pins be setted?
	const unsigned int OUT_;	// Which will pins be setted as output?
} gpio_Setup;

/* Struct for gpioIntSetup function */
typedef struct
{
	const unsigned int PORT_;	// Port 1 or 2?
	const unsigned int IN_;		// Which will pins be setted as input?
	const unsigned int PULL_UP_;// Which will pins be pulled up?
} gpio_Int_Setup;


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void gpioSetup(const gpio_Setup sGpioSetup_);
//-vector = PORT1_VECTOR or vector = PORT2_VECTOR-//
void gpioIntSetup(const gpio_Int_Setup sGpioIntSetup_);

/* Basic LED */
//-(Just support for LED_RED and LED_GREEN)-//
void ledOn (const unsigned char LED_);
void ledOff (const unsigned char LED_);
void ledToggle (const unsigned char LED_);


/**************************************************************************************************
 *	END OF GPIO_1_1_1.h
 *************************************************************************************************/
#endif /* GPIO_1_1_1_H_ */

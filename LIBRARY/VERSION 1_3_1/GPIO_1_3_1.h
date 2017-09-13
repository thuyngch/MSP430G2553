/*
 *	File			:	GPIO_1_3_1.h
 *	Date created	:	18/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.3.1
 *	Description		:	Construct GPIO library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *************************************************************************************************/
/**************************************************************************************************
 *
 *************************************************************************************************/
#ifndef GPIO_1_3_1_H_
#define GPIO_1_3_1_H_
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

/* Address of registers */
#define		ADDR_GPIO_P1_SEL			((gpio_SEL*)	&P1SEL)
#define		ADDR_GPIO_P1_SEL2			((gpio_SEL2*) 	&P1SEL2)
#define		ADDR_GPIO_P1_DIR			((gpio_DIR*) 	&P1DIR)
#define		ADDR_GPIO_P1_IN				((gpio_IN*) 	&P1IN)
#define		ADDR_GPIO_P1_OUT			((gpio_OUT*) 	&P1OUT)
#define		ADDR_GPIO_P1_REN			((gpio_REN*) 	&P1REN)
#define		ADDR_GPIO_P1_IE				((gpio_IE*) 	&P1IE)
#define		ADDR_GPIO_P1_IES			((gpio_IES*) 	&P1IES)
#define		ADDR_GPIO_P1_IFG			((gpio_IFG*)	&P1IFG)

#define		ADDR_GPIO_P2_SEL			((gpio_SEL*)	&P2SEL)
#define		ADDR_GPIO_P2_SEL2			((gpio_SEL2*) 	&P2SEL2)
#define		ADDR_GPIO_P2_DIR			((gpio_DIR*) 	&P2DIR)
#define		ADDR_GPIO_P2_IN				((gpio_IN*) 	&P2IN)
#define		ADDR_GPIO_P2_OUT			((gpio_OUT*) 	&P2OUT)
#define		ADDR_GPIO_P2_REN			((gpio_REN*) 	&P2REN)
#define		ADDR_GPIO_P2_IE				((gpio_IE*) 	&P2IE)
#define		ADDR_GPIO_P2_IES			((gpio_IES*) 	&P2IES)
#define		ADDR_GPIO_P2_IFG			((gpio_IFG*)	&P2IFG)

/* Union of GPIO_SEL register */
typedef union
{
	unsigned char regGpioSEL;
	struct
	{
		unsigned bGpioSELPin0: 1;
		unsigned bGpioSELPin1: 1;
		unsigned bGpioSELPin2: 1;
		unsigned bGpioSELPin3: 1;
		unsigned bGpioSELPin4: 1;
		unsigned bGpioSELPin5: 1;
		unsigned bGpioSELPin6: 1;
		unsigned bGpioSELPin7: 1;
	};
} gpio_SEL;

/* Union of GPIO_SEL2 register */
typedef union
{
	unsigned char regGpioSEL2;
	struct
	{
		unsigned bGpioSEL2Pin0: 1;
		unsigned bGpioSEL2Pin1: 1;
		unsigned bGpioSEL2Pin2: 1;
		unsigned bGpioSEL2Pin3: 1;
		unsigned bGpioSEL2Pin4: 1;
		unsigned bGpioSEL2Pin5: 1;
		unsigned bGpioSEL2Pin6: 1;
		unsigned bGpioSEL2Pin7: 1;
	};
} gpio_SEL2;

/* Union of GPIO_DIR register */
typedef union
{
	unsigned char regGpioDIR;
	struct
	{
		unsigned bGpioDIRPin0: 1;
		unsigned bGpioDIRPin1: 1;
		unsigned bGpioDIRPin2: 1;
		unsigned bGpioDIRPin3: 1;
		unsigned bGpioDIRPin4: 1;
		unsigned bGpioDIRPin5: 1;
		unsigned bGpioDIRPin6: 1;
		unsigned bGpioDIRPin7: 1;
	};
} gpio_DIR;

/* Union of GPIO_IN register */
typedef union
{
	unsigned char regGpioIN;
	struct
	{
		unsigned bGpioINPin0: 1;
		unsigned bGpioINPin1: 1;
		unsigned bGpioINPin2: 1;
		unsigned bGpioINPin3: 1;
		unsigned bGpioINPin4: 1;
		unsigned bGpioINPin5: 1;
		unsigned bGpioINPin6: 1;
		unsigned bGpioINPin7: 1;
	};
} gpio_IN;

/* Union of GPIO_OUT register */
typedef union
{
	unsigned char regGpioOUT;
	struct
	{
		unsigned bGpioOUTPin0: 1;
		unsigned bGpioOUTPin1: 1;
		unsigned bGpioOUTPin2: 1;
		unsigned bGpioOUTPin3: 1;
		unsigned bGpioOUTPin4: 1;
		unsigned bGpioOUTPin5: 1;
		unsigned bGpioOUTPin6: 1;
		unsigned bGpioOUTPin7: 1;
	};
} gpio_OUT;

/* Union of GPIO_REN register */
typedef union
{
	unsigned char regGpioREN;
	struct
	{
		unsigned bGpioRENPin0: 1;
		unsigned bGpioRENPin1: 1;
		unsigned bGpioRENPin2: 1;
		unsigned bGpioRENPin3: 1;
		unsigned bGpioRENPin4: 1;
		unsigned bGpioRENPin5: 1;
		unsigned bGpioRENPin6: 1;
		unsigned bGpioRENPin7: 1;
	};
} gpio_REN;

/* Union of GPIO_IE register */
typedef union
{
	unsigned char regGpioIE;
	struct
	{
		unsigned bGpioIEPin0: 1;
		unsigned bGpioIEPin1: 1;
		unsigned bGpioIEPin2: 1;
		unsigned bGpioIEPin3: 1;
		unsigned bGpioIEPin4: 1;
		unsigned bGpioIEPin5: 1;
		unsigned bGpioIEPin6: 1;
		unsigned bGpioIEPin7: 1;
	};
} gpio_IE;

/* Union of GPIO_IES register */
typedef union
{
	unsigned char regGpioIES;
	struct
	{
		unsigned bGpioIESPin0: 1;
		unsigned bGpioIESPin1: 1;
		unsigned bGpioIESPin2: 1;
		unsigned bGpioIESPin3: 1;
		unsigned bGpioIESPin4: 1;
		unsigned bGpioIESPin5: 1;
		unsigned bGpioIESPin6: 1;
		unsigned bGpioIESPin7: 1;
	};
} gpio_IES;

/* Union of GPIO_IFG register */
typedef union
{
	unsigned char regGpioIFG;
	struct
	{
		unsigned bGpioIFGPin0: 1;
		unsigned bGpioIFGPin1: 1;
		unsigned bGpioIFGPin2: 1;
		unsigned bGpioIFGPin3: 1;
		unsigned bGpioIFGPin4: 1;
		unsigned bGpioIFGPin5: 1;
		unsigned bGpioIFGPin6: 1;
		unsigned bGpioIFGPin7: 1;
	};
} gpio_IFG;

/* Struct of GPIO registers */
typedef struct
{
	gpio_SEL 	*puGpioSEL;
	gpio_SEL2 	*puGpioSEL2;
	gpio_DIR 	*puGpioDIR;
	gpio_IN 	*puGpioIN;
	gpio_OUT 	*puGpioOUT;
	gpio_REN 	*puGpioREN;
	gpio_IE 	*puGpioIE;
	gpio_IES 	*puGpioIES;
	gpio_IFG	*puGpioIFG;
} gpio_Port;


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
extern volatile gpio_Port sGpioPort1, sGpioPort2;


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void gpioSetup(const unsigned int PORT_, const unsigned int PIN_, const unsigned int OUTPUT_);
void gpioIntSetup(const unsigned int PORT_, const unsigned int INPUT_, const unsigned int PULL_UP_, const unsigned int INT_PORT_);

/* Basic states */
void gpioHigh (const unsigned int PORT_, const unsigned char PIN_);
void gpioLow (const unsigned int PORT_, const unsigned char PIN_);
void gpioToggle (const unsigned int PORT_, const unsigned char PIN_);


/**************************************************************************************************
 *	END OF GPIO_1_3_1.h
 *************************************************************************************************/
#endif /* GPIO_1_3_1_H_ */

/*
 *	File			:	USCI_UART_1_2_1.h
 *	Date created	:	28/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.2.1
 *	Description		:	Construct USCI UART library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *						PROGRESS
 *		This is the version 1.2.1 of this library about USCI UART.
 *		In the version 1.0.1, functions operate with parameters as const unsigned char/int numbers.
 *		In the version 1.1.1, all const parameters, which are transfered into functions, are repla-
 *	ced by structs. In file source, we provide some structs that contain usual modes of configurat-
 *	ion, users just need to declare them by key-word "extern" in main.c file for taking these ones.
 *	Otherwise, people can also create new structs and transfer them into functions.
 *		This version is released at 05/06/2016. In this version, we reconstruct structs becoming a
 *	system of struct (struct inside struct). Thank to this feature, users don't need to pay attent-
 *	ion to what modes are availably supporting. When using functions, we think it will be well as -
 *	you make struct pointers pointing to "struct paths", then put them into functions.  A speacial 
 *	thing is that this version doesn't support for modes of baudrate, which are larger than 9600, -
 *	with SMCLK_8MHz, SMCLK_12MHz, SMCLK_16MHz.
 *		We recommend that if your purpose is variable, you should use version 1.0.1, and if you wa-
 *	nt to operate your chip in some specific modes, you should create structs and version 1.1.1 is
 *	the better choice for you. Yet, considering to version 1.2.1 as things mentioned above.
 *************************************************************************************************/
#ifndef USCI_UART_1_2_1_H_
#define USCI_UART_1_2_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Pins for USCI UART module */
#define		RXD						BIT1	// P1.1
#define		TXD						BIT2	// P1.2

/* Clock Source */
#define		CLKS_SMCLK_1MHZ			1
#define		CLKS_SMCLK_8MHZ			2
#define		CLKS_SMCLK_12MHZ		3
#define		CLKS_SMCLK_16MHZ		4

/* Baudrate */
#define		BAUD_9600				1
#define		BAUD_19200				2
#define		BAUD_38400				3
#define		BAUD_56000				4
#define		BAUD_115200				5
#define		BAUD_128000				6
#define		BAUD_256000				7

/* RXD Interrupt */
#define		INT_RXD_ON				UCA0RXIE
#define		INT_RXD_OFF				0

/* Struct for uartSetup function */
//-Struct mapping-//
//	uart_Setup _sStruct_:
//		uart_Clks sSmclk1Mhz/sSmclk8Mhz/sSmclk12Mhz/sSmclk16Mhz:
//			uart_Baud sBaud9600:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
//			uart_Baud sBaud19200:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
//			uart_Baud sBaud38400:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
//			uart_Baud sBaud56000:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
//			uart_Baud sBaud115200:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
//			uart_Baud sBaud128000:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
//			uart_Baud sBaud256000:
//				uart_Int_Rxd sIntRxdOn;
//				uart_Int_Rxd sIntRxdOff;
typedef struct
{
	const unsigned int CLKS_;		// Clock source
	const unsigned int BAUD_;		// Baudrate
	const unsigned int INT_RXD_;	// Turn on/off RXD interrupt
} uart_Int_Rxd;
typedef struct
{
	uart_Int_Rxd sIntRxdOn;
	uart_Int_Rxd sIntRxdOff;
} uart_Baud;
typedef struct
{
	uart_Baud sBaud9600;
	uart_Baud sBaud19200;
	uart_Baud sBaud38400;
	uart_Baud sBaud56000;
	uart_Baud sBaud115200;
	uart_Baud sBaud128000;
	uart_Baud sBaud256000;
} uart_Clks;
typedef struct
{
	uart_Clks sSmclk1Mhz;
	uart_Clks sSmclk8Mhz;
	uart_Clks sSmclk12Mhz;
	uart_Clks sSmclk16Mhz;
} uart_Setup;


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void uartSetup (const uart_Int_Rxd sUartSetup_);

/* TXD */
void txdChar (unsigned char varChar);
void txdStr (unsigned char *strString);
void txdToStr (unsigned char varChar);

/* RXD */
//-(vector = USCIAB0RX_VECTOR)-//
unsigned char rxdChar (void);
void rxdStr (unsigned char strRxd[]);


/**************************************************************************************************
 *	END OF USCI_UART_1_2_1.h
 *************************************************************************************************/
#endif /* USCI_UART_1_2_1_H_ */

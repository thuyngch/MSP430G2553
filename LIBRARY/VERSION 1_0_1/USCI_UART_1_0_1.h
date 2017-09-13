/*
 *	File			:	USCI_UART_1_0_1.h
 *	Date created	:	28/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct USCI UART library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about USCI UART.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
#ifndef USCI_UART_1_0_1_H_
#define USCI_UART_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Pins of Port1 */
#define		RXD						BIT1
#define		TXD						BIT2

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


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void
uartSetup 		(const uint16_t CLKS_, const uint16_t BAUD_, const uint16_t INT_RXD_);

/* TXD */
void
txdChar 		(uint8_t varChar);
void
txdStr 			(uint8_t *strString);
void
txdToStr 		(uint8_t varChar);

/* RXD */
//-(vector = USCIAB0RX_VECTOR)-//
uint8_t
rxdChar 		(void);
void
rxdStr 			(uint8_t strRxd[]);
void
rxdStrNLandCR	(uint8_t strRxd[]);


/**************************************************************************************************
 *	END OF USCI_UART_1_0_1.h
 *************************************************************************************************/
#endif /* USCI_UART_1_0_1_H_ */

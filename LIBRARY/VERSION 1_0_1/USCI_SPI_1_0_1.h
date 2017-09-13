/*
 * 	File			:	USCI_SPI_1_0_1.h
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct SPI library
 */

#ifndef USCI_SPI_1_0_1_H_
#define USCI_SPI_1_0_1_H_
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* SPIA0 pins */
#define		SPIA0_STE			BIT5				// P1.5
#define		SPIA0_SCLK			BIT4				// P1.4
#define		SPIA0_MISO			BIT1				// P1.1
#define		SPIA0_MOSI			BIT2				// P1.2

/* SPIB0 pins */
#define		SPIB0_STE			BIT4				// P1.4
#define		SPIB0_SCLK			BIT5				// P1.5
#define		SPIB0_MISO			BIT6				// P1.6
#define		SPIB0_MOSI			BIT7				// P1.7

/* SPI modes */
#define 	SPI_MODE_0			UCCKPH				// CPOL=0 CPHA=0
#define 	SPI_MODE_1			0					// CPOL=0 CPHA=1
#define 	SPI_MODE_2 			UCCKPL | UCCKPH		// CPOL=1 CPHA=0
#define 	SPI_MODE_3 			UCCKPL				// CPOL=1 CPHA=1

/* Master/Slave */
#define		SPI_MASTER			UCMST				// Master
#define		SPI_SLAVE			0					// Slave

/* SPIA0 Interrupts */
#define		INT_SPIA0_RX_ON		UCA0RXIE			// SPIA0_RX
#define		INT_SPIA0_RX_OFF	0
#define		INT_SPIA0_TX_ON		UCA0TXIE			// SPIA0_TX
#define		INT_SPIA0_TX_OFF	0

/* SPIB0 Interrupts */
#define		INT_SPIB0_RX_ON		UCB0RXIE			// SPIB0_RX
#define		INT_SPIB0_RX_OFF	0
#define		INT_SPIB0_TX_ON		UCB0TXIE			// SPIB0_TX
#define		INT_SPIB0_TX_OFF	0


/****************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 ***************************************************************************************/
/* Setup */
void spiA0Setup (const unsigned char SPI_, const unsigned int PRE_SCALER,
				const unsigned char INT_SPIA0_RX_, const unsigned char INT_SPIA0_TX_);
void spiB0Setup (const unsigned char SPI_, const unsigned int PRE_SCALER,
				const unsigned char INT_SPIB0_RX_, const unsigned char INT_SPIB0_TX_);

/* Master */
void spiA0MstWriteByte (unsigned char varData);
unsigned char spiA0MstReadByte (void);
void spiB0MstWriteByte (unsigned char varData);
unsigned char spiB0MstReadByte (void);


/****************************************************************************************
 *	END OF USCI_SPI_1_0_1.h
 ***************************************************************************************/
#endif /* USCI_SPI_1_0_1_H_ */

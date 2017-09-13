/*
 *	File			:	USCI_I2C_2_0_1.h
 *	Date created	:	10/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	2.0.1
 *	Description		:	Construct USCI I2C library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about USCI I2C.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
#ifndef USCI_I2C_2_0_1_H_
#define USCI_I2C_2_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Pins for USCI I2C module */
#define		SCL					BIT6	// P1.6
#define		SDA					BIT7	// P1.7

/* Master/Slave mode */
#define		I2C_MASTER			UCMST
#define		I2C_SLAVE			0

/* Usual addresses */
#define 	MPU6050_ADDRESS		0x68
#define 	DS1307_ADDRESS		0x68
#define 	LM92_ADDRESS		0x48

/* Interrupts */
#define		INT_I2C_RX_ON		UCB0RXIE	// Transmit
#define		INT_I2C_RX_OFF		0
#define		INT_I2C_TX_ON		UCB0TXIE	// Receive
#define		INT_I2C_TX_OFF		0
#define		INT_I2C_STT_ON		UCSTTIE		// Start
#define		INT_I2C_STT_OFF		0


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void i2cSetup				(const uint8_t I2C_, const uint8_t ADDR_OWN_,
								const unsigned int PRE_SCALER,
								const uint8_t INT_I2C_RX_, const uint8_t INT_I2C_TX_,
								const uint8_t INT_I2C_STT_);
void i2cSlvAddress			(const unsigned int ADDR_SLAVE_);

/* Master */
uint8_t i2cMstWriteByte		(uint8_t varData);
uint8_t i2cMstWriteArray	(uint8_t arrData[], int varLength);
uint8_t i2cMstReadByte		(uint8_t varInfo);
uint8_t i2cMstReadArray		(uint8_t varInfo, uint8_t arrData[], int varLength);

/* Slave */



/**************************************************************************************************
 *	END OF USCI_I2C_2_0_1.h
 *************************************************************************************************/
#endif /* USCI_I2C_2_0_1_H_ */

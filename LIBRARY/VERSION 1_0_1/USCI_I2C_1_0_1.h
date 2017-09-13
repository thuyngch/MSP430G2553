/*
 *	File			:	USCI_I2C_1_0_1.h
 *	Date created	:	10/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct USCI I2C library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about USCI I2C.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
#ifndef USCI_I2C_1_0_1_H_
#define USCI_I2C_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
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


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void i2cSetup(const unsigned int I2C_, const unsigned char ADDR_SLAVE_);
void i2cSlvAddress(const unsigned char ADDR_SLAVE_);

/* Master */
unsigned char i2cMstWriteByte(unsigned char varRegAddress, unsigned char varData);
unsigned char i2cMstWriteArray(unsigned char varRegAddress, unsigned char arrData[], int varLength);
unsigned char i2cMstReadByte(unsigned char varRegAddress);
unsigned char i2cMstReadArray(unsigned char varRegAddress, unsigned char arrData[], int varLength);


/**************************************************************************************************
 *	END OF USCI_I2C_1_0_1.h
 *************************************************************************************************/
#endif /* USCI_I2C_1_0_1_H_ */

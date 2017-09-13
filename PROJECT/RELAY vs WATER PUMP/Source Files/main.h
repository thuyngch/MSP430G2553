/*
 *	File			:	main.h
 *	Date created	:	11/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Header of source files
 *	Target object	:	MSP430G2553
 */
#ifndef MAIN_H_
#define MAIN_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>					// From producer
#include "VERSION 1_2_3/CLOCK_1_2_3.h"		// Struct inside struct
#include "VERSION 1_0_1/GPIO_1_0_1.h"		// Const parameters
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"	// Struct inside struct
#include "VERSION 2_0_1/USCI_I2C_2_0_1.h"	// Const parameters
#include "VERSION 1_2_3/TIMERA_1_2_3.h"		// Struct inside struct
#include "VERSION 1_0_1/FLASH_1_0_1.h"		// Normal


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define			FREQUENCY				1		// 1MHz

/* I2C communication */
#define			I2C_ADDR_SLAVE			0x48	// Address of slave
#define			I2C_PASSWORD			0xFF	// Password of communicatting frame
#define			I2C_NUM_BYTE			4		// these 4 bytes for data, one more byte for password

/* BCD */
#define			BCD_UNIT				0x000F	// 4 unit bits
#define			BCD_DECI				0x00F0	// 4 decimal bits
#define			BCD_HUND				0x0F00	// 4 hundred bits
#define			BCD_THOU				0xF000	// 4 thousand bits

/* I/O pins */
#define			IO_PORT1_PIN			0x39	// 0b 0011 1001
#define			IO_PORT2_PIN			0xFF	// 0b 1111 1111

/* Timer */
#define			PERIOD					62500	// 62500 * 8 = 500,000 count
#define			GAIN					2		// Use for PERIOD
#define			TIMERA0_OVF				0x0A

/* Flash */
#define			FLASH_POSITION_INIT		0		// Segment C


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
#ifndef USE_RELAY_WATER_PUMP

	unsigned char strBuff[10];						// Use for print into UART

	unsigned char varCountData;
	unsigned char varRx;
	unsigned char arrCommunication[I2C_NUM_BYTE];

	unsigned int regFirmPeriod;
	unsigned int regFirmDuty;

	unsigned int varCountTime;

#endif /* USE_RELAY_WATER_PUMP */


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Communication */
void communicationDecode     	(void);
void communicationConvertDCB	(unsigned int *pNumber);
void communicationTestRXData	(void);

/* Control */
void controlRelayOn  (unsigned char varPort1, unsigned char varPort2);
void controlRelayOff (unsigned char varPort1, unsigned char varPort2);


/**************************************************************************************************
 *	END OF main.h
 *************************************************************************************************/
#endif /* MAIN_H_ */

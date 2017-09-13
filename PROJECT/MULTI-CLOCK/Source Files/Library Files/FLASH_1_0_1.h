/*
 *	File			:	FLASH_1_0_1.h
 *	Date created	:	12/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct Flash Memory library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *************************************************************************************************/
#ifndef FLASH_1_0_1_H_
#define FLASH_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include "CLOCK_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Initial address */
#define			FLASH_ADDR_INIT_SEG_A		0x10C0
#define			FLASH_ADDR_INIT_SEG_B		0x1080
#define			FLASH_ADDR_INIT_SEG_C		0x1040
#define			FLASH_ADDR_INIT_SEG_D		0x1000

/* Ultimate address */
#define			FLASH_ADDR_ULTI_SEG_A		0x10FF
#define			FLASH_ADDR_ULTI_SEG_B		0x10BF
#define			FLASH_ADDR_ULTI_SEG_C		0x107F
#define			FLASH_ADDR_ULTI_SEG_D		0x103F

/* Length of segment */
#define			FLASH_SEG_LENGTH			64

/* Segment */
typedef enum
{
	segA,
	segB,
	segC,
	segD
} flash_Segment;


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void flashSetup (const unsigned int CLK_);

/* Read */
void flashReadByte  (flash_Segment seg_, unsigned char *pData, unsigned char varPosition);
void flashReadBlock (flash_Segment seg_, unsigned char arrData[], unsigned char varPosition,
						unsigned char varNumOfByte);

/* Write */
void flashWriteByte  (flash_Segment seg_, unsigned char varData, unsigned char varPosition);
void flashWriteBlock (flash_Segment seg_, unsigned char arrData[], unsigned char varPosition,
						unsigned char varNumOfByte);


/**************************************************************************************************
 *	END OF FLASH_1_0_1.h
 *************************************************************************************************/
#endif /* FLASH_1_0_1_H_ */

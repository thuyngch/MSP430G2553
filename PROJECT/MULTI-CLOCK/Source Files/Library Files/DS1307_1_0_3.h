/*
 *	File			:	DS1307_1_0_3.h
 *	Date created	:	23/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.3
 *	Description		:	Construct DS1307 library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *
 *
 *************************************************************************************************/
#ifndef DS1307_1_0_3_H_
#define DS1307_1_0_3_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include "USCI_UART_1_0_1.h"
#include "USCI_I2C_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* DS1307 address in I2C communication */
#define		DS1307_ADDRESS			0x68

//-------------------------------------------------------------------------------------------------
/* Number of data */
#define		DS1307_BYTE_OF_DATA		7

//-------------------------------------------------------------------------------------------------
/* Registers */
//-From 0x00 to 0x06 are RTC registers-//
#define		DS1307_SECONDS			0x00
#define		DS1307_MINUTES			0x01
#define		DS1307_HOURS			0x02
#define		DS1307_DAY				0x03
#define		DS1307_DATE				0x04
#define		DS1307_MONTH			0x05
#define		DS1307_YEAR				0x06
//-SQW/OUT (pin6) control register-//
#define		DS1307_CONTROL			0x07
//-From 0x08 to 0x3F are 56 RAM registers-//
#define		DS1307_RAM0				0x08
#define		DS1307_RAM1				0x09
#define		DS1307_RAM2				0x0A
#define		DS1307_RAM3				0x0B
#define		DS1307_RAM4				0x0C
#define		DS1307_RAM5				0x0D
#define		DS1307_RAM6				0x0E
#define		DS1307_RAM7				0x0F
#define		DS1307_RAM8				0x10
#define		DS1307_RAM9				0x11
#define		DS1307_RAM10			0x12
#define		DS1307_RAM11			0x13
#define		DS1307_RAM12			0x14
#define		DS1307_RAM13			0x15
#define		DS1307_RAM14			0x16
#define		DS1307_RAM15			0x17
#define		DS1307_RAM16			0x18
#define		DS1307_RAM17			0x19
#define		DS1307_RAM18			0x1A
#define		DS1307_RAM19			0x1B
#define		DS1307_RAM20			0x1C
#define		DS1307_RAM21			0x1D
#define		DS1307_RAM22			0x1E
#define		DS1307_RAM23			0x1F
#define		DS1307_RAM24			0x20
#define		DS1307_RAM25			0x21
#define		DS1307_RAM26			0x22
#define		DS1307_RAM27			0x23
#define		DS1307_RAM28			0x24
#define		DS1307_RAM29			0x25
#define		DS1307_RAM30			0x26
#define		DS1307_RAM31			0x27
#define		DS1307_RAM32			0x28
#define		DS1307_RAM33			0x29
#define		DS1307_RAM34			0x2A
#define		DS1307_RAM35			0x2B
#define		DS1307_RAM36			0x2C
#define		DS1307_RAM37			0x2D
#define		DS1307_RAM38			0x2E
#define		DS1307_RAM39			0x2F
#define		DS1307_RAM40			0x30
#define		DS1307_RAM41			0x31
#define		DS1307_RAM42			0x32
#define		DS1307_RAM43			0x33
#define		DS1307_RAM44			0x34
#define		DS1307_RAM45			0x35
#define		DS1307_RAM46			0x36
#define		DS1307_RAM47			0x37
#define		DS1307_RAM48			0x38
#define		DS1307_RAM49			0x39
#define		DS1307_RAM50			0x3A
#define		DS1307_RAM51			0x3B
#define		DS1307_RAM52			0x3C
#define		DS1307_RAM53			0x3D
#define		DS1307_RAM54			0x3E
#define		DS1307_RAM55			0x3F

//-------------------------------------------------------------------------------------------------
/* Struct of DS1307 time */
typedef struct
{
	unsigned char varSecond, varMinute, varHour;	// ss:mm:hh
	unsigned char varDay;							// Sunday,...,Saturday
	unsigned char varDate, varMonth, varYear;		// dd/MM/yy
} DS1307_Time;

volatile DS1307_Time sDS1307Time;


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* Setup */
void ds1307Setup(unsigned char varHr, unsigned char varMin, unsigned char varSec, // hh:mm:ss  (24h)
				 unsigned char varWd,											  // Week day	
				 unsigned char varD, unsigned char varMth, unsigned char varYr);  // dd/mm/yy
				 
/* Read RTC data */
void ds1307Read (void);
unsigned char ds1307BcdDec(unsigned char varNumber);
unsigned char ds1307DecBcd(unsigned char varNumber);

/* Print */
void ds1307Print(void);
void ds1307PrintDigit(int varDigit);


/**************************************************************************************************
 *	END OF DS1307_1_0_3.h
 *************************************************************************************************/
#endif /* DS1307_1_0_3_H_ */

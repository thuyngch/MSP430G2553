/*
 *	File			:	HEADER02_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	General Header file for the Second Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef HEADER02_0_0_101_H_
#define HEADER02_0_0_101_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Producing Library */
#include <msp430g2553.h>
#include "../HEADER_MUTUAL_0.0.101.h"

/* My Library */
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/WATCHDOG_1_0_1.h"
#include "VERSION 1_0_1/FLASH_1_0_1.h"

#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/MFRC522_1_0_1.h"
#include "VERSION 1_0_1/LCD_162_1_0_1.h"

#include "VERSION 1_0_1/USCI_SPI_1_0_1.h"
#include "VERSION 2_0_1/USCI_I2C_2_0_1.h"
#include "VERSION 1_0_1/USCI_UART_1_0_1.h"

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define	FREQUENCY						16		// 16MHz

//-------------------------------------------------------------------------------------------------
/* Hardware */
#define	PIN_RFID_SS						BIT0	// P1.0
#define	PIN_RFID_MISO					BIT1	// P1.1	(Fixed)
#define	PIN_RFID_MOSI					BIT2	// P1.2	(Fixed)
#define	PIN_RFID_RST					BIT3	// P1.3
#define	PIN_RFID_CLK					BIT4	// P1.4	(Fixed)
#define	PIN_LED_RFID					BIT5	// P1.5	(RED)
#define	PIN_I2C_SCL						BIT6	// P1.6	(Fixed)
#define	PIN_I2C_SDA						BIT7	// P1.7	(Fixed)

#define	PIN_LED_BTN						BIT0	// P2.0
#define	PIN_BTN_CLOSE					BIT1	// P2.1	(GREEN)
#define	PIN_LCD_RS						BIT2	// P2.2
#define	PIN_LCD_EN						BIT3	// P2.3
#define	PIN_LCD_D4						BIT4	// P2.4	(Fixed)
#define	PIN_LCD_D5						BIT5	// P2.5	(Fixed)
#define	PIN_LCD_D6						BIT6	// P2.6	(Fixed)
#define	PIN_LCD_D7						BIT7	// P2.7	(Fixed)

//-------------------------------------------------------------------------------------------------
/* GPIO */
#define	GPIO_PORT1_IN					(0)
#define	GPIO_PORT1_OUT					(PIN_LED_RFID)
#define	GPIO_PORT1_PIN					(GPIO_PORT1_IN | GPIO_PORT1_OUT)

#define	GPIO_PORT2_IN					(PIN_BTN_CLOSE)
#define	GPIO_PORT2_OUT					(PIN_LED_BTN)
#define	GPIO_PORT2_PIN					(GPIO_PORT2_IN | GPIO_PORT2_OUT)

#define	DL_ANTI_NOISE					50000	// Anti-Noise for button (50ms)

//-------------------------------------------------------------------------------------------------
/* Status Register */
typedef	struct
{
	unsigned bCommunication			:	2;
	unsigned bButtonNumOfDigit		:	3;
	unsigned bTouchPadData			:	1;
	bool	 bPasswordResult		:	1;
	unsigned bWifiSection			:	2;
	unsigned bLoadDataFromWifi		:	1;
	bool	 bHavePeople			:	1;
	bool	 bIsErrorCard			:	1;
	bool	 bIsCorrectCard			:	1;

//	unsigned bReserved12			:	1;
//	unsigned bReserved13			:	1;
//	unsigned bReserved14			:	1;
//	unsigned bReserved15			:	1;
} register_Status_02;

typedef enum
{
	eButtonNumOfDigit_0		= 0,
	eButtonNumOfDigit_1		= 1,
	eButtonNumOfDigit_2		= 2,
	eButtonNumOfDigit_3		= 3,
	eButtonNumOfDigit_4		= 4,
	eButtonNumOfDigit_5		= 5,
	eButtonNumOfDigit_6		= 6,
	eButtonNumOfDigit_7		= 7,
} button_Num_Of_Digit;

typedef	enum
{
	eTouchPadDataControl	= 0,
	eTouchPadDataNumber		= 1
} touchPad_Data;

typedef	enum
{
	eWifiSectionNone		= 0,
	eWifiSectionStart		= 1,
	eWifiSectionEnd			= 2,
	eWifiSectionReserved	= 3
} wifi_Section;


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Reader */
extern  uint8_t				varReaderStatus;
extern	int					varNoCurrent;
extern	int					varNoLast;
extern  uint8_t				arrReaderID[];
extern	person				sMember02[];
//-------------------------------------------------------------------------------------------------
/* Display */
extern	char				arrButtonRxData[];

//-------------------------------------------------------------------------------------------------
/* Status Register */
extern	register_Status_02		sRegisterStatus02;

//-------------------------------------------------------------------------------------------------
/* Communication */
extern	uint8_t					arrCmnBuff[];
extern	uint8_t					varI2C02Data;
extern	uint8_t					varNoBuff;
extern	uint8_t					strNameBuff[];
extern	uint8_t					arrIDBuff[];
extern	uint8_t					arrPasswordBuff[];
extern	uint8_t					varCountWifiData;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Firmware */
touchPad_Data
firmwareCheckTouchPadData 	(char varRxData);

//-------------------------------------------------------------------------------------------------
/* Data */
int8_t
data02CheckID 				(void);
bool
data02CheckPassword			(char varNo, char arrButtonRxData[]);
void
data02SaveAccount			(char varNo_);
void
data02LoadFromFlash			(void);
void
data02SaveToFlash			(void);

//-------------------------------------------------------------------------------------------------
/* Display */
void
displayTotal 				(char varNo, uint8_t varRxData);
void
displayName					(char varNo);
void
displayPassword				(void);
void
displayOverFlow				(void);
void
displayNull					(void);
void
displayError				(void);
void
displayClear				(void);
void
displayErrCard				(void);
void
displaySuccess				(char varNo);

//-------------------------------------------------------------------------------------------------
/* Communication */
void
cmn02Send					(uint16_t I2C_ADDR_, chip_LCD_RFID_Data eLCDSendTo_);
void
cmn02BtnDataClear			(void);
void
cmn02StrDecoder				(uint8_t* strData, uint8_t* pNo, uint8_t* strName, uint8_t arrID[],
																			uint8_t arrPassword[]);
void
cmn02ClearBuff				(uint8_t arrBuff[]);


/**************************************************************************************************
 *	END OF HEADER02_0.0.101.c
 *************************************************************************************************/
#endif /* HEADER02_0_0_101_H_ */

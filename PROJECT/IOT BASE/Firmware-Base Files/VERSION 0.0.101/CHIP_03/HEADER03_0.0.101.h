/*
 *	File			:	HEADER03_0.0.101.h
 *	Date created	:	29/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	General Header file for the Third Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef HEADER03_0_0_101_H_
#define HEADER03_0_0_101_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdint.h>

/* Producing Library */
#include <msp430g2553.h>

/* My Library */
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/WATCHDOG_1_0_1.h"

#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/TIMERA_1_0_1.h"
#include "VERSION 1_0_1/ESP8266_1_0_1.h"

#include "VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "VERSION 2_0_1/USCI_I2C_2_0_1.h"

/* This project */
#include "../HEADER_MUTUAL_0.0.101.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define	FREQUENCY					16		// 16MHz

//-------------------------------------------------------------------------------------------------
/* Hardware */
#define	PIN_WIFI_LED				BIT0	// P1.0
#define	PIN_WIFI_RXD				BIT1	// P1.1	(Fixed)
#define	PIN_WIFI_TXD				BIT2	// P1.2	(Fixed)
#define	PIN_WIFI_RST				BIT3	// P1.3
#define	PIN_WIFI_EN					BIT4	// P1.4
#define	PIN_RESERVED_01				BIT5	// P1.5
#define	PIN_I2C_SCL					BIT6	// P1.6	(Fixed)
#define	PIN_I2C_SDA					BIT7	// P1.7	(Fixed)

#define	PIN_SERVO_DIR				BIT0	// P2.0
#define	PIN_SERVO_PWM				BIT1	// P2.1	(Fixed)
#define	PIN_RESERVED_02				BIT2	// P2.2
#define	PIN_RESERVED_03				BIT3	// P2.3
#define	PIN_RESERVED_04				BIT4	// P2.4
#define	PIN_RESERVED_05				BIT5	// P2.5
#define	PIN_RESERVED_06				BIT6	// P2.6
#define	PIN_RESERVED_07				BIT7	// P2.7

//-------------------------------------------------------------------------------------------------
/* GPIO */
#define	GPIO_PORT1_INPUT			(0)
#define	GPIO_PORT1_OUTPUT			(PIN_WIFI_LED | PIN_WIFI_RST | PIN_WIFI_EN)
#define	GPIO_PORT1_PIN				(GPIO_PORT1_INPUT | GPIO_PORT1_OUTPUT)

#define	GPIO_PORT2_INPUT			(0)
#define	GPIO_PORT2_OUTPUT			(PIN_SERVO_DIR)
#define	GPIO_PORT2_PIN				(GPIO_PORT2_INPUT | GPIO_PORT2_OUTPUT)

//-------------------------------------------------------------------------------------------------
/* Status Register */
typedef struct
{
	unsigned bCommunication			: 2;	// Indicate which chip transaction in I2C network
	unsigned bIsWifiData			: 2;	// Indicate start/ending of data frame when USE_UART_WIFISHIELD
	unsigned bIsNullCharacter		: 1;	// Indicate '\0' in UART_RXD_ISR
	unsigned bEnoughDataFromWifi	: 1;	// Enough data from Wifi, so transfer it to LcdRfid chip

//	unsigned bReserved_06			: 1;
//	unsigned bReserved_07			: 1;
//	unsigned bReserved_08			: 1;
//	unsigned bReserved_09			: 1;
//	unsigned bReserved_10			: 1;
//	unsigned bReserved_11			: 1;
//	unsigned bReserved_12			: 1;
//	unsigned bReserved_13			: 1;
//	unsigned bReserved_14			: 1;
//	unsigned bReserved_15			: 1;
} register_Status_03;

typedef enum
{
	eIsWifiDataNone		= 0,	// None data frame from Wifi
	eIsWifiDataFalse	= 1,	// Starting of data frame from Wifi
	eIsWifiDataTrue		= 2,	// Ending of data frame from Wifi
	eIsWifiDataReserved	= 3
} is_Wifi_Data;


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Firmware */
extern	register_Status_03		sRegisterStatus03;

//-------------------------------------------------------------------------------------------------
/* Communication */
extern	uint8_t					varI2CData03;
extern	uint8_t					arrEachMember03[];

//-------------------------------------------------------------------------------------------------
/* Wifi */
extern	uint8_t					varUART03;
extern	uint16_t				varCountUARTData03;
extern	uint8_t					arrUARTBuff03[];


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Communication */
void
cmn03SendToRFID			(void);
void
cmn03MakeSampleFrame 	(void);

//-------------------------------------------------------------------------------------------------
/* Servo */
void
servo03Open				(void);
void
servo03Close			(void);

//-------------------------------------------------------------------------------------------------
/* Wifi */
bool
wifi03CheckATCmdComplete(const char* strCheck);
void
wifi03StartTimerCount	(uint16_t varTimeOut);
void
wifi03StopTimerCount	(void);
bool
wifi03FindStr			(const char *strSource, const char *strNeed);
void
wifi03ClearBuffer		(uint8_t arrBuff[], uint16_t varLength);


/**************************************************************************************************
 *	END OF HEADER03_0.0.101.h
 *************************************************************************************************/
#endif /* HEADER03_0_0_101_H_ */

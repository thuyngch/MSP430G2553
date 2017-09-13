/*
 *	File			:	HEADER00.c
 *	Date created	:	26/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef HEADER00_H_
#define HEADER00_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdint.h>
#include <stdbool.h>

/* Producing Library */
#include <msp430g2553.h>

/* My Library */
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/WATCHDOG_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/TIMERA_1_0_1.h"

#include "VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "VERSION 1_0_1/ESP8266_1_0_1.h"

/* This project */
#include "../HEADER_MUTUAL.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define	FREQUENCY					1		// 1 MHz

/* Hardware */
#define	PIN_LED_RED					BIT0	// P1.0
#define	PIN_WIFI_RXD				BIT1	// P1.1
#define	PIN_WIFI_TXD				BIT2	// P1.2
#define	PIN_WIFI_RST				BIT3	// P1.3
#define	PIN_WIFI_EN					BIT4	// P1.4
#define	PIN_P1_5					BIT5	// P1.5
#define	PIN_P1_6					BIT6	// P1.6
#define	PIN_P1_7					BIT7	// P1.7

#define	PIN_P2_0					BIT0	// P2.0
#define	PIN_P2_1					BIT1	// P2.1
#define	PIN_P2_2					BIT2	// P2.2
#define	PIN_P2_3					BIT3	// P2.3
#define	PIN_P2_4					BIT4	// P2.4
#define	PIN_P2_5					BIT5	// P2.5
#define	PIN_P2_6					BIT6	// P2.6
#define	PIN_P2_7					BIT7	// P2.7

/* Status Register */
typedef struct
{
	bool 		bIsNullCharacter			: 1;	// Indicate the null character '\0'
	bool		bIsEnoughWifiData			: 1;	// Indicate enough data received from Wifi
	unsigned 	bButton						: 4;	// Indicate which button is press (1-8)
	bool		bIsButtonTurnOn				: 1;	// Indicate whether button is turned on
} register_Status_00;


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Wifi */
extern	uint8_t						varUART00;
extern	uint16_t					varCountUART00;
extern	uint8_t						arrUART00[];

/* Firmware */
extern	register_Status_00			sRegisterStatus00;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Wifi */
bool
wifi00CheckATCmdComplete	(const char* strCheck);
void
wifi00StartTimerCount		(uint16_t varTimeOut);
void
wifi00StopTimerCount		(void);
bool
wifi00FindStr				(const char *strSource, const char *strNeed);
void
wifi00ClearBuffer			(uint8_t arrBuff[], uint16_t varLength);
char*
wifi00FindDataFromBuffer	(const char *strSource);

/* Firmware */
void
fw00DetectButton			(uint8_t* arrBuff);

/* Communication */
void
cmn00Send					(void);



/**************************************************************************************************
 *	END OF HEADER00.h
 *************************************************************************************************/
#endif /* HEADER00_H_ */

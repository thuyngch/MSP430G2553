/*
 *	File			:	HEADER01_0.0.101.h
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	General Header file for the First Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef HEADER01_0_0_101_H_
#define HEADER01_0_0_101_H_


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
#include "VERSION 1_0_1/CAPACITIVE_1_0_1.h"
#include "VERSION 1_0_1/TIMERA_1_0_1.h"

#include "VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "VERSION 2_0_1/USCI_I2C_2_0_1.h"

/* This project */
#include "../HEADER_MUTUAL_0.0.101.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define	FREQUENCY						16		// 16 MHz
/* Hardware */
#define	PIN_TOUCH_09					BIT0	// P1.0
#define	PIN_TOUCH_00					BIT1	// P1.1
#define	PIN_TOUCH_05					BIT2	// P1.2
#define	PIN_TOUCH_02					BIT3	// P1.3
#define	PIN_TOUCH_08					BIT4	// P1.4
#define	PIN_TOUCH_CLR					BIT5	// P1.5
#define	PIN_I2C_SDA						BIT6	// P1.6	(Fixed)
#define	PIN_I2C_SCL						BIT7	// P1.7	(Fixed)

#define	PIN_TOUCH_04					BIT0	// P2.0
#define	PIN_TOUCH_01					BIT1	// P2.1
#define	PIN_TOUCH_07					BIT2	// P2.2
#define	PIN_LED_TP						BIT3	// P2.3
#define	PIN_SPEAKER						BIT4	// P2.4
#define	PIN_TOUCH_CFM					BIT5	// P2.5
#define	PIN_TOUCH_03					BIT6	// P2.6
#define	PIN_TOUCH_06					BIT7	// P2.7

/* GPIO */
#define	GPIO_PORT1_IN					(0)
#define	GPIO_PORT1_OUT					(0)
#define	GPIO_PORT1_PIN					(GPIO_PORT1_IN | GPIO_PORT1_OUT)

#define	GPIO_PORT2_IN					(0)
#define	GPIO_PORT2_OUT					(PIN_LED_TP | PIN_SPEAKER)
#define	GPIO_PORT2_PIN					(GPIO_PORT2_IN | GPIO_PORT2_OUT)

/* TOUCHPAD */
#define	TOUCHPAD_PORT1_PIN				(PIN_TOUCH_01 | PIN_TOUCH_02 | PIN_TOUCH_03 | PIN_TOUCH_04)
#define	TOUCHPAD_PORT1_NUM				4

#define	TOUCHPAD_PORT2_PIN				(PIN_TOUCH_05 | PIN_TOUCH_06 | PIN_TOUCH_07 | PIN_TOUCH_08 | PIN_TOUCH_09 | PIN_TOUCH_00 | PIN_TOUCH_CFM | PIN_TOUCH_CLR)
#define	TOUCHPAD_PORT2_NUM				8

#define	TOUCHPAD_NUM					(TOUCHPAD_PORT1_NUM | TOUCHPAD_PORT2_NUM)
#define TOUCHPAD_THRESHOLD     			3000				// Threshold for a key press // total = 10,000; ID_3

/* WDT */
#define WDT_meas_setting 				WDT_MDLY_0_5	// SMCLK/512, interval for sensor measurements
#define WDT_delay_setting 				WDT_ADLY_16		// ACLK/512, interval for delay between measurement cycles

/* Status Register */
typedef struct
{
	unsigned bCommunication		: 2;	// Indicate which received data from

//	unsigned bReserved02		: 1;
//	unsigned bReserved03		: 1;
//	unsigned bReserved04		: 1;
//	unsigned bReserved05		: 1;
//	unsigned bReserved06		: 1;
//	unsigned bReserved07		: 1;
//	unsigned bReserved08		: 1;
//	unsigned bReserved09		: 1;
//	unsigned bReserved10		: 1;
//	unsigned bReserved11		: 1;
//	unsigned bReserved12		: 1;
//	unsigned bReserved13		: 1;
//	unsigned bReserved14		: 1;
//	unsigned bReserved15		: 1;
} register_Status_01;

typedef enum
{
	eTouchPadBtn0			= 0,
	eTouchPadBtn1			= 1,
	eTouchPadBtn2			= 2,
	eTouchPadBtn3			= 3,
	eTouchPadBtn4			= 4,
	eTouchPadBtn5			= 5,
	eTouchPadBtn6			= 6,
	eTouchPadBtn7			= 7,
	eTouchPadBtn8			= 8,
	eTouchPadBtn9			= 9,
	eTouchPadBtnCfm			= 10,
	eTouchPadBtnClr			= 11,
	eTouchPadBtnReserved0	= 12,
	eTouchPadBtnReserved1	= 13,
	eTouchPadBtnReserved2	= 14,
	eTouchPadBtnReserved3	= 15
} touchPad_Btn;


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Status Register */
extern	register_Status_01	sRegisterStatus01;

/* Touchpad */
extern	uint16_t			arrBaseCount[TOUCHPAD_NUM];
extern 	uint16_t 			arrMeasCount[TOUCHPAD_NUM];
extern 	int16_t 			arrDeltaCount[TOUCHPAD_NUM];
extern 	uint8_t 			arrKeyPress[TOUCHPAD_NUM];
extern 	int8_t 				varKeyPress;
extern 	int16_t 			varCycles;

/* Communication */
extern	uint8_t				varI2CData01;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* TouchPad */
void
touchPadDetectBtn	(void);

/* Communication */
void
cmn01Send			(const uint16_t I2C_ADDR_, const chip_TouchPad_Data eTouchPadSendTolCD_);

/* Speaker */
void
speaker01Play		(void);
void
speaker01On			(void);
void
speaker01Off		(void);

/* Firmware */
chip_TouchPad_Data
fmwr01GetCmnData	(void);


/**************************************************************************************************
 *	END OF HEADER01_0.0.101.h
 *************************************************************************************************/
#endif /* HEADER01_0_0_101_H_ */

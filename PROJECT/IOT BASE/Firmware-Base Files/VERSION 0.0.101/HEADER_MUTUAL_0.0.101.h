/*
 *	File			:	HEADER_MUTUAL_0.0.101.h
 *	Date created	:	28/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	General Header file for all Chips
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef HEADER_MUTUAL_0_0_101_H_
#define HEADER_MUTUAL_0_0_101_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */

/* Producing Library */

/* My Library */

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* COMMUNICATION_I2C */
#define	I2C_ADDR_WIFI_SERVO				0x7F	// Address of chip with Wifi, Servo
#define	I2C_ADDR_LCD_RFID				0x7E	// Address of chip with LCD, RFID
#define	I2C_ADDR_TOUCHPAD				0x7D	// Address of chip with TouchPad

#define	I2C_HEADER_WIFI_SERVO			0xFF	// Header of chip with Wifi, Servo
#define	I2C_HEADER_LCD_RFID				0xFE	// Header of chip with LCD, RFID
#define	I2C_HEADER_TOUCHPAD				0xFD	// Header of chip with TouchPad

#define	I2C_ENDING						0xFC	// End of Trasaction

#define	I2C_NUM_BYTE_OF_FRAME			40

//-------------------------------------------------------------------------------------------------
/* Data */
#define	DATA_NUM_MEMBER					5		// 5 members are saved in flash

#define	DATA_MEM_BYTE					20		// 20 bytes for one person
#define	DATA_SEG_C_BYTE					60		// 60 bytes/segC
#define	DATA_SEG_D_BYTE					40		// 40 bytes/segD

#define	DATA_SEG_C_OFF_0				0		// Offset position of Member0
#define	DATA_SEG_C_OFF_1				20		// Offset position of Member1
#define	DATA_SEG_C_OFF_2				40		// Offset position of Member2

#define	DATA_SEG_D_OFF_3				0		// Offset position of Member3
#define	DATA_SEG_D_OFF_4				20		// Offset position of Member4

//-------------------------------------------------------------------------------------------------
/* TouchPad Chip's Data */
typedef	enum
{
	eTouchPadSendTolCD_Button_0 		= '0',
	eTouchPadSendTolCD_Button_1 		= '1',
	eTouchPadSendToLCD_Button_2 		= '2',
	eTouchPadSendToLCD_Button_3 		= '3',
	eTouchPadSendTolCD_Button_4 		= '4',
	eTouchPadSendTolCD_Button_5 		= '5',
	eTouchPadSendTolCD_Button_6 		= '6',
	eTouchPadSendTolCD_Button_7 		= '7',
	eTouchPadSendTolCD_Button_8 		= '8',
	eTouchPadSendTolCD_Button_9 		= '9',
	eTouchPadSendTolCD_Button_Confirm 	= ':',
	eTouchPadSendTolCD_Button_Clear		= ';'
} chip_TouchPad_Data;

//-------------------------------------------------------------------------------------------------
/* LCD_RFID Chip's Data */
typedef	enum
{
	eLCDSendToServo_Close		= '0',
	eLCDSendToServo_Open		= '1',
	eLCDSendToTouchPad_Warning	= '2'
} chip_LCD_RFID_Data;

//-------------------------------------------------------------------------------------------------
/* Communication chip */
typedef	enum
{
	eCommunicationNone 		= 0,
	eCommunicationTouchPad	= 1,
	eCommunicationLcdRfid	= 2,
	eCommunicationWifiServo = 3
} communication;

//-------------------------------------------------------------------------------------------------
/* Load data from Wifi */
typedef	enum
{
	eLoadDataFromWifiFalse	= 0,
	eLoadDataFromWifiTrue	= 1
} load_Data_From_Wifi;

//-------------------------------------------------------------------------------------------------
/* Person struct */
typedef	struct
{
	char		varNo;
	char 		strName[10];
	char		arrID[5];
	char		arrPassword[4];
} person;


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	END OF HEADER_MUTUAL_0.0.101.h
 *************************************************************************************************/
#endif /* HEADER_MUTUAL_0_0_101_H_ */

/*
 *	File			:	HEADER_0_0_101.h
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.101
 *	Description		:	Header of Multi-Clock
 */
#ifndef HEADER_0_0_101_H_
#define HEADER_0_0_101_H_
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdint.h>
#include <stdbool.h>

/* Producing Library */
#include <msp430g2553.h>

/* My Library */
#include "../Library Files/CLOCK_1_0_1.h"
#include "../Library Files/WATCHDOG_1_0_1.h"
#include "../Library Files/GPIO_1_0_1.h"
#include "../Library Files/IC74HC595_1_0_1.h"
#include "../Library Files/FLASH_1_0_1.h"
#include "../Library Files/TIMERA_1_0_1.h"
#include "../Library Files/USCI_I2C_1_0_1.h"
#include "../Library Files/DS1307_1_0_3.h"
#include "../Library Files/USCI_UART_1_0_1.h"

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Module */
#define		MODULE_BUTTON			0
#define		MODULE_DATA				1
#define		MODULE_DISPLAY			2
#define		MODULE_FIRMWARE			3
#define		MODULE_POWER			4
#define		MODULE_SPEAKER			5
#define		MODULE_TIMER			6

//-------------------------------------------------------------------------------------------------
/* Component */
#define		COMPONENT_BTN_UP		0
#define		COMPONENT_BTN_DOWN		1
#define		COMPONENT_BTN_CONFIRM	2
#define		COMPONENT_BTN_EN_TIME	3
#define		COMPONENT_BTN_EN_ALARM	4
#define		COMPONENT_BTN_EN_FOCUS	5


//-------------------------------------------------------------------------------------------------
/* Frequency */
#define		FREQUENCY				1		// 1MHz

//-------------------------------------------------------------------------------------------------
/* Hardware */
#define		PIN_4017				BIT0	// P1.0
#define		PIN_READ_4017			BIT1	// P1.1

#define		PIN_UART_TXD			BIT2	// P1.2
#define		PIN_SPEAKER				BIT2	// P1.2

#define		PIN_595_DATA			BIT3	// P1.3
#define		PIN_595_CLK				BIT4	// P1.4
#define		PIN_595_LATCH			BIT5	// P1.5

#define		PIN_DS1307_SCL			BIT6	// P1.6
#define		PIN_DS1307_SDA			BIT7	// P1.7

#define		PIN_LED_ALARM			BIT0	// P2.0
#define		PIN_LED_FOCUS			BIT1	// P2.1

#define		PIN_BTN_UP				BIT2	// P2.2
#define		PIN_BTN_DOWN			BIT3	// P2.3
#define		PIN_BTN_CONFIRM			BIT4	// P2.4

#define		PIN_BTN_EN_TIME			BIT5	// P2.5
#define		PIN_BTN_EN_ALARM		BIT6	// P2.6
#define		PIN_BTN_EN_FOCUS		BIT7	// P2.7

#define		PIN_GPIO_OUT_PORT1		(PIN_4017 + PIN_SPEAKER + PIN_595_CLK + PIN_595_DATA + PIN_595_LATCH)
#define		PIN_GPIO_IN_PORT1		(PIN_READ_4017)
#define		PIN_GPIO_PORT1			(PIN_GPIO_OUT_PORT1 | PIN_READ_4017)

#define		PIN_GPIO_OUT_PORT2		(PIN_LED_ALARM + PIN_LED_FOCUS)
#define		PIN_GPIO_IN_PORT2		(PIN_BTN_UP + PIN_BTN_DOWN + PIN_BTN_CONFIRM + PIN_BTN_EN_TIME + PIN_BTN_EN_ALARM + PIN_BTN_EN_FOCUS)
#define		PIN_GPIO_PORT2			(PIN_GPIO_OUT_PORT2 + PIN_GPIO_IN_PORT2)

//-------------------------------------------------------------------------------------------------
/* Flash */
#define		FLASH_SEGMENT			segC

#define		FLASH_ALARM_POSITION	0
#define		FLASH_ALARM_NUM_BYTE	2

#define		FLASH_FOCUS_POSITION	2
#define		FLASH_FOCUS_NUM_BYTE	1

//-------------------------------------------------------------------------------------------------
/* Delay */
#define		DL_ANTI_NOISE			50000	// 50ms

//-------------------------------------------------------------------------------------------------
/* Speaker */
#define 	SPEAKER_ALARM			0
#define 	SPEAKER_FOCUS			1

//-------------------------------------------------------------------------------------------------
/* TimerA0 */
#define		TIMERA0_PERIOD			62500	// 62500 * 8 = 500,000 count = 500ms
#define		TIMERA1_PERIOD			62500	// 62500 * 8 = 500,000 count = 500ms
#define		TIMERA0_OVF				0x0A
#define		TIMERA1_OVF				0x0A

//-------------------------------------------------------------------------------------------------
/* Type of Status register */
typedef union
{
//	unsigned int regStatus;
	struct
	{
		unsigned bPage		: 2;	// Mode of Multi-Clock
		unsigned bComponent	: 2;	// Component of page (hour, minute, second)
		unsigned bControl	: 2;	// Control button (Up, Down, Confirm)
		unsigned bIdle		: 1;	// Indicate Idle mode
		unsigned bSpkAlarm	: 1;	// Priority of Alarm > Focus in speaker
		unsigned bEnAlarm	: 1;	// Enable Alarm
		unsigned bEnFocus	: 1;	// Enable Focus

//		unsigned bReserved9: 1;
//		unsigned bReserved10: 1;
//		unsigned bReserved11: 1;
//		unsigned bReserved12: 1;
//		unsigned bReserved13: 1;
//		unsigned bReserved14: 1;
//		unsigned bReserved15: 1;
	};
} status_Register;

typedef enum						// Page of Multi-Clock enum
{
	ePageNormal = 0,
	ePageTime = 1,
	ePageAlarm = 2,
	ePageFocus = 3
} status_Page;

typedef enum						// Component of page
{
	eComponentHour = 0,
	eComponentMinute = 1,
	eComponentSecond = 2,
	eComponentReserved = 3
} status_Component;

typedef enum						// Control button
{
	eControlNone = 0,
	eControlUp = 1,
	eControlDown = 2,
	eControlConfirm = 3,
} status_Control;

//-------------------------------------------------------------------------------------------------
/* Type of System Time struct */
typedef struct
{
	char varHour;		// 0~23
	char varMinute;		// 0~59
	char varSecond;		// 0~59
} system_Time;

//-------------------------------------------------------------------------------------------------
/* Type of Alarm Time struct */
typedef struct
{
	char varHour;		// 0~23
	char varMinute;		// 0~59
} alarm_Time;

//-------------------------------------------------------------------------------------------------
/* Type of Focus Time struct */
typedef struct
{
	char varInterval;	// 1~99
	char varHour;		// 0~23
	char varMinute;		// 0~59
} focus_Time;


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Status register */
extern volatile 	status_Register 	sStatusRegister;

/* Time */
extern volatile 	system_Time 		sTime;
extern volatile 	system_Time 		sTimeSet;
extern volatile 	alarm_Time	 		sAlarm;
extern volatile 	focus_Time	 		sFocus;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* BasicOperation */
uint16_t
setBits8 				(unsigned char reg_, unsigned int varBits);
uint16_t
clearBits8	 			(unsigned char reg_, unsigned int varBits);
uint16_t
setBits16 				(unsigned int reg_, unsigned int varBits);
uint16_t
clearBits16 			(unsigned int reg_, unsigned int varBits);
void
uintToByte				(unsigned int varInt, unsigned char *pMSB, unsigned char *pLSB);
uint16_t
byteToUint				(unsigned char varMSB, unsigned char varLSB);
void
digitDivide				(unsigned char varNumber, unsigned char *pTenthDigit, unsigned char *pUnitDigit);
void
testUart				(unsigned char MODULE_, unsigned char COMPONENT_);

/* Button */
void
buttonIdentify			(void);

/* Data */
void
dataLoad 				(status_Page ePage_);
void
dataSave 				(status_Page ePage_);

/* Display */
void
displayHour				(unsigned char varNumber);
void
displayMinute			(unsigned char varNumber);
void
displaySecond			(unsigned char varNumber);
void
display4017Calib		(void);

/* Firmware (Base of system) */
void
firmPageNormalDisplay 	(void);
void
firmPageTime 			(void);
void
firmPageAlarm			(void);
void
firmPageFocus			(void);
void
firmPageTimeDisplay		(void);
void
firmPageAlarmDisplay	(void);
void
firmPageFocusDisplay	(void);

/* Power */

/* Speaker */
void
speakerTurnOn			(void);
void
speakerTurnOff			(void);
void
speakerPlay				(unsigned int SPEAKER_);

/* Timer */
void
timerGetCurrent			(void);
void
timerAlarm				(char varHr, char varMin, char varSec);
void
timerFocus				(char varInterval);


/**************************************************************************************************
 *	END OF HEADER_0_0_101.h
 *************************************************************************************************/
#endif /* HEADER_0_0_101_H_ */

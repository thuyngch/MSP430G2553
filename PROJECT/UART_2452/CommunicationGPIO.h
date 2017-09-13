/*
 * 	File			:	CommunicationGPIO.h
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	23/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.3
 *	Description		:	Generate Communication module by GPIO
 */

/****************************************************************************************
 *										PROGRESS
 *									   ----------
 *		In version 1.0, this file had two functions for sending data, meanwhile, there is
 *	no function for getting data. However, I construct a segment in while loop in main
 *	function to do this shortcoming.
 *		In version 1.1, I moved the segment mentioned in version 1.0 into a port interrupt.
 *		In version 1.2, I expanded a new module MOSI, communicating between Master chip
 *	and Slave chips. We will agree to call Communication module having 3 sub
 *	modules: TXD, RXD, and MOSI.
 *		In version 1.3, I integrated a security mode to protect MOSI module when an unreal
 *	Master chip try to connect with Slave chip.
 ***************************************************************************************/

/****************************************************************************************
 *										PIN MAP
 *									   ---------
 *									P1.0		LED_RED
 *									P1.1		TXD
 *									P1.2		RXD
 *									P1.4		MOSI
 *									P1.5		MISO
 ***************************************************************************************/
#ifndef COMMUNICATIONGPIO_H_
#define COMMUNICATIONGPIO_H_

#include <msp430.h>
/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* Pin and bit */
#define		LED_RED			BIT0		//This pin for a red LED
#define		TXD				BIT1		//TXD pin
#define		TXD_TRANS		1			//TXD transition bit
#define		RXD				BIT2		//RXD pin
#define		RXD_TRANS		2			//RXD transition bit
#define		MOSI			BIT4		//MOSI pin
#define		MOSI_TRANS		4			//MOSI transition bit
#define		MISO			BIT5		//MISO pin
#define		MISO_TRANS		5			//MISO transition bit

/* Delay in communication module */
#define		BAUDRATE_TXD	104			//104us
#define		BAUDRATE_RXD	104			//104us
#define		BAUDRATE_MOSI	90			//90us
#define		BAUDRATE_MISO	90			//90us
#define		BAUD_LAG_PUT	40			//40us (used for lagging in for loop)
#define		BAUD_LAG_GET	10			//10us (used for lagging in start bit at ISR)
#define		DELAY_MS		90			//90us between 2 bytes of MS communication

/* Address and pasword in SIMO module */
#define		ADDR_BIT		0XC0		//BIT6+BIT7
#define		ADDRESS1		0X00		//0B00.000000
#define		ADDRESS2		0X40		//0B01.000000
#define		ADDRESS3		0X80		//0B10.000000
#define		ADDRESS4		0XC0		//0B11.000000
#define		PASS_BIT		0X3F		//BIT0+BIT1+BIT2+BIT3+BIT4+BIT5
#define		PASSWORD1		0X2A		//0B00.101010
#define		PASSWORD2		0X2C		//0B00.101100
#define		PASSWORD3		0X39		//0B00.111001
#define		PASSWORD4		0X0E		//0B00.001110
#define		SECURITY_ON		0XFF		//Turn on sercurity mdoe
#define		SECURITY_OFF	0X00		//Turn off sercurity mdoe

/****************************************************************************************
 *	FUNCTION PROTOTYPEs
 ***************************************************************************************/
/* LED mode configuration */
void ledOn (void);
void ledOff (void);
void ledToogle (void);

/* Get data (every 8 bits) from Buff memory (16 bits) */
void arrayPushLow (int arrSource[], int arrDestination[]);
void arrayPushHigh (int arrSource[], int arrDestination[]);

/* Convert 8 integer array's elements to a unsigned char variable */
unsigned char power (unsigned char varBase, unsigned char varExponential);
unsigned char characterConvert (int arrArray[]);

/* Choose the type of chip (Master/Slave) and its address, password */
void selectPosition(const unsigned char ADDRESS, const unsigned char PASSWORD, unsigned char *varAddress, unsigned char *varPassword);
void masterSetup(const unsigned char ADDRESS, const unsigned char PASSWORD, const unsigned char SECURITY, unsigned char *varSecurity);
void slaveSetup (const unsigned char ADDRESS, const unsigned char PASSWORD, const unsigned char SECURITY, unsigned char *varSecurity);

/* TXD and RXD module */
void txdChar (unsigned char varData);
void txdStr (unsigned char *strData);
void rxd (int arrBuff[]);

/* Respond of Master/Slave when get data from the other one */
void masterRespond (unsigned char varCharacter);
void slaveRespond (unsigned char varCharacter);

/* Communicate between Master and Slave through MOSI and MISO module */
void masterPut (unsigned char varByte1, unsigned char varByte2);
void masterGet (int arrBuff[]);
void slavePut (unsigned char varByte1, unsigned char varByte2);
void slaveGet (int arrBuff[]);

/* Check address and password and data through MOSI and MISO module */
void masterCheck (int arrBuff[], int arrData[], unsigned char varSecurity, unsigned char *varCharacter, int *varWrongtime);
void slaveCheck (int arrBuff[], int arrData[], unsigned char varSecurity, unsigned char *varCharacter, int *varWrongtime);

/* Speacial mode to protect chip when there is an unreal chip try to key password */
void lockSecurity (int varWrongTimes);


/****************************************************************************************
 *	END OF CommunicationGPIO.h
 ***************************************************************************************/
#endif /* COMMUNICATIONGPIO_H_ */

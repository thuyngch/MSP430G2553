/*
 *	File			:	main.c
 *	Date created	:	11/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Communicate with MPU6050 through I2C and MSP430G2553 through SPI
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>					// From producer
#include <math.h>							// Standard C lib
#include "VERSION 1_2_3/CLOCK_1_2_3.h"		// Struct inside struct, without extern decare
#include "VERSION 1_0_1/GPIO_1_0_1.h"		// Const parameter
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"	// Testing
#include "VERSION 1_0_1/USCI_SPI_1_0_1.h"	// Const parameter
#include "VERSION 1_0_1/USCI_I2C_1_0_1.h"	// Const parameter
#include "VERSION 1_0_1/MPU6050_1_0_1.h"	// Normal


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define		FREQUENCY				16			// 16MHz

/* Delay intervals */
#define		MPU6050_PREPARING		50			// 1s
#define		SAFE_DELAY				2000		// 1ms


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
unsigned char varTx;		// Used to transmit to slave chip
unsigned char strBuff[7];	// Testing


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:	dataEncode
 *	Purpose	:	Encode data package for transmitting
 * 	Input	:	None
 * 	Output	:	Value of encoded data
 */
unsigned char dataEncode (void)
{
	//unsigned int varAngle;
	unsigned char varData;
//	varAngle = (unsigned int)(-ACCEL_ZOUT - 7698);	// 7698 corresponds with 70 degrees,
													// 8192 corresponds with 90 degrees
//	if(varAngle >= 494)
//	{
//		varAngle = 90;
//	}
//	else if(varAngle >= 492)
//	{
//		varAngle = 89;
//	}
//	else if(varAngle >= 487)
//	{
//		varAngle = 88;
//	}
//	else if(varAngle >= 479)
//	{
//		varAngle = 87;
//	}
//	else if(varAngle >= 469)
//	{
//		varAngle = 86;
//	}
//	else if(varAngle >= 444)
//	{
//		varAngle = (unsigned int)((2*varAngle + 1212) / 25);
//	}
//	else if(varAngle >= 382)
//	{
//		varAngle = (unsigned int)((3*varAngle + 3876) / 62);
//	}
//	else if(varAngle >= 275)
//	{
//		varAngle = (unsigned int)((4*varAngle + 7139) / 107);
//	}
//	else
//	{
//		varAngle = (unsigned int)((7*varAngle + 19250) / 275);
//	}
//	varData = (unsigned char)(varAngle);
	varData = (unsigned char)((float)(-ACCEL_ZOUT) / 1420 * 90);
	if(varData > 90)
	{
		varData = 90;
	}
	if(ACCEL_XOUT > 0)
	{
		varData |= 0x80;	// Direction value (Highest bit)
							// 0 for reverse, 1 for forward
	}
	return varData;
}


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-CLK & WDT-//
	clkSetup(sClkSetup.sDco16mhz.sSwdtOn);		// DCO = 16MHz, Stop Watchdog timer

	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);			// Just use LED_RED for notification

	//-SPI-//
	spiA0Setup(SPI_MASTER, 4, INT_SPIA0_RX_OFF, INT_SPIA0_TX_OFF);	// SPIA0 rate = 4MHz, 3-pin mode

	//-I2C-//
	i2cSetup(I2C_MASTER, MPU6050_ADDRESS);		// MSP430G2553 as Master I2C

	//-UART TESTING-//
//	uartSetup(sUartSetup.sSmclk16Mhz.sBaud9600.sIntRxdOff);

	//-MPU6050-//
	mpu6050Setup();											// +-4g mode, 500 degrees/s
	__delay_cycles(MPU6050_PREPARING * FREQUENCY);			// Wait 1 second for preparing
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		ledToggle(LED_RED);						// Notify operation
		mpu6050GetAccelValue();					// Get value from MPU6050
		varTx = dataEncode();					// Process data
		spiA0MstWriteByte(varTx);				// Transmit data
		__delay_cycles(2000 * FREQUENCY);		// Ensure no overlap in communication
		__delay_cycles(2000 * FREQUENCY);		// Ensure no overlap in communication
		__delay_cycles(2000 * FREQUENCY);		// Ensure no overlap in communication
		__delay_cycles(2000 * FREQUENCY);		// Ensure no overlap in communication

		//-Testing-//
//		sprintf((char*)strBuff, "%d", (varTx >> 7));
//		txdStr(strBuff);
//		txdChar(13);txdChar(13);
//		sprintf((char*)strBuff, "%d", (varTx & 0x7F));
//		txdStr(strBuff);
//		txdChar(10);

//		sprintf((char*)strBuff, "%d", (-ACCEL_ZOUT));
//		txdStr(strBuff);
//		txdChar(ENTER);

//		mpu6050PrintAccelValue();
	}
}


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

/*
 *	File			:	main.c
 *	Date created	:	04/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Communicate with MMA8452
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430g2553.h>					// From producer
#include "VERSION 1_2_3/CLOCK_1_2_3.h"		// Struct inside struct
#include "VERSION 1_0_1/GPIO_1_0_1.h"		// Const parameter
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"	// Struct inside struct
#include "VERSION 1_0_1/USCI_I2C_1_0_1.h"	// Const parameter
#include "VERSION 1_0_1/USCI_SPI_1_0_1.h"	// Const parameter
#include "VERSION 1_0_1/MMA8452_1_0_1.h"	// Normal


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Frequency */
#define		FREQUENCY				16			// 16MHz

/* Delay interval */
#define		MMA8452_PREPARING		1000			// 50us


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
unsigned char strBuff[10];


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-CLK & WDT-//
	clkSetup(sClkSetup.sDco16mhz.sSwdtOn);	// DCO = 16MHz, Stop Watchdog timer

	//-GPIO-//
	gpioSetup(PORT1, LED_RED, LED_RED);	// Just use LED_RED for notification

	//-SPI-//
//	spiA0Setup(SPI_MASTER, 4, INT_SPIA0_RX_OFF, INT_SPIA0_TX_OFF);	// SPIA0 rate = 4MHz, 3-pin mode

	//-I2C-//
	i2cSetup(I2C_MASTER, );	// MSP430G2553 as Master I2C

	//-UART TESTING-//
	uartSetup(sUartSetup.sSmclk16Mhz.sBaud9600.sIntRxdOff);

	//-MMA8452-//
	mma8452Setup(MMA8452_SCALE_2, MMA8452_ODR_800HZ, 0x80, 0x80, 0x08);	// Disable x-y, z: 0.5g threshold
	__delay_cycles(MMA8452_PREPARING * FREQUENCY);						// Wait 50us for preparing
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		if(mma8452DataAvailable() == MMA8452_STATE_DATA_AVAILABLE)
		{
			ledToggle(LED_RED);
			mma8452GetAccelValue();
			sprintf((char*)strBuff, "%d", sMma8452AccelValue.varZ_Uint);
			txdStr(strBuff);
			txdChar(ENTER);
		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

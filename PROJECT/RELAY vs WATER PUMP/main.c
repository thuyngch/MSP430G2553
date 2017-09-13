/*
 *	File			:	main.c
 *	Date created	:	11/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Control Relay & Water pump
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "Source Files/main.h"


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-CLK & WDT-//
	clkSetup(sClkSetup.sDco1mhz.sSwdtOn);	// DCO = 1MHz, Stop watchdog timer

	//-GPIO-//
	gpioSetup(PORT1, IO_PORT1_PIN, IO_PORT1_PIN);	// I/O pins for relay
	gpioSetup(PORT2, IO_PORT2_PIN, IO_PORT2_PIN);	// I/O pins for relay

	//-UART-//
	uartSetup(sUartSetup.sSmclk1Mhz.sBaud9600.sIntRxdOff);
	txdStr("Complete\n");

	//-I2C-//
	i2cSetup(I2C_SLAVE, I2C_ADDR_SLAVE, 10, INT_I2C_RX_ON, INT_I2C_TX_OFF, INT_I2C_STT_OFF);
	varCountData = 0;

	//-TIMER-//
	timerASetup(sTimerASetup.sTimerA0Setup.sTimerModeUp.sTimerDiv8.sTimerIntOvfOn, 0 , PERIOD);

	//-FLASH-//
	flashSetup(CLK_DCO_1MHZ);
	flashReadBlock(segC, arrCommunication, FLASH_POSITION_INIT, I2C_NUM_BYTE);
	communicationDecode();
	communicationConvertDCB(&regFirmPeriod);
	communicationConvertDCB(&regFirmDuty);
//-------------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
		communicationTestRXData();
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* TX */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR (void)
{
	varRx = UCB0RXBUF;
	if((varCountData > 0) && (varCountData < 5))
	{
		arrCommunication[varCountData-1] = varRx;	// Get data
		varCountData++;								// Increase num-byte ordinal
	}
	if(varRx == I2C_PASSWORD)						// If matching the password
	{
		varCountData = 1;							// Start get data
	}
	if(varCountData == 5)							// If enough data
	{
		communicationDecode();						// Decode 4 byte to 2 unsigned int
		communicationConvertDCB(&regFirmPeriod);	// Convert BCD to DCB for Period
		communicationConvertDCB(&regFirmDuty);		// Convert BCD to DCB for Duty
		varCountData++;

		flashWriteBlock(segC, arrCommunication, FLASH_POSITION_INIT, I2C_NUM_BYTE);	// Save into flash

		varCountTime = 0;							// Reset
		TA0R         = 0;							// Reset
	}
}
//-------------------------------------------------------------------------------------------------
/* TIMER0_A1 */
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
	if(TA0IV & TIMERA0_OVF)	// Overflow
	{
		varCountTime++;
		if (varCountTime == 1)
		{
			controlRelayOn(IO_PORT1_PIN, IO_PORT2_PIN);
		}
		else if(varCountTime == (GAIN*regFirmDuty))
		{
			controlRelayOff(IO_PORT1_PIN, IO_PORT2_PIN);
		}
		else if(varCountTime == (GAIN*regFirmPeriod))
		{
			controlRelayOn(IO_PORT1_PIN, IO_PORT2_PIN);
			varCountTime = 0;
		}
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

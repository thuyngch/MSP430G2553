/*
 *	File			:	main.c
 *	Date created	:	08/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Keypad 4x4
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
	gpioSetup(PORT2, 0xFF, PIN_KEYPAD_OUT);
	gpioIntSetup(PORT2, PIN_KEYPAD_IN, PIN_KEYPAD_IN, INT_PORT_ON);

	//-LCD-//
#ifdef USE_LCD
	LCD_Init();
	LCD_Clear();
	LCD_Home();
#endif /* USE_LCD */

	//-I2C-//
	i2cSetup(I2C_MASTER, I2C_ADDR_SLAVE, 10, INT_I2C_RX_OFF, INT_I2C_TX_OFF, INT_I2C_STT_OFF);

	//-Firmware-//
	firmwareSetup();
//-------------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
		for(varCount = 0; varCount < 4; varCount++)
		{
			P2OUT = arrOut[varCount];
			__delay_cycles(DL_OUT);
		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* PORT2 */
#pragma vector = PORT2_VECTOR
__interrupt void port2Isr (void)
{
	//-Get keypad-//
	keypadButtonIdentify(P2IFG);												// Identify interrupt

	//-Process-//
	if(regFirmStatus & FIRM_STT_MODE_SEL)										// A, B, C is pressed
	{
#ifdef USE_LCD
		lcdNotifyMode(varFirmMode);
#endif	/* USE_LCD */
#ifdef USE_LED_7SEG
		__delay_cycles(1);														// Reserved
#endif	/* USE_LED_7SEG */
		if(regFirmStatus & FIRM_STT_PERIOD)										// Input for Period
		{
			firmwareInputValue(FIRM_STT_PERIOD);
		}
		if(regFirmStatus & FIRM_STT_DUTY)										// Input for Duty
		{
			firmwareInputValue(FIRM_STT_DUTY);
		}
	}
	if(regFirmStatus & FIRM_STT_EXIT_SEL)										// D is pressed
	{
		firmwareExit();
	}
	if(regFirmOvf & FIRM_OVF_CONFIRM)											// If confirm all
	{
		firmwareConfirm();														// Implement command
	}
	__delay_cycles(DL_ANTI_NOISE * FREQUENCY);
	P2IFG = 0;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

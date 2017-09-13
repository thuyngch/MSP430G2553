/*
 *	File			:	MAIN01_0.0.101.c
 *	Date created	:	06/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Main file of project for Chip_01
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
/* Use of Chip */
//#define		USE_CHIP_01

/* Use of Modules */
#define		USE_CAPTOUCH
#define		USE_I2C


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER01_0.0.101.h"


#ifdef		USE_CHIP_01
/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
void main (void)
{
	//-WDT-//
	wdtSetup(WDT_OFF, WDT_TIME_8MS);
	//=============================================================================================
	//-CLK-//
	clkSetup(CLK_DCO_16MHZ);
	//=============================================================================================
	//-GPIO-//
	gpioSetup(PORT2, GPIO_PORT2_PIN, GPIO_PORT2_OUT);
	gpioHigh(PORT2, PIN_LED_TP);
	//=============================================================================================
#ifdef 	USE_CAPTOUCH
	//-CAPACITIVE TOUCH-//
	capTouchSetup(&sCapTouchSensor);
#endif	/* USE_CAPTOUCH */
	//=============================================================================================
	//-I2C-//
#ifdef 	USE_I2C
	i2cSetup(I2C_MASTER, I2C_ADDR_TOUCHPAD, 40, INT_I2C_RX_ON, INT_I2C_TX_OFF, INT_I2C_STT_OFF);
	__delay_cycles(DL_500MS * FREQUENCY);
#endif	/* USE_I2C */
	gpioLow(PORT2, PIN_LED_TP);

//	cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_0);
//	__delay_cycles(1000);
//	cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_1);
//	__delay_cycles(1000);
//	cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendToLCD_Button_2);
//	__delay_cycles(1000);
//	cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendToLCD_Button_3);
//	__delay_cycles(1000);
//	cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_Confirm);
//	__delay_cycles(1000);
	//---------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
#ifdef	USE_CAPTOUCH
#ifdef 	USE_I2C
		/* Detect which button is pressed and send info to LCD_RFID chip */
		touchPadDetectBtn();
#endif	/* USE_I2C */
#endif	/* USE_CAPTOUCH */
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
#ifdef 	USE_I2C
/* USCIAB0 TX */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0_TX_ISR (void)
{
#ifdef 	USE_CAPTOUCH
	/* Reset TimerA1 */
	TA1CTL &= ~MC_1;
#endif	/* USE_CAPTOUCH */

	/* Read Buffer */
	varI2CData01 = UCB0RXBUF;
	gpioHigh(PORT2, PIN_LED_TP);

	/* Set Status Register */
	switch (varI2CData01)
	{
		case I2C_HEADER_LCD_RFID:
			sRegisterStatus01.bCommunication = eCommunicationLcdRfid;
			break;
		case I2C_ENDING:
			sRegisterStatus01.bCommunication = eCommunicationNone;
			break;
		default:
			/* Process Data */
			switch (sRegisterStatus01.bCommunication)
			{
				//-Communicate with LCD_RFID Chip-//
				case eCommunicationLcdRfid:
					if(varI2CData01 == eLCDSendToTouchPad_Warning)
					{
						speaker01Play();
					}
					break;
			}
	}
	gpioLow(PORT2, PIN_LED_TP);

#ifdef 	USE_CAPTOUCH
	/* Resume TimerA1 */
	TA1CTL |= MC_1;
	TA1R = 0;
#endif	/* USE_CAPTOUCH */
}
#endif	/* USE_I2C */


/**************************************************************************************************
 *	END OF MAIN01_0.0.101.c
 *************************************************************************************************/
#endif	/* USE_CHIP_01 */

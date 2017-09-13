/*
 *	File			:	MAIN02_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Main file of project for Chip_02
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
/* Use of Chip */
//#define		USE_CHIP_02

/* Use of Modules */
//#define		USE_UART
#define		USE_I2C
#define		USE_RFID
#define		USE_LCD16x2
#define		USE_FLASH


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER02_0.0.101.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
#ifdef	USE_CHIP_02
void main (void)
{
	/* SETUP */
	//-CLK-//
	clkSetup(CLK_DCO_16MHZ);
	//=============================================================================================
	//-WDT-//
	wdtSetup(WDT_OFF, WDT_TIME_32MS);
	//=============================================================================================
	//-GPIO-//
	gpioSetup(PORT1, GPIO_PORT1_PIN, GPIO_PORT1_OUT);
	gpioSetup(PORT2, GPIO_PORT2_PIN, GPIO_PORT2_OUT);
	gpioIntSetup(PORT2, GPIO_PORT2_IN, GPIO_PORT2_IN, INT_PORT_ON);
	gpioHigh(PORT1, PIN_LED_RFID);
	//=============================================================================================
#ifdef USE_LCD16x2
	//-LCD 16x2-//
	lcdSetup(LCD_PORT_2, PIN_LCD_RS, PIN_LCD_EN, 0);
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("    Welcome!    ");
#endif /* USE_LCD16x2 */
	//=============================================================================================
#ifdef USE_RFID
	//-SPI-//
	spiA0Setup(SPI_MASTER, 2, INT_SPIA0_RX_OFF, INT_SPIA0_TX_OFF);
	//=============================================================================================
	//-RFID-//
	rfidSetup(RFID_PORT_1, PIN_RFID_SS, PIN_RFID_RST);
#endif /* USE_RFID */
	//=============================================================================================
	//-UART-//
#ifdef	USE_UART
	uartSetup(CLKS_SMCLK_16MHZ, BAUD_9600, INT_RXD_OFF);
	__delay_cycles(DL_500MS * FREQUENCY);
#endif	/* USE_UART */
	//=============================================================================================
#ifdef USE_I2C
	//-I2C-//
	i2cSetup(I2C_MASTER, I2C_ADDR_LCD_RFID, 40, INT_I2C_RX_ON, INT_I2C_TX_OFF, INT_I2C_STT_OFF);
	__delay_cycles(DL_500MS * FREQUENCY);
#endif /* USE_I2C */
	//=============================================================================================
	//-FLASH-//
#ifdef	USE_FLASH
	flashSetup(CLK_DCO_16MHZ);
	__delay_cycles(DL_500MS * FREQUENCY);
	if(sRegisterStatus02.bLoadDataFromWifi == eLoadDataFromWifiFalse) data02LoadFromFlash();
#endif /* USE_FLASH */
	//=============================================================================================
	//-NOTIFY-//
#ifdef	USE_UART
	txdStr("Inialize System\n");
#endif	/* USE_UART */
	gpioLow(PORT1, PIN_LED_RFID);
	//---------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
#ifdef	USE_RFID
		varReaderStatus = rfidGetCardID(arrReaderID);		// Detect CARD and get ID
		if(varReaderStatus == MI_OK)
		{
			gpioHigh(PORT1, PIN_LED_RFID);
			varNoCurrent = data02CheckID();
			if((varNoCurrent != -1) && (varNoCurrent != varNoLast))	// Correct ID, New access
			{
				sRegisterStatus02.bButtonNumOfDigit = 0;
				sRegisterStatus02.bHavePeople = true;
				varNoLast = varNoCurrent;
				cmn02BtnDataClear();
#ifdef	USE_LCD16x2
				displayName(varNoCurrent);
#endif 	/* USE_LCD16x2 */
			}
			else if(varNoCurrent == -1)			// Wrong ID
			{
				sRegisterStatus02.bButtonNumOfDigit = 0;
				sRegisterStatus02.bHavePeople = false;
				cmn02BtnDataClear();
				varNoLast = -1;
#ifdef USE_LCD16x2
				displayErrCard();
#endif 	/* USE_LCD16x2 */
			}
			__delay_cycles(DL_100MS * FREQUENCY);
			gpioLow(PORT1, PIN_LED_RFID);
		}
#endif 	/* USE_RFID */

		//=========================================================================================
		/* Wrong Password */
		if(sRegisterStatus02.bIsErrorCard)
		{
			gpioHigh(PORT1, PIN_LED_RFID);
			sRegisterStatus02.bIsErrorCard = false;
#ifdef	USE_I2C
			cmn02Send(I2C_ADDR_TOUCHPAD, eLCDSendToTouchPad_Warning);
#endif	/* USE_I2C */
			gpioLow(PORT1, PIN_LED_RFID);
			while(1);						// Entity loop, require a RST trigger to resume
		}

		//=========================================================================================
		/* Corect Password */
		if(sRegisterStatus02.bIsCorrectCard)
		{
			gpioHigh(PORT1, PIN_LED_RFID);
			sRegisterStatus02.bIsCorrectCard = false;
#ifdef	USE_I2C
//			cmn02Send(I2C_ADDR_WIFI_SERVO, eLCDSendToServo_Open);
#endif	/* USE_I2C */
#ifdef	USE_LCD16x2
			displaySuccess(varNoCurrent);
#endif	/* USE_LCD16x2 */
			gpioLow(PORT1, PIN_LED_RFID);
		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINE
 *************************************************************************************************/
#ifdef USE_I2C
/* USCIAB0 RX ISR */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	/* Read Buffer */
	varI2C02Data = UCB0RXBUF;
	gpioHigh(PORT1, PIN_LED_RFID);
#ifdef	USE_UART
	if((varI2C02Data >= '0') && (varI2C02Data <= ';')) txdChar(varI2C02Data);
#endif

	/* Set Status Register */
	switch (varI2C02Data)
	{
		case I2C_HEADER_WIFI_SERVO:
			sRegisterStatus02.bCommunication = eCommunicationWifiServo;
			sRegisterStatus02.bLoadDataFromWifi = eLoadDataFromWifiTrue;
			break;
		case I2C_HEADER_TOUCHPAD:
			sRegisterStatus02.bCommunication = eCommunicationTouchPad;
			break;
		case I2C_ENDING:
			sRegisterStatus02.bCommunication = eCommunicationNone;
			break;
		default:
			/* Process Data */
			switch (sRegisterStatus02.bCommunication)
			{
				//-Communicate with TOUCHPAD Chip-//
				case eCommunicationTouchPad:
					if(sRegisterStatus02.bHavePeople)
					{
						switch (firmwareCheckTouchPadData(varI2C02Data))
						{
							case eTouchPadDataNumber:
								if(sRegisterStatus02.bButtonNumOfDigit < 4)
								{
									arrButtonRxData[sRegisterStatus02.bButtonNumOfDigit++] = varI2C02Data;
#ifdef	USE_LCD16x2
									displayTotal(varNoCurrent, varI2C02Data);
#endif	/* USE_LCD16x2 */
								} else displayOverFlow();
								break;
							case eTouchPadDataControl:
								if(varI2C02Data == eTouchPadSendTolCD_Button_Confirm)
								{
									if(sRegisterStatus02.bButtonNumOfDigit < 4) displayNull();
									else
									{
										sRegisterStatus02.bPasswordResult =
												data02CheckPassword(varNoCurrent, arrButtonRxData);
										if(sRegisterStatus02.bPasswordResult)
											sRegisterStatus02.bIsCorrectCard = true;
										else
										{
											sRegisterStatus02.bIsErrorCard = true;
#ifdef	USE_LCD16x2
											displayError();
#endif	/* USE_LCD16x2 */
										}
									}
								}
								else if (varI2C02Data == eTouchPadSendTolCD_Button_Clear)
								{
									sRegisterStatus02.bButtonNumOfDigit = 0;
									cmn02BtnDataClear();
#ifdef	USE_LCD16x2
									displayClear();
#endif	/* USE_LCD16x2 */
								}
								break;
						}
						break;
					}
				break;
				//=================================================================================
				//-Communicate with WIFI_SERVO Chip-//
				case eCommunicationWifiServo:
					if((varI2C02Data == '/') && (sRegisterStatus02.bWifiSection == eWifiSectionNone))
						sRegisterStatus02.bWifiSection = eWifiSectionStart;
					else if(varI2C02Data == 10) sRegisterStatus02.bWifiSection = eWifiSectionEnd;

					if(sRegisterStatus02.bWifiSection == eWifiSectionStart)
						arrCmnBuff[varCountWifiData++] = varI2C02Data;
					else if(sRegisterStatus02.bWifiSection == eWifiSectionEnd)
					{
						varCountWifiData = 0;
						sRegisterStatus02.bWifiSection = eWifiSectionNone;
						cmn02StrDecoder(arrCmnBuff, &varNoBuff, strNameBuff, arrIDBuff, arrPasswordBuff);
						data02SaveAccount(varNoBuff);
#ifdef USE_FLASH
						data02SaveToFlash();
#endif /* USE_FLASH */
					}
					break;
			}
			break;
	}
	gpioLow(PORT1, PIN_LED_RFID);
}
#endif	/* USE_I2C */
//-------------------------------------------------------------------------------------------------
/* PORT ISR */
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR (void)
{
	switch (P2IFG & PIN_BTN_CLOSE)
	{
		case PIN_BTN_CLOSE:
			gpioHigh(PORT2, PIN_LED_BTN);
			sRegisterStatus02.bButtonNumOfDigit = 0;
			cmn02BtnDataClear();
			varNoLast = -1;
			LCD_Clear();
			LCD_Home();
			LCD_PrintString("    Welcome!    ");
			cmn02Send(I2C_ADDR_WIFI_SERVO, eLCDSendToServo_Close);
			__delay_cycles(DL_1S * FREQUENCY);
			gpioLow(PORT2, PIN_LED_BTN);
			break;
	}
	//-Exit ISR-//
	__delay_cycles(DL_ANTI_NOISE * FREQUENCY);
	P2IFG = 0;
}
#endif /* USE_CHIP_02 */


/**************************************************************************************************
 *	END OF MAIN02_0.0.101.c
 *************************************************************************************************/

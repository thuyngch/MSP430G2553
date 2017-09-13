/*
 *	File			:	MAIN03_0.0.101.c
 *	Date created	:	29/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Main file of project for Chip_03
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
/* Use of Chip */
#define		USE_CHIP_03

/* Use of Modules */
#define		USE_UART
#define		USE_ESP8266
//#define		USE_UART_WIFISHIELD
#define		USE_I2C
#define		USE_TIMER
//#define		USE_PWM

/* Use of purpose */
//#define		USE_EXAMPLE_FRAME_FOR_I2C_CMN		// unless, using normal function


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER03_0.0.101.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
#ifdef	USE_CHIP_03
void main (void)
{
	/* SETUP */
	//-WDT-//
	wdtSetup(WDT_OFF, WDT_TIME_32MS);
	//=============================================================================================
	//-CLK-//
	clkSetup(CLK_DCO_16MHZ);
	//=============================================================================================
	//-GPIO-//
	gpioSetup(PORT1, GPIO_PORT1_PIN, GPIO_PORT1_OUTPUT);
	gpioSetup(PORT2, GPIO_PORT2_PIN, GPIO_PORT2_OUTPUT);
	gpioHigh(PORT1, PIN_WIFI_LED);
	//=============================================================================================
#ifdef	USE_TIMER
	//-TIMER-//
	timerASetup(TIMER_A_0, MODE_UP, ID_3, INT_OVF_ON, 0, 65000);
	wifi03StopTimerCount();
#endif 	/* USE_TIMER */
	//=============================================================================================
#ifdef 	USE_PWM
	//-PWM-//
	timerASetup(TIMER_A_1, MODE_UP, ID_3, INT_OVF_OFF, 0, 1000);
	pwmSetup(TIMER_A_1, MODE_UP, BIT1, PWM_RST_SET, 1000, 0);
#endif 	/* USE_PWM */
	//=============================================================================================
#ifdef 	USE_UART
	//-UART-//
	uartSetup(CLKS_SMCLK_16MHZ, BAUD_9600, INT_RXD_ON);
	txdStr("Initialize System\n");
	wifi03ClearBuffer(arrUARTBuff03, 256);
#endif /* USE_UART */
	//=============================================================================================
#ifdef	USE_ESP8266
	//-ESP8266-//
	esp8266Setup(ESP8266_PORT_1, PIN_WIFI_RST, PIN_WIFI_EN);
	wifi03StartTimerCount(65000);
	while(!wifi03CheckATCmdComplete("ready")) wifi03StartTimerCount(65000);

	esp8266CheckModule();				// Send AT command
	wifi03StartTimerCount(65000);		// Start Timer for counting timeout
	while(!wifi03CheckATCmdComplete("OK")) wifi03StartTimerCount(65000);
										// Loop for detecting successful progress

	esp8266ConnectWifi("lau 6", "0988851122vt");
	wifi03StartTimerCount(65000);
	while(!wifi03CheckATCmdComplete("OK")) wifi03StartTimerCount(65000);

	esp8266MultiConnection();
	wifi03StartTimerCount(65000);
	while(!wifi03CheckATCmdComplete("OK")) wifi03StartTimerCount(65000);

	esp8266MakeServer(8000);
	wifi03StartTimerCount(65000);
	while(!wifi03CheckATCmdComplete("OK")) wifi03StartTimerCount(65000);

	esp8266GetIP();
	wifi03StartTimerCount(65000);
	while(!wifi03CheckATCmdComplete("OK")) wifi03StartTimerCount(65000);

	wifi03ClearBuffer(arrUARTBuff03, 256);
#endif	/* USE_ESP8266 */
	//=============================================================================================
#ifdef 	USE_I2C
	//-I2C-//
	i2cSetup(I2C_MASTER, I2C_ADDR_WIFI_SERVO, 40, INT_I2C_RX_ON, INT_I2C_TX_OFF, INT_I2C_STT_OFF);
	__delay_cycles(DL_500MS * FREQUENCY);
#endif /* USE_I2C */
	gpioLow(PORT1, PIN_WIFI_LED);
	//---------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
#ifdef 	USE_EXAMPLE_FRAME_FOR_I2C_CMN
		cmn03MakeSampleFrame();
		cmn03SendToRFID();
		__delay_cycles(DL_2S * FREQUENCY);
#else
#ifdef	USE_UART_WIFISHIELD
		if(sRegisterStatus03.bIsWifiData == eIsWifiDataFalse)
		{
			sRegisterStatus03.bIsWifiData = eIsWifiDataNone;
			cmn03SendToRFID();
		}
#endif	/* USE_UART_WIFISHIELD */
#ifdef	USE_ESP8266
		if(sRegisterStatus03.bEnoughDataFromWifi)
		{
			sRegisterStatus03.bEnoughDataFromWifi = false;
#ifdef	USE_I2C
			cmn03SendToRFID();
#endif	/* USE_I2C */
		}
#endif	/* USE_ESP8266 */
#endif	/* USE_EXAMPLE_FRAME_FOR_I2C_CMN */
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINE
 *************************************************************************************************/
#ifdef 	USE_I2C
/* USCIAB0 TX */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	/* Read Buffer */
	varI2CData03 = UCB0RXBUF;
	gpioHigh(PORT1, PIN_WIFI_LED);

	/* Set Status Register */
	switch (varI2CData03)
	{
		case I2C_HEADER_LCD_RFID:
			sRegisterStatus03.bCommunication = eCommunicationLcdRfid;
			break;
		case I2C_ENDING:
			sRegisterStatus03.bCommunication = eCommunicationNone;
			break;
		default:	/* Process Data */
			switch (sRegisterStatus03.bCommunication)
			{
				case eCommunicationLcdRfid:
					if(varI2CData03 == eLCDSendToServo_Open) 		servo03Open();
					else if(varI2CData03 == eLCDSendToServo_Close)	servo03Close();
					break;
			}
			break;
	}
	gpioLow(PORT1, PIN_WIFI_LED);
}
#endif /* USE_I2C */

//-------------------------------------------------------------------------------------------------
/* UART_RXD_ISR */
#ifdef	USE_ESP8266
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	varUART03 = rxdChar();					// Read received data
	gpioHigh(PORT1, PIN_WIFI_LED);			// Turn on LED
	if(!sRegisterStatus03.bEnoughDataFromWifi)
											// bEnoughDataFromWifi must be false to do process below
	{
		if((varUART03 == '/') && arrUARTBuff03[varCountUARTData03 - 1] == ':')
			varCountUARTData03 = 0;				// If meeting the first '/', reset counter index
		arrUARTBuff03[varCountUARTData03++] = varUART03;
												// Store in arrUARTBuff03
		if(arrUARTBuff03[varCountUARTData03 - 1] == '\0' &&
		   arrUARTBuff03[varCountUARTData03 - 2] == '\n' &&
		   arrUARTBuff03[varCountUARTData03 - 3] == '\r' &&
		   arrUARTBuff03[varCountUARTData03 - 4] == '\0')
												// If correct this characters, set bEnoughDataFromWifi
			sRegisterStatus03.bEnoughDataFromWifi = true;
		if(varUART03 == '\0')					// If meet '\0', set IsNullCharacter and stop timer
		{
			sRegisterStatus03.bIsNullCharacter = true;
			wifi03StopTimerCount();
		}
	}
	gpioLow(PORT1, PIN_WIFI_LED);			// Turn off LED
}
#endif	/* USE_ESP8266 */

#ifdef 	USE_UART_WIFISHIELD
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	gpioHigh(PORT1, PIN_WIFI_LED);
	varUART03 = rxdChar();
	if(varUART03 == '/') sRegisterStatus03.bIsWifiData = eIsWifiDataTrue;
	else if((sRegisterStatus03.bIsWifiData == eIsWifiDataTrue) && (varUART03 == 10))
	{
		arrBuff03[varCountWifiData03++] = varUART03;
		sRegisterStatus03.bIsWifiData = eIsWifiDataFalse;
	}
	if(sRegisterStatus03.bIsWifiData == eIsWifiDataTrue)
		arrBuff03[varCountWifiData03++] = varUART03;
	else if (sRegisterStatus03.bIsWifiData == eIsWifiDataFalse) varCountWifiData03 = 0;
	gpioLow(PORT1, PIN_WIFI_LED);
}
#endif /* USE_UART_WIFISHIELD */

//-------------------------------------------------------------------------------------------------
#ifdef	USE_TIMER
/* TIMERA0 */
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
	if(TA0IV)
	{
		sRegisterStatus03.bIsNullCharacter = true;		// If overflow, escape while loop
	}
}
#endif	/* USE_TIMER */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF MAIN03_0.0.101.c
 *************************************************************************************************/
#endif /* USE_CHIP_03 */

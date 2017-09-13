/*
 *	File			:	MAIN00.c
 *	Date created	:	26/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#define	USE_CHIP00


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER00.h"


#ifdef	USE_CHIP00
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
	clkSetup(CLK_DCO_1MHZ);
	//=============================================================================================
	//-GPIO-//
	gpioSetup(PORT1, PIN_LED_RED, PIN_LED_RED);
	//=============================================================================================
	//-TIMER-//
	timerASetup(TIMER_A_0, MODE_UP, ID_3, INT_OVF_ON, 0, 65000);
	wifi00StopTimerCount();
	//=============================================================================================
	//-UART-//
	uartSetup(CLKS_SMCLK_1MHZ, BAUD_9600, INT_RXD_ON);
	//=============================================================================================
	//-ESP8266-//
	esp8266Setup(ESP8266_PORT_1, PIN_WIFI_RST, PIN_WIFI_EN);
	wifi00StartTimerCount(65000);
	while(!wifi00CheckATCmdComplete("ready")) wifi00StartTimerCount(65000);

	RESETUP_ESP:
	esp8266CheckModule();				// Send AT command
	wifi00StartTimerCount(65000);		// Start Timer for counting timeout
	while(!wifi00CheckATCmdComplete("OK")) wifi00StartTimerCount(65000);
										// Loop for detecting successful progress

	esp8266ConnectWifi("0988851122.", "875269Abc");
	wifi00StartTimerCount(65000);
	while(!wifi00CheckATCmdComplete("OK")) wifi00StartTimerCount(65000);

	esp8266MultiConnection();
	wifi00StartTimerCount(65000);
	while(!wifi00CheckATCmdComplete("OK")) wifi00StartTimerCount(65000);

	esp8266MakeServer(8000);
	wifi00StartTimerCount(65000);
	while(!wifi00CheckATCmdComplete("OK")) wifi00StartTimerCount(65000);

	esp8266GetIP();
	wifi00StartTimerCount(65000);
	while(!wifi00CheckATCmdComplete("OK")) wifi00StartTimerCount(65000);

	wifi00ClearBuffer(arrUART00, 256);
	sRegisterStatus00.bIsEnoughWifiData = false;
	//---------------------------------------------------------------------------------------------
	/* LOOP */
	while(1)
	{
		/* Send TXD when receiving enough data from WiFi */
		 if(sRegisterStatus00.bIsEnoughWifiData)
		 {
			 fw00DetectButton(arrUART00);
			 cmn00Send();

			 sRegisterStatus00.bIsEnoughWifiData = false;
			 varCountUART00 = 0;
		 }

		 /* If an incident Reset occurs with ESP8266 */
		 if(arrUART00[varCountUART00 - 1] == 'y' &&
			arrUART00[varCountUART00 - 2] == 'd' &&
			arrUART00[varCountUART00 - 3] == 'a' &&
			arrUART00[varCountUART00 - 4] == 'e' &&
			arrUART00[varCountUART00 - 5] == 'r')	goto RESETUP_ESP;
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* UART RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	/* Read RXD */
	varUART00 = rxdChar();
	gpioHigh(PORT1, LED_RED);

	/* Process data */
	if(varUART00 == '/') varCountUART00 = 0;
											// If meeting the first '/', reset counter index
	arrUART00[varCountUART00++] = varUART00;
											// Store in arrUART00
	if(arrUART00[varCountUART00 - 1] == '\0' &&
		arrUART00[varCountUART00 - 2] == '\n' &&
		arrUART00[varCountUART00 - 3] == '\r' &&
		arrUART00[varCountUART00 - 4] == '>')
	{										// If enough needed data, start processing it
		sRegisterStatus00.bIsEnoughWifiData = true;
	}


	if(varUART00 == '\0')					// If meet '\0', set IsNullCharacter and stop timer
	{
		sRegisterStatus00.bIsNullCharacter = true;
		wifi00StopTimerCount();
	}

	/* Escape ISR*/
	gpioLow(PORT1, LED_RED);
}
//-------------------------------------------------------------------------------------------------
/* TIMERA0 */
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
	if(TA0IV) sRegisterStatus00.bIsNullCharacter = true;	// If overflow, escape while loop
}


/**************************************************************************************************
 *	END OF MAIN00.c
 *************************************************************************************************/
#endif	/* USE_CHIP00 */

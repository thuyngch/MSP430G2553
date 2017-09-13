/*
 *	File			:	main.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Main source of Multi-Clock
 */

//#define 	TEST_UART			// Use for testing modules but UART
//#define	TEST_UART_BUTTON	// Test button through UART
#define 	USE_DS1307			// Use DS1307 to count time
#define	INIT_DS1307			// Initial DS1307
#define		TEST_SPEAKER		// Test speaker for initialization
//#define		USE_IDLE			// Low power mode
//#define	USE_WATCHDOG		// Using WDT
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "Source Files/VERSION 0_0_101/HEADER_0_0_101.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
volatile unsigned char varTimerCount = 0;		// Used in TIMERA0_A1 ISR
volatile unsigned int varTimerIdle	= 0;		// Used for count idle interval


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
void main (void)
{
	/* SETUP */
	//-CLOCK-//
	clkSetup(CLK_DCO_8MHZ);

	//-WDT-//
#ifdef USE_WATCHDOG
	wdtSetup(WDT_ON, WDT_TIME_32MS);
#else
	wdtSetup(WDT_OFF, WDT_TIME_32MS);
#endif /* USE_WATCHDOG */

	//-GPIO-//
	gpioSetup(PORT1, PIN_GPIO_PORT1, PIN_GPIO_OUT_PORT1);						// Output
	gpioSetup(PORT2, PIN_GPIO_PORT2, PIN_GPIO_OUT_PORT2);						// Output

	gpioIntSetup(PORT1, PIN_GPIO_IN_PORT1, 0, INT_PORT_OFF);					// Input
	gpioIntSetup(PORT2, PIN_GPIO_IN_PORT2, PIN_GPIO_IN_PORT2, INT_PORT_ON);		// Input

	ic74HC595Setup(PIN_595_DATA, PIN_595_CLK, PIN_595_LATCH);					// 74HC595

	display4017Calib();				// Reset position to S0

	//-FLASH-//
	flashSetup(CLK_DCO_8MHZ);

	//-DATA-//
	dataLoad(ePageAlarm);
	dataLoad(ePageFocus);

#ifdef USE_DS1307
	//-TIMERA0-//
	timerASetup(TIMER_A_0, MODE_UP, ID_3, INT_OVF_ON, 0, TIMERA0_PERIOD);	// Overflow every 500ms
#endif /* USE_DS1307 */

#ifdef USE_IDLE
	//-TIMERA1-//
	timerASetup(TIMER_A_1, MODE_UP, ID_3, INT_OVF_ON, 0, TIMERA1_PERIOD);	// Overflow every 500ms
#endif /* USE_IDLE */

#ifdef TEST_UART
	//-UART-//
	uartSetup(CLKS_SMCLK_8MHZ, BAUD_9600, INT_RXD_OFF);
	__delay_cycles(DL_50MS);
#endif /* TEST_UART */

#ifdef TEST_UART_BUTTON
	//-UART-//
	uartSetup(CLKS_SMCLK_8MHZ, BAUD_9600, INT_RXD_OFF);
	__delay_cycles(DL_50MS);
#endif /* TEST_UART_BUTTON */

#ifdef USE_DS1307
	//-I2C-//
	i2cSetup(I2C_MASTER, DS1307_ADDRESS);

#ifdef INIT_DS1307
	//-DS1307-//
	ds1307Setup(23, 15, 30, 3, 18, 10, 16);		// Initial time: 00:00:00 Sat 15/10/2016
#endif /*INIT_DS1307*/
#endif /* USE_DS1307 */

#ifdef TEST_UART
	//-Notify System-//
	__delay_cycles(DL_100MS);
	txdStr("Initial System\n");
#endif /* TEST_UART */

#ifdef TEST_UART_BUTTON
	//-Notify System-//
	__delay_cycles(DL_100MS);
	txdStr("Initial System\n");
#endif /* TEST_UART_BUTTON */

#ifdef TEST_SPEAKER
	gpioHigh(PORT1, PIN_SPEAKER);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	__delay_cycles(DL_1S);
	gpioLow(PORT1, PIN_SPEAKER);
#endif

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		if(sStatusRegister.bIdle == 1)
		{
//			__bis_SR_register(CPUOFF + GIE);	// Enter Low Power Mode 0
		}

		switch (sStatusRegister.bPage)
		{
			case ePageNormal:
				firmPageNormalDisplay();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
				break;
			//=========================================================================================
			case ePageTime:
				firmPageTimeDisplay();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
				break;
			//=========================================================================================
			case ePageAlarm:
				firmPageAlarmDisplay();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
				break;
			//=========================================================================================
			case ePageFocus:
				firmPageFocusDisplay();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
				break;
		}
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* PORT2 */
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR (void)
{
	//-Clear Idle mode-//
//	sStatusRegister.bIdle = 0;
//	__bis_SR_register_on_exit(CPUOFF);

	//-Identify whether button is pressed-//
	buttonIdentify();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

	//-Processing-//
	if		(sStatusRegister.bPage == ePageTime)
	{
		varTimerIdle = 0;
		firmPageTime();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}
	else if	(sStatusRegister.bPage == ePageAlarm)
	{
		varTimerIdle = 0;
		firmPageAlarm();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}
	else if (sStatusRegister.bPage == ePageFocus)
	{
		varTimerIdle = 0;
		firmPageFocus();

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
	}

	//-Exit ISR-//
	__delay_cycles(DL_ANTI_NOISE * FREQUENCY);
	P2IFG = 0;
}
//-------------------------------------------------------------------------------------------------
/* TIMER0_A1 */
// Every 500ms, TIMERA0_A1 is overflow and jump to this ISR
#ifdef USE_DS1307
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
	if(TA0IV & TIMERA0_OVF)	// Overflow
	{
		varTimerCount++;

		//-Every 1s, do this work-//
		if(varTimerCount == 16)
		{
#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

			timerGetCurrent();		// Get current time
			timerAlarm(sAlarm.varHour, sAlarm.varMinute, 0);	// Alarm
			timerFocus(sFocus.varInterval);

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */

#ifdef TEST_UART
			ds1307Print();
#endif	/* TEST_UART */
			varTimerCount = 0;		// Reset value of varTimerCount
		}
	}
}
#endif	/* USE_DS1307 */
//-------------------------------------------------------------------------------------------------
/* TIMER1_A1 */
#ifdef USE_IDLE
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
{
	if(TA1IV & TIMERA1_OVF)	// Overflow
	{
		varTimerIdle++;
		if(varTimerIdle == 600)			// If 5 idle minutes ==> Turn off CPU
		{
			varTimerIdle = 0;
//			sStatusRegister.bIdle = 1;
		}
	}

#ifdef USE_WATCHDOG
	/* Clear WDT */
	wdtClear();
#endif /* USE_WATCHDOG */
}
#endif /* USE_IDLE */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

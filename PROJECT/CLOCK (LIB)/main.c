/*
 *	File			:	main.c
 *	Date created	:	31/05/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.2.1
 *	Description		:	Construct Clock library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include "VERSION 1_2_3/CLOCK_1_2_3.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "VERSION 1_0_1/TIMERA_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Globals */
char varRxd;
unsigned int varInterval;
char strBuff[10];
unsigned long varCmd = 100;
const clk_Wdt *psClkSetup[4];

/* Externals */
extern const timer_A_Setup sTimerASetup[];
extern const timer_A_Cap_Setup sTimerACapSetup[];


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:	port1Int
 *	Purpose	:	Use in port1Isr function
 * 	Input	:	None
 * 	Output	:	None
 */
//void port1Int (void)
//{
//	if (P1IFG & BUTTON)
//	{
//		ledOn(LED_RED);
//		__delay_cycles(DL_2S);
//		ledOff(LED_RED);
//		//Exit ISR//
//		P1IFG &= ~BUTTON;
//	}
//}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	rxdInt
 *	Purpose	:	Use in rxdIsr function
 * 	Input	:	None
 * 	Output	:	None
 */
void rxdInt(void)
{
	varRxd = rxdChar();
	switch (varRxd)
	{
		case '0':
			varCmd = 10;
//			clkSetup(*psClkSetup[(int)varRxd - 48]);
//			uartSetup(CLKS_SMCLK_1MHZ, BAUD_9600, INT_RXD_ON);
			txdStr("Mode 0 is actived\n");
			break;
		case '1':
			varCmd = 20;
//			clkSetup(*psClkSetup[(int)varRxd - 48]);
//			uartSetup(CLKS_SMCLK_8MHZ, BAUD_9600, INT_RXD_ON);
			txdStr("Mode 1 is actived\n");
			break;
		case '2':
			varCmd = 50;
//			clkSetup(*psClkSetup[(int)varRxd - 48]);
//			uartSetup(CLKS_SMCLK_12MHZ, BAUD_9600, INT_RXD_ON);
			txdStr("Mode 2 is actived\n");
			break;
		case '3':
			varCmd = 100;
//			clkSetup(*psClkSetup[(int)varRxd - 48]);
//			uartSetup(CLKS_SMCLK_16MHZ, BAUD_9600, INT_RXD_ON);
			txdStr("Mode 3 is actived\n");
			break;
		case '4':
			varCmd = 200;
			txdStr("Mode 4 is actived\n");
			break;
		case '5':
			varCmd = 500;
			txdStr("Mode 5 is actived\n");
			break;
		case '6':
			varCmd = 1000;
			txdStr("Mode 6 is actived\n");
			break;
		case '7':
			varCmd = 2000;
			txdStr("Mode 7 is actived\n");
			break;
		case '8':
			varCmd = 1;
			txdStr("Mode 8 is actived\n");
			break;
		case '9':
			varCmd = 2;
			txdStr("Mode 9 is actived\n");
			break;
		case 'a':
			varCmd = 3;
			txdStr("Mode a is actived\n");
			break;
		case 'b':
			varCmd = 0;
			txdStr("Mode a is actived\n");
			break;
		default:
			break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	delay
 *	Purpose	:	Delay an interval
 * 	Input	:	Interval
 * 	Output	:	None
 */


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
int main (void)
{
	/* SETUP */
	//-Clock-//
	clkSetup(sClkSetup.sDco1mhz.sSwdtOn);
//	psClkSetup[0] = &sClkSetup.sDco1mhz.sSwdtOn;
//	psClkSetup[1] = &sClkSetup.sDco8mhz.sSwdtOn;
//	psClkSetup[2] = &sClkSetup.sDco12mhz.sSwdtOn;
//	psClkSetup[3] = &sClkSetup.sDco16mhz.sSwdtOn;

	//-GPIO-//
	gpioSetup(PORT1, LED_GREEN, LED_GREEN);

	//-UART-//
	uartSetup(CLKS_SMCLK_1MHZ, BAUD_9600, INT_RXD_OFF);

	//-TimerA1-//
	TA1CTL    = TASSEL_2 + MC_2;
	TA1CCTL1 |= CM_3 + CCIS_0 + CAP + CCIE;		// Both edges, Channel A, Capture, Enable Interrupt
	TA1R      = 0;
	P2SEL    |= BIT1;		// P2.1
	P2SEL2   &= ~BIT1;
	P2DIR    &= ~BIT1;
	TA0CCTL1 &= ~COV;
	__bis_SR_register(GIE);
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		ledToggle(LED_GREEN);
		//__delay_cycles(200);
		delay(varCmd);
	}
	return 1;
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* PORT1 */
//#pragma vector = PORT1_VECTOR
//__interrupt void port1Isr (void)
//{
//	port1Int();
//}
//-------------------------------------------------------------------------------------------------
/* RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	rxdInt();
}
//-------------------------------------------------------------------------------------------------
/* Capture */
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA1IV_Interrupt (void)
{
	  switch(__even_in_range(TA1IV,0x0A))
	  {
	      case  TA1IV_TACCR1:
		  {
			//-Rising edge-//
			if (TA1CCTL1 & CCI)
			{
				TA1R = 0;
			}
			//-Falling edge-//
			else
			{
				varInterval = TA1CCR1;
				sprintf(strBuff, "%d", varInterval);
				txdStr((unsigned char*)strBuff);
				txdChar(10);
			}
			break;
		  }
	      default:
    	  {
    		  break;
    	  }
	  }
}

/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

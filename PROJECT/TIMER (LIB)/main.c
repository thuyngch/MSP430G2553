/*
 * 	File			:	main.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct TimerA library
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>
#include <string.h>
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/USCI_UART_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_0_1/TIMERA_1_0_1.h"


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* Variables */
unsigned int varInterval;
unsigned char varRxd;
unsigned char strRxd[20];
unsigned char strString[6];
unsigned char varCount0 = 0, varCount0_0 = 0, varCount0_1 = 0, varCount0_2 = 0;
unsigned char varCount1 = 0, varCount1_0 = 0, varCount1_1 = 0, varCount1_2 = 0;

/* Structs */
pwm_Out *psPwmSetup[4];

/* Externals */
extern clk_Setup sClkSetup[];
extern gpio_Setup sGpioSetup[];
extern gpio_Int_Setup sGpioIntSetup[];
extern uart_Setup sUartSetup[];
extern timer_A_Setup sTimerASetup[];
extern timer_A_Cmp_Setup sTimerACmpSetup[];
extern pwm_Setup sPwmSetup;


/****************************************************************************************
 *	SUB-ROUTINEs
 ***************************************************************************************/
/*
 * Function : toString
 * Input	: varInterval: a variable that you want to be converted to string
 * Output	: strString: variable is converted into this string
 */
void toString (unsigned int varData, unsigned char strString[])
{
	unsigned char varA, varB, varC, varD, varE;
	varA = varData / 10000;
	varB = (varData - varA*10000) / 1000;
	varC = (varData - varA*10000 - varB*1000) / 100;
	varD = (varData - varA*10000 - varB*1000 - varC*100) / 10;
	varE = varData - varA*10000 - varB*1000 - varC*100 - varD*10;

	strString[0] = varA + 48;
	strString[1] = varB + 48;
	strString[2] = varC + 48;
	strString[3] = varD + 48;
	strString[4] = varE + 48;
	strString[5] = '\0';
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA0Ccr0Int
 * Input	: None
 * Output	: TimerA0 CCR0 interrupt
 */
void rxdInt (void)
{
	varRxd = rxdChar();
	if(varRxd == '0')
	{
		pwmSetup(*psPwmSetup[0], 1000, 1000);
		txdStr("Mode 0 is actived\n");
	}
	if(varRxd == '1')
	{
		pwmSetup(*psPwmSetup[0], 1000, 10);
		txdStr("Mode 1 is actived\n");
	}
	if(varRxd == '2')
	{
		timerA0Setup(sTimerASetup[0]);
		pwmSetup(*psPwmSetup[1], 1000, 1000);
		txdStr("Mode 2 is actived\n");
	}
	if(varRxd == '3')
	{
		timerA0Setup(sTimerASetup[0]);
		pwmSetup(*psPwmSetup[1], 1000, 10);
		txdStr("Mode 3 is actived\n");
	}
	if(varRxd == '4')
	{
		timerA1Setup(sTimerASetup[0]);
		pwmSetup(*psPwmSetup[2], 1000, 1000);
		txdStr("Mode 4 is actived\n");
	}
	if(varRxd == '5')
	{
		timerA1Setup(sTimerASetup[0]);
		pwmSetup(*psPwmSetup[2], 1000, 10);
		txdStr("Mode 5 is actived\n");
	}
	if(varRxd == '6')
	{
		timerA1Setup(sTimerASetup[0]);
		pwmSetup(*psPwmSetup[3], 1000, 1000);
		txdStr("Mode 4 is actived\n");
	}
	if(varRxd == '7')
	{
		timerA1Setup(sTimerASetup[0]);
		pwmSetup(*psPwmSetup[3], 1000, 10);
		txdStr("Mode 5 is actived\n");
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA0Ccr0Int
 * Input	: None
 * Output	: TimerA0 CCR0 interrupt
 */
void timerA0Ccr0Int (void)
{
	varCount0_0++;
	if(varCount0_0 == 5)
	{
		ledToggle(LED_RED);
		varCount0_0 = 0;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA0Ccr1Int
 * Input	: None
 * Output	: TimerA0 CCR1 interrupt
 */
void timerA0Ccr1Int (void)
{
	  //-Rising edge-//
	  if (TA0CCTL1 & CCI)
	  {
		  TA0R = 0;
	  }
		//-Falling edge-//
	  else
	  {
		  varInterval = TA0CCR1 - 20;
		  toString(varInterval, strString);
		  txdStr(strString);
		  txdChar('\n');
	  }
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA0Ccr2Int
 * Input	: None
 * Output	: TimerA0 CCR2 interrupt
 */
void timerA0Ccr2Int (void)
{
	varCount0_2++;
	if(varCount0_2 == 5)
	{
		ledToggle(LED_GREEN);
		varCount0_2 = 0;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA0TaifgInt
 * Input	: None
 * Output	: TimerA0 TAIFG interrupt
 */
void timerA0TaifgInt (void)
{
	varCount0++;
	if(varCount0 == 5)
	{
		ledToggle(LED_GREEN);
		varCount0 = 0;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA1Ccr0Int
 * Input	: None
 * Output	: TimerA1 CCR0 interrupt
 */
void timerA1Ccr0Int (void)
{
	varCount1_0++;
	if(varCount1_0 == 5)
	{
		ledToggle(LED_RED);
		varCount1_0 = 0;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA1Ccr1Int
 * Input	: None
 * Output	: TimerA1 CCR1 interrupt
 */
void timerA1Ccr1Int (void)
{
	  //-Rising edge-//
	  if (TA1CCTL1 & CCI)
	  {
		  TA1R = 0;
	  }
		//-Falling edge-//
	  else
	  {
		  varInterval = TA1CCR1 - 20;
		  toString(varInterval, strString);
		  txdStr(strString);
		  txdChar('\n');
	  }
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA1Ccr2Int
 * Input	: None
 * Output	: TimerA1 CCR2 interrupt
 */
void timerA1Ccr2Int (void)
{
	varCount1_2++;
	if(varCount1_2 == 5)
	{
		ledToggle(LED_GREEN);
		varCount1_2 = 0;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : timerA1TaifgInt
 * Input	: None
 * Output	: TimerA1 TAIFG interrupt
 */
void timerA1TaifgInt (void)
{
	varCount1++;
	if(varCount1 == 5)
	{
		ledToggle(LED_GREEN);
		varCount1 = 0;
	}
}


/****************************************************************************************
 *	MAIN-ROUTINE
 ***************************************************************************************/
int main (void)
{
	/* SETUP */
	//-DCO, f = 1MHz, Stop watchdog timer-//
	clkSetup(sClkSetup[0]);

	//-UART-//
	uartSetup(sUartSetup[1]);

	//-GPIO-//
	gpioSetup(sGpioSetup[1]);

	//-TimerA0-//
	psPwmSetup[0] = &sPwmSetup.sTimerA0.sA0ModeUp.sP1_2.sP1_2RstSet;
	psPwmSetup[1] = &sPwmSetup.sTimerA0.sA0ModeUp.sP1_6.sP1_6RstSet;
	psPwmSetup[2] = &sPwmSetup.sTimerA1.sA1ModeUp.sP2_1.sP2_1RstSet;
	psPwmSetup[3] = &sPwmSetup.sTimerA1.sA1ModeUp.sP2_2.sP2_2RstSet;
	timerA0Setup(sTimerASetup[0]);
	pwmSetup(*psPwmSetup[1], 1000, 0);
//	timerA0CmpSetup(sTimerACmpSetup[2]);
//	timerA0CmpSetup(sTimerACmpSetup[7]);

	//-Prepare for system-//
	ledOn(LED_RED);
	__delay_cycles(DL_2S);
	ledOff(LED_RED);

//---------------------------------------------------------------------------------------

	/* PROCESS */
	while(1)
	{
		for(varCount0 = 0; varCount0 < 255; varCount0++)
		{
			pwmSetup(*psPwmSetup[1], 1000, varCount0);
			__delay_cycles(DL_5MS);
		}
	}

//---------------------------------------------------------------------------------------

	/* FINISH */
	return 1;
}

/****************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 ***************************************************************************************/
/* RXD */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void rxdIsr (void)
{
	rxdInt();
}
//-----------------------------------------------------------------------------
/* TimerA0: CCR0 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerA0Ccr0Isr (void)
{
	timerA0Ccr0Int();
}
//-----------------------------------------------------------------------------
/* TimerA0: TA0IV */
#pragma vector = TIMER0_A1_VECTOR
__interrupt void ta0ivIsr (void)
{
	switch(__even_in_range(TA0IV,0x0A))
	{
	      case  TA0IV_NONE:
	      {
	    	  break;	// No interrupt
	      }
	      case TA0IV_TACCR1:
	      {
	    	  timerA0Ccr1Int();
	    	  break;
	      }
	      case TA0IV_TACCR2:
	      {
	    	  timerA0Ccr2Int();
	    	  break;
	      }
	      case TA0IV_TAIFG:
	      {
	    	  timerA0TaifgInt();
	    	  break;
	      }
	      default:
	      {
	    	  break;
	      }
	}
}//-----------------------------------------------------------------------------
/* TimerA1: CCR0 */
#pragma vector = TIMER1_A0_VECTOR
__interrupt void timerA1Ccr0Isr (void)
{
	timerA1Ccr0Int();
}
//-----------------------------------------------------------------------------
/* TimerA1: TA1IV */
#pragma vector = TIMER1_A1_VECTOR
__interrupt void ta1ivIsr (void)
{
	switch(__even_in_range(TA1IV,0x0A))
	{
	      case TA1IV_NONE:
	      {
	    	  break;	// No interrupt
	      }
	      case TA1IV_TACCR1:
	      {
	    	  timerA1Ccr1Int();
	    	  break;
	      }
	      case TA1IV_TACCR2:
	      {
	    	  timerA1Ccr2Int();
	    	  break;
	      }
	      case TA1IV_TAIFG:
	      {
	    	  timerA1TaifgInt();
	    	  break;
	      }
	      default:
	      {
	    	  break;
	      }
	}
}


/****************************************************************************************
 *	END OF main.c
 ***************************************************************************************/

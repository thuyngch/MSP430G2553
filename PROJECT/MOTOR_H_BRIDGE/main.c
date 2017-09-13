/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h> 
#include "VERSION 1_2_3/CLOCK_1_2_3.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"
#include "VERSION 1_2_3/TIMERA_1_2_3.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
#define		FREQUENCY			1					// 16HMZ
#define		PIN_DIRECTION		BIT7				// P1.7
#define		FORWARD				1					//
#define		BACKWARD			0					//
#define		PERIOD				1000 * FREQUENCY	// 1ms
#define		CMD_FORWARD			'1'
#define		CMD_BACKWARD		'0'


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
unsigned char varRx;
unsigned char varDirection;
unsigned int varCount0, varCount1;
unsigned char strBuff[7];


/**************************************************************************************************
 *	SUB-FUNCTIONs
 *************************************************************************************************/
void setMotorDirection (unsigned char varDirection)
{
	if(varDirection == FORWARD)
	{
		P1OUT |= PIN_DIRECTION;
	}
	if(varDirection == BACKWARD)
	{
		P1OUT &= ~ PIN_DIRECTION;
	}
}
//-------------------------------------------------------------------------------------------------
void setMotorSpeed (unsigned int varDuty)
{
	TA0CCR1 = varDuty * FREQUENCY;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	MAIN ROUTINE
 *************************************************************************************************/
void main(void)
{
	clkSetup(sClkSetup.sDco1mhz.sSwdtOn);
	gpioSetup(PORT1, LED_RED + LED_GREEN + PIN_DIRECTION, LED_RED + LED_GREEN + PIN_DIRECTION);
	uartSetup(sUartSetup.sSmclk1Mhz.sBaud115200.sIntRxdOff);

	timerASetup(sTimerASetup.sTimerA1Setup.sTimerModeUp.sTimerDiv8.sTimerIntOvfOff, 0, 0xFFFF);
	timerACapSetup(sTimerACapSetup.sTimerA1Cap.sCCR2.sP2_5.sBoth.sIntCcOn);

	while(1)
	{
		ledToggle(LED_RED);
		__delay_cycles(1000);
	}
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* TIMERA0: CCR0 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0A0Isr(void)
{
}
//-------------------------------------------------------------------------------------------------
/* TIMERA0: CCR1, CCR2, OVF */
#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer0A1Isr(void)
{
	switch (TA0IV)
	{
		case 0x02:	// CCR1
		{
			break;
		}
		case 0x04:	// CCR2
		{
			break;
		}
		case 0x0A:	// Overflow
		{
			break;
		}
		default:
		{
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/* TIMERA1: CCR0 */
#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer1A0Isr(void)
{
}
//-------------------------------------------------------------------------------------------------
/* TIMERA1: CCR1, CCR2, OVF */
#pragma vector = TIMER1_A1_VECTOR
__interrupt void timer1A1Isr(void)
{
	switch (TA1IV)
	{
		case 0x02:	// CCR1
		{
			break;
		}
		case 0x04:	// CCR2
		{
			if(TA1CCTL2 & CCI)	// Rising edge
			{
				TA1R = 0;
			}
			else				// Falling edge
			{
				sprintf((char*)strBuff, "%d", TA1CCR2);
				txdStr(strBuff);
				txdChar(ENTER);
			}
			break;
		}
		case 0x0A:	// Overflow
		{
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

#include <msp430g2553.h>
#include "VERSION 1_2_3/CLOCK_1_2_3.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_3/TIMERA_1_2_3.h"

#define		PERIOD			62500	// 62500 * 8 = 500,000 count

unsigned int varTimeOn  = 2;		// 2s for turning on
unsigned int varTimeOff = 3;		// 1s for turning off

unsigned int varTimeOnCompare  = 2 * 2;
unsigned int varTimeOffCompare = 2 * 3;

unsigned int varCount;

void main (void)
{
	clkSetup(sClkSetup.sDco1mhz.sSwdtOn);
	gpioSetup(PORT1, LED_RED, LED_RED);
	gpioIntSetup(PORT1, BUTTON, BUTTON, INT_PORT_ON);

	timerASetup(sTimerASetup.sTimerA0Setup.sTimerModeUp.sTimerDiv8.sTimerIntOvfOn, 0, PERIOD);	// Period = 500ms

	while(1);
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
	if(TA0IV & 0x0A)	// Overflow
	{
		varCount++;
		if (varCount == 1)
		{
			ledOn(LED_RED);
		}
		else if(varCount == varTimeOnCompare)
		{
			ledOff(LED_RED);
		}
		else if(varCount == varTimeOffCompare)
		{
			ledOn(LED_RED);
			varCount = 0;
		}
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR (void)
{
	varTimeOnCompare  += 2;
	varTimeOffCompare += 2;
	varCount = 0;
	TA0R     = 0;
	P1IFG &= ~ BUTTON;
}

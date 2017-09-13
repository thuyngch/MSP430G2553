#include <msp430g2553.h>
#include <stdint.h>
#include <string.h>

#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/WATCHDOG_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"

void main (void)
{
	clkSetup(CLK_DCO_1MHZ);
	wdtSetup(WDT_OFF, WDT_TIME_32MS);
	gpioSetup(PORT1, LED_RED | LED_GREEN, LED_RED | LED_GREEN);

	while(1)
	{
		gpioToggle(PORT1, LED_RED | LED_GREEN);
		__delay_cycles(DL_1S);
	}
}

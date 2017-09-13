/*
 *	File			:	CAPACITIVE_1_0_1.c
 *	Date created	:	06/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Capacitive Touch library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "CAPACITIVE_1_0_1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
 

/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	: 	
 */
void
capTouchSetup (const struct Sensor* sCapTouchButton)
{
	// Divide SMCLK by 4
//	BCSCTL2 	|=  DIVS_2;
	// LFXT1 = VLO
	BCSCTL3 	|=  LFXT1S_2;

	// Initialize Baseline measurement
	TI_CAPT_Init_Baseline(sCapTouchButton);
	// Update baseline measurement (Average 5 measurements)
	TI_CAPT_Update_Baseline(sCapTouchButton, 5);
}
 //-------------------------------------------------------------------------------------------------
 /*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	: 	
 */
uint16_t
capTouchRead (const struct Sensor* sCapTouchButton)
{
	uint16_t varDelta;
	TI_CAPT_Custom(sCapTouchButton, &varDelta);	// Get the raw delta counts
	return varDelta;
}
 //-------------------------------------------------------------------------------------------------
 /*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	: 	
 */
bool
capTouchIsPress (const struct Sensor* sCapTouchButton)
{
	return TI_CAPT_Button(sCapTouchButton);
}
 //-------------------------------------------------------------------------------------------------
 /*
 * 	Function:	capTouchSleep
 *	Purpose	:	Configures Timer A to run off ACLK, count in UP mode, places the CPU in LPM3
 * 	Input	:	varInterval: Interval of sleep
 * 	Output	: 	None
 */
void
capTouchSleep (uint16_t varInterval)
{
    TA0CCR0 	 =  varInterval;
    TA0CTL 		 =  TASSEL_1 + MC_1 + TACLR;
    TA0CCTL0 	&= ~CCIFG;
    TA0CCTL0 	|=  CCIE;
    __bis_SR_register(LPM3_bits + GIE);
    __no_operation();
}
//-------------------------------------------------------------------------------------------------
/*
* 	Function:
*	Purpose	:
* 	Input	:
* 	Output	:
*/
//-------------------------------------------------------------------------------------------------
/*
* 	Function:
*	Purpose	:
* 	Input	:
* 	Output	:
*/
//-------------------------------------------------------------------------------------------------
/*
* 	Function:
*	Purpose	:
* 	Input	:
* 	Output	:
*/
 //-------------------------------------------------------------------------------------------------
 /*
 * 	Function:	ISR_Timer0_A0
 *	Purpose	:	Disables the timer and exists LPM3
 * 	Input	:	None
 * 	Output	: 	None
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void ISR_Timer0_A0 (void)
{
	TA0CTL 		&= ~MC_1;
	TA0CCTL0 	&= ~CCIE;
	varIsHall 	 = false;
//	__bic_SR_register_on_exit(LPM3_bits + GIE);
}
//-------------------------------------------------------------------------------------------------
 

/**************************************************************************************************
 *	END OF WATCHDOG_1_0_1.c
 *************************************************************************************************/

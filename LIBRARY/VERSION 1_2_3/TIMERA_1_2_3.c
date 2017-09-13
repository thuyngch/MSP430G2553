/*
 * 	File			:	TIMERA_1_2_3.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	03/06/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.2.1
 *	Description		:	Construct TimerA library
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "TIMERA_1_2_3.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
volatile extern timer_A_Setup sTimerASetup =
{
	{// TimerA0
			{// Mode up
					{// ID_0
							{TIMER_A_0, MODE_UP, ID_0, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UP, ID_0, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_1
							{TIMER_A_0, MODE_UP, ID_1, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UP, ID_1, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_2
							{TIMER_A_0, MODE_UP, ID_2, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UP, ID_2, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_3
							{TIMER_A_0, MODE_UP, ID_3, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UP, ID_3, INT_OVF_OFF},// INT_OVF_OFF
					},
			},
			{// Mode continuous
					{// ID_0
							{TIMER_A_0, MODE_CONTI, ID_0, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_CONTI, ID_0, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_1
							{TIMER_A_0, MODE_CONTI, ID_1, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_CONTI, ID_1, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_2
							{TIMER_A_0, MODE_CONTI, ID_2, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_CONTI, ID_2, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_3
							{TIMER_A_0, MODE_CONTI, ID_3, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_CONTI, ID_3, INT_OVF_OFF},// INT_OVF_OFF
					},
			},
			{// Mode up down
					{// ID_0
							{TIMER_A_0, MODE_UPDOWN, ID_0, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UPDOWN, ID_0, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_1
							{TIMER_A_0, MODE_UPDOWN, ID_1, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UPDOWN, ID_1, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_2
							{TIMER_A_0, MODE_UPDOWN, ID_2, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UPDOWN, ID_2, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_3
							{TIMER_A_0, MODE_UPDOWN, ID_3, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_0, MODE_UPDOWN, ID_3, INT_OVF_OFF},// INT_OVF_OFF
					},
			},
	},
	{// TimerA1
			{// Mode up
					{// ID_0
							{TIMER_A_1, MODE_UP, ID_0, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UP, ID_0, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_1
							{TIMER_A_1, MODE_UP, ID_1, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UP, ID_1, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_2
							{TIMER_A_1, MODE_UP, ID_2, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UP, ID_2, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_3
							{TIMER_A_1, MODE_UP, ID_3, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UP, ID_3, INT_OVF_OFF},// INT_OVF_OFF
					},
			},
			{// Mode continuous
					{// ID_0
							{TIMER_A_1, MODE_CONTI, ID_0, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_CONTI, ID_0, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_1
							{TIMER_A_1, MODE_CONTI, ID_1, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_CONTI, ID_1, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_2
							{TIMER_A_1, MODE_CONTI, ID_2, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_CONTI, ID_2, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_3
							{TIMER_A_1, MODE_CONTI, ID_3, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_CONTI, ID_3, INT_OVF_OFF},// INT_OVF_OFF
					},
			},
			{// Mode up down
					{// ID_0
							{TIMER_A_1, MODE_UPDOWN, ID_0, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UPDOWN, ID_0, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_1
							{TIMER_A_1, MODE_UPDOWN, ID_1, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UPDOWN, ID_1, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_2
							{TIMER_A_1, MODE_UPDOWN, ID_2, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UPDOWN, ID_2, INT_OVF_OFF},// INT_OVF_OFF
					},
					{// ID_3
							{TIMER_A_1, MODE_UPDOWN, ID_3, INT_OVF_ON},	// INT_OVF_ON
							{TIMER_A_1, MODE_UPDOWN, ID_3, INT_OVF_OFF},// INT_OVF_OFF
					},
			},
	}
};

//-------------------------------------------------------------------------------------------------
volatile extern timer_A_Cap_Setup sTimerACapSetup =
{
	{// TimerA0
			{// CCR0
					{// P1_1
							{// Rising
									{TIMER_A_0, CCR_0, CHANNEL_A, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_0, CCR_0, CHANNEL_A, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_0, CCR_0, CHANNEL_A, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_0, CCR_0, CHANNEL_A, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_0, CCR_0, CHANNEL_A, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_0, CCR_0, CHANNEL_A, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
			},
			{// CCR1
					{// P1_2
							{// Rising
									{TIMER_A_0, CCR_1, CHANNEL_A, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_0, CCR_1, CHANNEL_A, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_0, CCR_1, CHANNEL_A, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_0, CCR_1, CHANNEL_A, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_0, CCR_1, CHANNEL_A, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_0, CCR_1, CHANNEL_A, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
			},
	},
	{// TimerA1
			{// CCR0
					{// P2_0
							{// Rising
									{TIMER_A_1, CCR_0, CHANNEL_A, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_0, CHANNEL_A, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_1, CCR_0, CHANNEL_A, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_0, CHANNEL_A, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_1, CCR_0, CHANNEL_A, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_1, CCR_0, CHANNEL_A, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
					{// P2_3
							{// Rising
									{TIMER_A_1, CCR_0, CHANNEL_B, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_0, CHANNEL_B, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_1, CCR_0, CHANNEL_B, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_0, CHANNEL_B, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_1, CCR_0, CHANNEL_B, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_1, CCR_0, CHANNEL_B, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
			},
			{// CCR1
					{// P2_1
							{// Rising
									{TIMER_A_1, CCR_1, CHANNEL_A, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_1, CHANNEL_A, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_1, CCR_1, CHANNEL_A, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_1, CHANNEL_A, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_1, CCR_1, CHANNEL_A, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_1, CCR_1, CHANNEL_A, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
					{// P2_2
							{// Rising
									{TIMER_A_1, CCR_1, CHANNEL_B, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_1, CHANNEL_B, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_1, CCR_1, CHANNEL_B, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_1, CHANNEL_B, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_1, CCR_1, CHANNEL_B, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_1, CCR_1, CHANNEL_B, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
			},
			{// CCR2
					{// P2_4
							{// Rising
									{TIMER_A_1, CCR_2, CHANNEL_A, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_2, CHANNEL_A, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_1, CCR_2, CHANNEL_A, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_2, CHANNEL_A, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_1, CCR_2, CHANNEL_A, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_1, CCR_2, CHANNEL_A, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
					{// P2_5
							{// Rising
									{TIMER_A_1, CCR_2, CHANNEL_B, CAP_RISING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_2, CHANNEL_B, CAP_RISING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Falling
									{TIMER_A_1, CCR_2, CHANNEL_B, CAP_FALLING, INT_CC_ON},	// INT_CC_ON
									{TIMER_A_1, CCR_2, CHANNEL_B, CAP_FALLING, INT_CC_OFF},	// INT_CC_OFF
							},
							{// Both
									{TIMER_A_1, CCR_2, CHANNEL_B, CAP_BOTH, INT_CC_ON},		// INT_CC_ON
									{TIMER_A_1, CCR_2, CHANNEL_B, CAP_BOTH, INT_CC_OFF},	// INT_CC_OFF
							},
					},
			},
	},
};

//-------------------------------------------------------------------------------------------------
volatile extern timer_A_Cmp_Setup sTimerACmpSetup =
{
	{// TimerA0
			{// CCR0
					{TIMER_A_0, CCR_0, INT_CC_ON},	// INT_ON
					{TIMER_A_0, CCR_0, INT_CC_OFF},	// INT_OFF
			},
			{// CCR1
					{TIMER_A_0, CCR_1, INT_CC_ON},	// INT_ON
					{TIMER_A_0, CCR_1, INT_CC_OFF},	// INT_OFF
			},
			{// CCR2
					{TIMER_A_0, CCR_2, INT_CC_ON},	// INT_ON
					{TIMER_A_0, CCR_2, INT_CC_OFF},	// INT_OFF
			},
	},
	{// TimerA1
			{// CCR0
					{TIMER_A_1, CCR_0, INT_CC_ON},	// INT_ON
					{TIMER_A_1, CCR_0, INT_CC_OFF},	// INT_OFF
			},
			{// CCR1
					{TIMER_A_1, CCR_1, INT_CC_ON},	// INT_ON
					{TIMER_A_1, CCR_1, INT_CC_OFF},	// INT_OFF
			},
			{// CCR2
					{TIMER_A_1, CCR_2, INT_CC_ON},	// INT_ON
					{TIMER_A_1, CCR_2, INT_CC_OFF},	// INT_OFF
			},
	}
};

//-------------------------------------------------------------------------------------------------
volatile extern pwm_Setup sPwmSetup =
{
	{// TimerA0
			{// ModeUp
					{// P1.2
							{TIMER_A_0, MODE_UP, P1_2, PWM_TG_RST},	// Toggle/Reset
							{TIMER_A_0, MODE_UP, P1_2, PWM_SET_RST},// Set/Reset
							{TIMER_A_0, MODE_UP, P1_2, PWM_TG_SET},	// Toggle/Set
							{TIMER_A_0, MODE_UP, P1_2, PWM_RST_SET}	// Reset/Set
					},
					{// P1.6
							{TIMER_A_0, MODE_UP, P1_6, PWM_TG_RST},	// Toggle/Reset
							{TIMER_A_0, MODE_UP, P1_6, PWM_SET_RST},// Set/Reset
							{TIMER_A_0, MODE_UP, P1_6, PWM_TG_SET},	// Toggle/Set
							{TIMER_A_0, MODE_UP, P1_6, PWM_RST_SET}	// Reset/Set
					}
			}
	},
	{// TimerA1
			{// ModeUp
					{// P2.1
							{TIMER_A_1, MODE_UP, P2_1, PWM_TG_RST},	// Toggle/Reset
							{TIMER_A_1, MODE_UP, P2_1, PWM_SET_RST},// Set/Reset
							{TIMER_A_1, MODE_UP, P2_1, PWM_TG_SET},	// Toggle/Set
							{TIMER_A_1, MODE_UP, P2_1, PWM_RST_SET}	// Reset/Set
					},
					{// P2.2
							{TIMER_A_1, MODE_UP, P2_2, PWM_TG_RST},	// Toggle/Reset
							{TIMER_A_1, MODE_UP, P2_2, PWM_SET_RST},// Set/Reset
							{TIMER_A_1, MODE_UP, P2_2, PWM_TG_SET},	// Toggle/Set
							{TIMER_A_1, MODE_UP, P2_2, PWM_RST_SET}	// Reset/Set
					}
			}
	}
};
 

/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * Function : timerASetup
 * Input	: Struct with type of timer_A_Setup
 * Output	: Setup TimerA
 */
void timerASetup (timer_Int sTimerASetup_, unsigned int varTarInit, unsigned int varCcr0Init)
{
	if(sTimerASetup_.TIMER_A_ == TIMER_A_0)
	{
		TA0CTL = TASSEL_2 + sTimerASetup_.MODE_ + sTimerASetup_.DIV_ + sTimerASetup_.INT_OVF_;
		TA0R = varTarInit;
		TA0CCR0 = varCcr0Init;			// Used in Up mode and Up/Down mode
		if (sTimerASetup_.INT_OVF_ == INT_OVF_ON)
		{
			__bis_SR_register(GIE);
		}
	}
	if(sTimerASetup_.TIMER_A_ == TIMER_A_1)
	{
		TA1CTL = TASSEL_2 + sTimerASetup_.MODE_ + sTimerASetup_.DIV_ + sTimerASetup_.INT_OVF_;
		TA1R = varTarInit;
		TA1CCR0 = varCcr0Init;			// Used in Up mode and Up/Down mode
		if (sTimerASetup_.INT_OVF_ == INT_OVF_ON)
		{
			__bis_SR_register(GIE);
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : 	timerASetup
 * Purpose	:	Stop timerA operation
 * Input	:	TIMER_A_0 or TIMER_A_1
 * Output	: 	None
 */
void timerAStop (const char TIMER_A_)
{
	if(TIMER_A_ == TIMER_A_0)
	{
		TA0CTL &= 0xFFCF;
	}
	if(TIMER_A_ == TIMER_A_1)
	{
		TA1CTL &= 0xFFCF;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function :	timerACapSetup
 * Purpose	:	Setup timerA Capture
 * Input	:	Struct inside struct
 * Output	:	None
 */
void timerACapSetup (timer_A_Cap_Int sTimerACapSetup_)
{
	if(sTimerACapSetup_.TIMER_A_ == TIMER_A_0)
	{
		if(sTimerACapSetup_.CCR_ == CCR_0)
		{
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_A)
			{
				P1SEL   |=  BIT1;
				P1SEL2  &= ~BIT1;
				P1DIR   &= ~BIT1;
				TA0CCTL0 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA0R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA0CCTL0 &= ~COV;
			}
		}
		if(sTimerACapSetup_.CCR_ == CCR_1)
		{
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_A)
			{
				P1SEL   |=  BIT2;
				P1SEL2  &= ~BIT2;
				P1DIR   &= ~BIT2;
				TA0CCTL1 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA0R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA0CCTL1 &= ~COV;
			}
		}
	}
	if(sTimerACapSetup_.TIMER_A_ == TIMER_A_1)
	{
		if(sTimerACapSetup_.CCR_ == CCR_0)
		{
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_A)
			{
				P2SEL   |=  BIT0;
				P2SEL2  &= ~BIT0;
				P2DIR   &= ~BIT0;
				TA1CCTL0 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA1R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA1CCTL0 &= ~COV;
			}
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_B)
			{
				P2SEL   |=  BIT3;
				P2SEL2  &= ~BIT3;
				P2DIR   &= ~BIT3;
				TA1CCTL0 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA1R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA1CCTL0 &= ~COV;
			}
		}
		if(sTimerACapSetup_.CCR_ == CCR_1)
		{
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_A)
			{
				P2SEL   |=  BIT1;
				P2SEL2  &= ~BIT1;
				P2DIR   &= ~BIT1;
				TA1CCTL1 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA1R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA1CCTL1 &= ~COV;
			}
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_B)
			{
				P2SEL   |=  BIT2;
				P2SEL2  &= ~BIT2;
				P2DIR   &= ~BIT2;
				TA1CCTL1 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA1R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA1CCTL1 &= ~COV;
			}
		}
		if(sTimerACapSetup_.CCR_ == CCR_2)
		{
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_A)
			{
				P2SEL   |=  BIT4;
				P2SEL2  &= ~BIT4;
				P2DIR   &= ~BIT4;
				TA1CCTL2 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA1R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA1CCTL2 &= ~COV;
			}
			if(sTimerACapSetup_.CHANNEL_ == CHANNEL_B)
			{
				P2SEL   |=  BIT5;
				P2SEL2  &= ~BIT5;
				P2DIR   &= ~BIT5;
				TA1CCTL2 = CAPTURE + sTimerACapSetup_.MODE_ + sTimerACapSetup_.CHANNEL_ + sTimerACapSetup_.INT_CC_;
				TA1R = 0;
				if(sTimerACapSetup_.INT_CC_ == INT_CC_ON)
				{
					__bis_SR_register(GIE);
				}
				TA1CCTL2 &= ~COV;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function :	timerACmpSetup
 * Purpose	:	Setup timerA Compare
 * Input	: 	Struct inside struct
 * Output	: 	None
 */
void timerACmpSetup (timer_A_Cmp_Int sTimerACmpSetup_, unsigned int varCcrInit)
{
	if(sTimerACmpSetup_.TIMER_A_ == TIMER_A_0)
	{
		if(sTimerACmpSetup_.CCR_ == CCR_0)
		{
			TA0CCTL0 = sTimerACmpSetup_.INT_CC_;
			TA0CCR0 = varCcrInit;
			if(sTimerACmpSetup_.INT_CC_ == INT_CC_ON)
			{
				__bis_SR_register(GIE);
			}
		}
		if(sTimerACmpSetup_.CCR_ == CCR_1)
		{
			TA0CCTL1 = sTimerACmpSetup_.INT_CC_;
			TA0CCR1 = varCcrInit;
			if(sTimerACmpSetup_.INT_CC_ == INT_CC_ON)
			{
				__bis_SR_register(GIE);
			}
		}
		if(sTimerACmpSetup_.CCR_ == CCR_2)
		{
			TA0CCTL2 = sTimerACmpSetup_.INT_CC_;
			TA0CCR2 = varCcrInit;
			if(sTimerACmpSetup_.INT_CC_ == INT_CC_ON)
			{
				__bis_SR_register(GIE);
			}
		}
	}
	if(sTimerACmpSetup_.TIMER_A_ == TIMER_A_1)
	{
		if(sTimerACmpSetup_.CCR_ == CCR_0)
		{
			TA1CCTL0 = sTimerACmpSetup_.INT_CC_;
			TA1CCR0 = varCcrInit;
			if(sTimerACmpSetup_.INT_CC_ == INT_CC_ON)
			{
				__bis_SR_register(GIE);
			}
		}
		if(sTimerACmpSetup_.CCR_ == CCR_1)
		{
			TA1CCTL1 = sTimerACmpSetup_.INT_CC_;
			TA1CCR1 = varCcrInit;
			if(sTimerACmpSetup_.INT_CC_ == INT_CC_ON)
			{
				__bis_SR_register(GIE);
			}
		}
		if(sTimerACmpSetup_.CCR_ == CCR_2)
		{
			TA1CCTL2 = sTimerACmpSetup_.INT_CC_;
			TA1CCR2 = varCcrInit;
			if(sTimerACmpSetup_.INT_CC_ == INT_CC_ON)
			{
				__bis_SR_register(GIE);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function : pwmSetup
 * Input	: Struct with type of pwm_Setup
 * Output	: Setup PWM module of TimerA
 */
void pwmSetup (pwm_Out sPwmSetup_, unsigned int varPeriod, unsigned int varDuty)
{
	if(sPwmSetup_.TIMER_A_ == TIMER_A_0)
	{
		if(sPwmSetup_.MODE_ == MODE_UP)		// Output: P1.2 & P1.6
		{
			P1DIR |= sPwmSetup_.PIN_;
			P1SEL |= sPwmSetup_.PIN_;
			P1SEL2 &= ~sPwmSetup_.PIN_;
			TA0CCTL1 = sPwmSetup_.PWM_;
			TA0CCR0 = varPeriod;
			if((sPwmSetup_.PWM_ == PWM_TG_RST) || (sPwmSetup_.PWM_ == PWM_SET_RST))	//Mode 2 & 3
			{
				TA0CCR1 = varPeriod - varDuty;
			}
			if((sPwmSetup_.PWM_ == PWM_TG_SET) || (sPwmSetup_.PWM_ == PWM_RST_SET))	//Mode 6 & 7
			{
				TA0CCR1 = varDuty;
			}
		}
	}
	if(sPwmSetup_.TIMER_A_ == TIMER_A_1)
	{
		if(sPwmSetup_.MODE_ == MODE_UP)		// Output: P2.1 & P2.2
		{
			P2DIR |= sPwmSetup_.PIN_;
			P2SEL |= sPwmSetup_.PIN_;
			P2SEL2 &= ~sPwmSetup_.PIN_;
			TA1CCTL1 = sPwmSetup_.PWM_;
			TA1CCR0 = varPeriod;
			if((sPwmSetup_.PWM_ == PWM_TG_RST) || (sPwmSetup_.PWM_ == PWM_SET_RST))	//Mode 2 & 3
			{
				TA1CCR1 = varPeriod - varDuty;
			}
			if((sPwmSetup_.PWM_ == PWM_TG_SET) || (sPwmSetup_.PWM_ == PWM_RST_SET))	//Mode 6 & 7
			{
				TA1CCR1 = varDuty;
			}
		}
	}
}


/****************************************************************************************
 *	END OF TIMERA_1_2_3.c
 ***************************************************************************************/

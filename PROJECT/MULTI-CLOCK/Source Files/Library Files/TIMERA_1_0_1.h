/*
 * 	File			:	TIMERA_1_0_1.h
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	03/06/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct TimerA library
 */
#ifndef TIMERA_1_0_1_H_
#define TIMERA_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* TimerA */
#define		TIMER_A_0			0			// TimerA0
#define		TIMER_A_1			1			// TimerA1

//-------------------------------------------------------------------------------------------------
/* Timer modes */
#define		MODE_UP				MC_1		// Up mode
#define		MODE_CONTI			MC_2		// Continuous mode
#define		MODE_UPDOWN			MC_3		// Up/down mode

//-------------------------------------------------------------------------------------------------
/* Overflow interrupt */
#define		INT_OVF_OFF			0			// Disable Overflow interrupt
#define		INT_OVF_ON			TAIE		// Enable Overflow interrupt

//-------------------------------------------------------------------------------------------------
/* Capture/Compare */
#define		CAPTURE				CAP			// Capture
#define		COMPARE				0			// Compare

//-------------------------------------------------------------------------------------------------
/* Modules of Capture and Compare */
#define		CCR_0				0			// TimerAx_A0
#define		CCR_1				1			// TimerAx_A1
#define		CCR_2				2			// TimerAx_A2

//-------------------------------------------------------------------------------------------------
/* Capture modes */
#define		CAP_OFF				CM_0		// No capture
#define		CAP_RISING			CM_1		// Capture in rising edge
#define		CAP_FALLING			CM_2		// Capture in falling edge
#define		CAP_BOTH			CM_3		// Capture in both edges

//-------------------------------------------------------------------------------------------------
/* Channels of Capture */
#define		CHANNEL_A			CCIS_0		// Channel A
#define		CHANNEL_B			CCIS_1		// Channel B
#define		CHANNEL_GND			CCIS_2		// Channel GND
#define		CHANNEL_VCC			CCIS_3		// Channel VCC

//-------------------------------------------------------------------------------------------------
/* Outmodes */
#define		PWM_OUTBIT			OUTMOD_0	// OUT bit value
#define		PWM_SET				OUTMOD_1	// Set
#define		PWM_TG_RST			OUTMOD_2	// Toggle/Reset
#define		PWM_SET_RST			OUTMOD_3	// Set/Reset
#define		PWM_TG				OUTMOD_4	// Toggle
#define		PWM_RST				OUTMOD_5	// Reset
#define		PWM_TG_SET			OUTMOD_6	// Toggle/Set
#define		PWM_RST_SET			OUTMOD_7	// Reset/Set

//-------------------------------------------------------------------------------------------------
/* Output pins */
#define		P1_2				BIT2		// P1.2
#define		P1_6				BIT6		// P1.6
#define		P2_1				BIT1		// P2.1
#define		P2_2				BIT2		// P2.2

//-------------------------------------------------------------------------------------------------
/* Capture/Compare interrupt */
#define		INT_CC_ON			CCIE		// Enable Capture/Compare interrupt
#define		INT_CC_OFF			0			// Disable Capture/Compare interrupt


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
 /* Setup */
void timerASetup (const unsigned int TIMER_A_, const unsigned int MODE_, const unsigned int DIV_,
		const unsigned int INT_OVF_, unsigned int varTarInit, unsigned int varCcr0Init);

void timerAStop (const char TIMER_A_);

void timerACapSetup (const unsigned int TIMER_A_, const unsigned int CCR_,
		const unsigned int CHANNEL_, const unsigned int MODE_, const unsigned int INT_CC_);
	// CCR0 is not used for ModeUp & ModeUpDown

void timerACmpSetup (const unsigned int TIMER_A_, const unsigned int CCR_,
		const unsigned int INT_CC_, unsigned int varCcrInit);

void pwmSetup (const unsigned int TIMER_A_, const unsigned int MODE_,
		const unsigned int PIN_, const unsigned int PWM_,
		unsigned int varPeriod, unsigned int varDuty);


/**************************************************************************************************
 *	END OF TIMERA_1_0_1.h
 *************************************************************************************************/
#endif /* TIMERA_1_0_1_H_ */

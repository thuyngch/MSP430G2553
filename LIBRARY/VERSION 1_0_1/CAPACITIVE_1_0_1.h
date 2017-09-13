/*
 *	File			:	CAPACITIVE_1_0_1.h
 *	Date created	:	06/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Capacitive Touch library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef CAPACITIVE_1_0_1_H_
#define CAPACITIVE_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdint.h>
#include <stdbool.h>

/* Producing Library */
#include <msp430g2553.h>
#include "Capacitive Touch/CTS_Layer.h"

/* My Library */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void
capTouchSetup 		(const struct Sensor* sCapTouchButton);

/* Read */
uint16_t
capTouchRead		(const struct Sensor* sCapTouchButton);
bool
capTouchIsPress		(const struct Sensor* sCapTouchButton);

/* Control */
void
capTouchSleep		(uint16_t varInterval);

/* Implicit ISR */
__interrupt void
ISR_Timer0_A0 		(void);


/**************************************************************************************************
 *	END OF CAPACITIVE_1_0_1.h
 *************************************************************************************************/
#endif /* CAPACITIVE_1_0_1_H_ */

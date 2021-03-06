/*
 *	File			:	Setup.c
 *	Date created	:	22/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Source for Setup
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "Header.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void stateSetup (void)
{
	varState = STATE_STOP_PUMP;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void sensorSetup (void)
{
	gpioSetup(PORT1, SENSOR1 + SENSOR2, 0);
	gpioIntSetup(PORT1, SENSOR1 + SENSOR2, SENSOR1 + SENSOR2, INT_PORT_OFF);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void motorSetup (void)
{
	gpioSetup(PORT1, MOTOR, MOTOR);
	gpioLow(PORT1, MOTOR);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void systemSetup (void)
{
	stateSetup();
	sensorSetup();
	motorSetup();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Setup.c
 *************************************************************************************************/

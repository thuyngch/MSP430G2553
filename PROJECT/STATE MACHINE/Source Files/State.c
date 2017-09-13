/*
 *	File			:	State.c
 *	Date created	:	22/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Source for State
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "Header.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
extern volatile state varState = STATE_STOP_PUMP;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************//*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void stateUpdate (void)
{
	switch (varState)
	{
		case STATE_STOP_PUMP:
			if(sensorState() == SENSOR_UNDER)
			{
				varState = STATE_PUMP;
			}
			break;
		case STATE_PUMP:
			if(sensorState() == SENSOR_OVER)
			{
				varState = STATE_STOP_PUMP;
			}
			break;
	}
	switch (varState)
	{
		case STATE_STOP_PUMP:
			motorControl(MOTOR_OFF);
			break;
		case STATE_PUMP:
			motorControl(MOTOR_ON);
			break;
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF State.c
 *************************************************************************************************/

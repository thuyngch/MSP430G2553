/*
 *	File			:	KEYPAD.c
 *	Date created	:	10/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Source for keypad
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "main.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
extern volatile unsigned char varCount = 0;
extern volatile unsigned char arrOut[4] = {0xEF, 0xDF, 0xBF, 0x7F};


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	keypadButtonIdentify
 *	Purpose	:	Identify what button is press
 * 	Input	:	None
 * 	Output	:
 */
void keypadButtonIdentify (unsigned char regPortIfg)
{
	switch (regPortIfg & PIN_KEYPAD_IN)
	{
		case PIN_KEYPAD_IN_1:
		{
			switch (varCount)
			{
				case 0:					// [1]
				{
					keypadSetRegSttNum(1);
					break;
				}
				case 1:					// [2]
				{
					keypadSetRegSttNum(2);
					break;
				}
				case 2:					// [3]
				{
					keypadSetRegSttNum(3);
					break;
				}
				case 3:					// [A]
				{
					keypadSetRegSttMode('A');
					break;
				}
				default:
				{
					// Check error at here
					break;
				}
			}
			break;
		}
		case PIN_KEYPAD_IN_2:
		{
			switch (varCount)
			{
				case 0:					// [4]
				{
					keypadSetRegSttNum(4);
					break;
				}
				case 1:					// [5]
				{
					keypadSetRegSttNum(5);
					break;
				}
				case 2:					// [6]
				{
					keypadSetRegSttNum(6);
					break;
				}
				case 3:					// [B]
				{
					keypadSetRegSttMode('B');
					break;
				}
				default:
				{
					// Check error at here
					break;
				}
			}
			break;
		}
		case PIN_KEYPAD_IN_3:
		{
			switch (varCount)
			{
				case 0:					// [7]
				{
					keypadSetRegSttNum(7);
					break;
				}
				case 1:					// [8]
				{
					keypadSetRegSttNum(8);
					break;
				}
				case 2:					// [9]
				{
					keypadSetRegSttNum(9);
					break;
				}
				case 3:					// [C]
				{
					keypadSetRegSttMode('C');
					break;
				}
				default:
				{
					// Check error at here
					break;
				}
			}
			break;
		}
		case PIN_KEYPAD_IN_4:
		{
			switch (varCount)
			{
				case 0:					// [*]
				{
					keypadSetRegSttControl('*');
					break;
				}
				case 1:					// [0]
				{
					keypadSetRegSttNum(0);
					break;
				}
				case 2:					// [#]
				{
					keypadSetRegSttControl('#');
					break;
				}
				case 3:					// [D]
				{
					keypadSetRegSttMode('D');
					break;
				}
				default:
				{
					// Check error at here
					break;
				}
			}
			break;
		}
		default:
		{
			// Check error at here
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void keypadSetRegSttMode (unsigned char varMode)
{
	if((varMode == 'A') || (varMode == 'B') || (varMode == 'C'))	// Sellect
	{
		regFirmStatus |=  FIRM_STT_MODE_SEL;
		switch (varMode)
		{
			case 'A':
				regFirmStatus &= ~FIRM_STT_MODE_SEL_ALL;
				regFirmStatus |=  FIRM_STT_MODE_SEL_A;
				regFirmTimeOn  =  regFirmTimeOnA;
				regFirmTimeOff =  regFirmTimeOffA;
				break;
			case 'B':
				regFirmStatus &= ~FIRM_STT_MODE_SEL_ALL;
				regFirmStatus |=  FIRM_STT_MODE_SEL_B;
				regFirmTimeOn  =  regFirmTimeOnB;
				regFirmTimeOff =  regFirmTimeOffB;
				break;
			case 'C':
				regFirmStatus &= ~FIRM_STT_MODE_SEL_ALL;
				regFirmStatus |=  FIRM_STT_MODE_SEL_C;
				regFirmTimeOn  =  regFirmTimeOnC;
				regFirmTimeOff =  regFirmTimeOffC;
				break;
		}
		regFirmStatus |=  FIRM_STT_PERIOD;
		regFirmStatus |=  FIRM_STT_OLD_VALUE;
		regFirmStatus &= ~FIRM_STT_EXIT_SEL;
		varFirmMode    =  varMode;
		varFirmNum	   =  mathBcdUnit(regFirmTimeOn);
	}
	if(varMode == 'D')												// Exit
	{
		regFirmStatus  = FIRM_STT_EXIT_SEL;
		varFirmMode    = varMode;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void keypadSetRegSttControl (unsigned char varControl)
{
	if(varControl == '*')	// Clear
	{
		regFirmStatus |=  FIRM_STT_CLEAR;
		regFirmStatus &= ~FIRM_STT_CONFIRM;
		regFirmStatus &= ~FIRM_STT_GET_NUM;
	}
	if(varControl == '#')	// Confirm
	{
		regFirmStatus |=  FIRM_STT_CONFIRM;
		regFirmStatus &= ~FIRM_STT_CLEAR;
		regFirmStatus &= ~FIRM_STT_GET_NUM;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void keypadSetRegSttNum (unsigned char varNum)
{
	regFirmStatus |=  FIRM_STT_GET_NUM;
	regFirmStatus &= ~FIRM_STT_CLEAR;
	regFirmStatus &= ~FIRM_STT_CONFIRM;
	varFirmNum = varNum;
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


/**************************************************************************************************
 *	END OF KEYPAD.c
 *************************************************************************************************/

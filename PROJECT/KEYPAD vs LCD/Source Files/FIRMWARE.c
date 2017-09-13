/*
 *	File			:	Firmware.c
 *	Date created	:	10/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Source for firmware
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "main.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
extern volatile unsigned int 	regFirmStatus 	= 0;		// Firmware status register
extern volatile unsigned int 	regFirmOvf 		= 0;		// Firmware overflow register

extern volatile unsigned int 	regFirmTimeOn 	= 0;		// Firmware period data register
extern volatile unsigned int 	regFirmTimeOff	= 0;		// Firmware duty data register
extern volatile unsigned int 	regFirmTimeOnA	= 0;		// Firmware period data of mode A register
extern volatile unsigned int 	regFirmTimeOffA	= 0;		// Firmware duty data of mode A register
extern volatile unsigned int 	regFirmTimeOnB	= 0;		// Firmware period data of mode B register
extern volatile unsigned int 	regFirmTimeOffB	= 0;		// Firmware duty data of mode B register
extern volatile unsigned int 	regFirmTimeOnC	= 0;		// Firmware period data of mode C register
extern volatile unsigned int 	regFirmTimeOffC	= 0;		// Firmware duty data of mode C register

extern volatile unsigned int 	regFirmEnalbe 	= 0;		// Firmware enable register
extern volatile unsigned char 	varFirmNum 		= 0;		// Stores gotten number from keypad
extern volatile unsigned char 	varFirmMode 	= 0;		// Stores gotten mode from keypad


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareSetup (void)
{
	flashReadBlock(FLASH_SEGMENT, (unsigned char*)arrCommunication, FLASH_ADDR_INIT_A, FLASH_NUM_BYTE);
	communicationDecode(FIRM_STT_MODE_SEL_A);
	flashReadBlock(FLASH_SEGMENT, (unsigned char*)arrCommunication, FLASH_ADDR_INIT_B, FLASH_NUM_BYTE);
	communicationDecode(FIRM_STT_MODE_SEL_B);
	flashReadBlock(FLASH_SEGMENT, (unsigned char*)arrCommunication, FLASH_ADDR_INIT_C, FLASH_NUM_BYTE);
	communicationDecode(FIRM_STT_MODE_SEL_C);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	firmConfirm
 *	Purpose	:	Implement confirm command
 * 	Input	:	None
 * 	Output	:	None
 */
void firmwareConfirm (void)
{
	communicationEncode();			// Encode data for communication
	communicationTransmit();		// Transmit data
#ifdef USE_LCD
	lcdNotifyConfirm();				// Notify in LCD
#elif USE_LED_7SEG
	led7segNotifyConfirm();			// Notify in LED 7-segment
#endif
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareClearTempValue (unsigned int varPeDu)
{
	varFirmNum = 0;
	regFirmStatus &= ~FIRM_STT_DIGIT;
	regFirmStatus &= ~FIRM_STT_GET_NUM;
	regFirmStatus &= ~FIRM_STT_CONFIRM;
#ifdef USE_LCD
	lcdNotifyMode(varFirmMode);
#elif USE_LED_7SEG
	__delay_cycles(1);						// Reserved
#endif
	if(varPeDu == FIRM_STT_PERIOD)
	{
		regFirmTimeOn = 0;
#ifdef USE_LCD
			LCD_Goto(2, 2);
			LCD_PrintString("Period=");
#elif USE_LED_7SEG
			__delay_cycles(1);				// Reserved
#endif
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
		regFirmTimeOff = 0;
#ifdef USE_LCD
		LCD_Goto(2, 2);
		LCD_PrintString("Duty=");
#elif USE_LED_7SEG
		__delay_cycles(1);					// Reserved
#endif
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareNullValue (unsigned int varPeDu)
{
	regFirmStatus &= ~FIRM_STT_GET_NUM;
	regFirmStatus &= ~FIRM_STT_DIGIT;
#ifdef USE_LCD
	lcdNotifyNullValue(varPeDu);				// Notify in LCD
#elif USE_LED_7SEG
	led7segNotifyError();						// Notify in LED 7-segment
#endif
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareExit (void)
{
	regFirmStatus = FIRM_STT_EXIT_SEL;
	regFirmOvf = 0;
	regFirmTimeOn = 0;
	regFirmTimeOff = 0;
	varFirmMode = 0;
	varFirmNum = 0;
#ifdef USE_LCD
	lcdNotifyExit();
#elif USE_LED_7SEG
	led7segNotifyExit();
#endif
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareConfirmNextValue (void)
{
	if(regFirmTimeOn != 0)			// Period is not equal 0 -> Pass to Duty
	{
		regFirmStatus &= ~FIRM_STT_GET_NUM;
		regFirmStatus &= ~FIRM_STT_CONFIRM;
		regFirmStatus &= ~FIRM_STT_DIGIT;
		regFirmStatus &= ~FIRM_STT_PERIOD;
		regFirmStatus |=  FIRM_STT_DUTY;
		regFirmStatus |=  FIRM_STT_OLD_VALUE;
#ifdef USE_LCD
		lcdNotifyMode(varFirmMode);
#elif USE_LED_7SEG
		__delay_cycles(1);			// Reserved
#endif
	}
	else		// Notify error (Period == 0) at here and request reinputting
	{
		firmwareNullValue(FIRM_STT_PERIOD);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareConfirmAllValue (void)
{
	if(regFirmTimeOff != 0)			// Duty is not equal 0 -> Pass to next task
	{
		if(regFirmTimeOn > regFirmTimeOff)		// Period > Duty ---> Pass
		{
			switch (varFirmMode)
			{
				case 'A':
					regFirmTimeOnA  = regFirmTimeOn;
					regFirmTimeOffA = regFirmTimeOff;
					communicationEncode();
					flashWriteBlock(FLASH_SEGMENT, (unsigned char*)arrCommunication, FLASH_ADDR_INIT_A, FLASH_NUM_BYTE);
					break;
				case 'B':
					regFirmTimeOnB  = regFirmTimeOn;
					regFirmTimeOffB = regFirmTimeOff;
					communicationEncode();
					flashWriteBlock(FLASH_SEGMENT, (unsigned char*)arrCommunication, FLASH_ADDR_INIT_B, FLASH_NUM_BYTE);
					break;
				case 'C':
					regFirmTimeOnC  = regFirmTimeOn;
					regFirmTimeOffC = regFirmTimeOff;
					communicationEncode();
					flashWriteBlock(FLASH_SEGMENT, (unsigned char*)arrCommunication, FLASH_ADDR_INIT_C, FLASH_NUM_BYTE);
					break;
			}
			regFirmStatus &= ~FIRM_STT_GET_NUM;
			regFirmStatus &= ~FIRM_STT_CONFIRM;
			regFirmStatus &= ~FIRM_STT_DIGIT;
			regFirmStatus &= ~FIRM_STT_DUTY;
			regFirmOvf 	  |=  FIRM_OVF_CONFIRM;
		}
		else				// Period <= Duty -----> Not pass
		{
			lcdNotifyViolateTime();
		}
	}
	else		// Notify error (Duty == 0) at here and request reinputting
	{
		firmwareNullValue(FIRM_STT_DUTY);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
unsigned char firmwareGetDigitOrdinal (void)
{
	return ((regFirmStatus & FIRM_STT_DIGIT) >> 7);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareFirstDigit (unsigned int varPeDu)
{
#ifdef USE_LCD
	LCD_Display(0 + 48);
	LCD_Display(0 + 48);
	LCD_Display(0 + 48);
	LCD_Display(varFirmNum + 48);										// Print first digit
#endif /* USE_LCD */
	if(varPeDu == FIRM_STT_PERIOD)
	{
		mathGetBCDNumber(FIRM_STT_PERIOD, varFirmNum, MATH_ORGI_UNIT);	// Storing
#ifdef USE_LED_7SEG
		led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);			// Print in LED 7-segment
#endif /* USE_LED_7SEG */
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
		mathGetBCDNumber(FIRM_STT_DUTY, varFirmNum, MATH_ORGI_UNIT);	// Storing
#ifdef USE_LED_7SEG
		led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);			// Print in LED 7-segment
#endif /* USE_LED_7SEG */
	}
	regFirmStatus = ((regFirmStatus & (~FIRM_STT_DIGIT)) | (1<<7));		// Turn to second digit
	regFirmOvf &= ~FIRM_OVF_DIGIT;										// Turn off digit Ovf
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareSecondDigit (unsigned int varPeDu)
{
	if(varPeDu == FIRM_STT_PERIOD)
	{
#ifdef USE_LCD
		LCD_Display(0 + 48);
		LCD_Display(0 + 48);
		LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOn) + 48);		// Print first digit
		LCD_Display(varFirmNum + 48);										// Print second digit
#endif
		mathGetBCDNumber(FIRM_STT_PERIOD, varFirmNum, MATH_ORGI_DECIMAL);	// Storing
#ifdef USE_LED_7SEG
		led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);
#endif
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
#ifdef USE_LCD
		LCD_Display(0 + 48);
		LCD_Display(0 + 48);
		LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOff) + 48);		// Print first digit
		LCD_Display(varFirmNum + 48);										// Print second digit
#endif
		mathGetBCDNumber(FIRM_STT_DUTY, varFirmNum, MATH_ORGI_DECIMAL);		// Storing
#ifdef USE_LED_7SEG
		led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);
#endif
	}
	regFirmStatus = ((regFirmStatus & (~FIRM_STT_DIGIT)) | (2<<7));	// Turn to third digit
	regFirmOvf &= ~FIRM_OVF_DIGIT;									// Turn off digit Ovf
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareThirdDigit (unsigned int varPeDu)
{
	if(varPeDu == FIRM_STT_PERIOD)
	{
#ifdef USE_LCD
		LCD_Display(0 + 48);
		LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOn) + 48);		// Print first digit
		LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOn) + 48);		// Print second digit
		LCD_Display(varFirmNum + 48);										// Print third digit
#endif
		mathGetBCDNumber(FIRM_STT_PERIOD, varFirmNum, MATH_ORGI_HUNDRED);	// Storing
#ifdef USE_LED_7SEG
		led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);
#endif
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
#ifdef USE_LCD
		LCD_Display(0 + 48);
		LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOff) + 48);		// Print first digit
		LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOff) + 48);		// Print second digit
		LCD_Display(varFirmNum + 48);										// Print third digit
#endif
		mathGetBCDNumber(FIRM_STT_DUTY, varFirmNum, MATH_ORGI_HUNDRED);		// Storing
#ifdef USE_LED_7SEG
		led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);
#endif
	}
	regFirmStatus = ((regFirmStatus & (~FIRM_STT_DIGIT)) | (3<<7));			// Turn to fourth digit
	regFirmOvf &= ~FIRM_OVF_DIGIT;											// Turn off digit Ovf
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareFourthDigit (unsigned int varPeDu)
{
	if(varPeDu == FIRM_STT_PERIOD)
	{
		if(!(regFirmOvf & FIRM_OVF_DIGIT))								// No digit overflow
		{
#ifdef USE_LCD
			LCD_Display((unsigned char)mathBcdHund(regFirmTimeOn) + 48);// Print first digit
			LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOn) + 48);// Print second digit
			LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOn) + 48);// Print third digit
			LCD_Display(varFirmNum + 48);								// Print fourth digit
#endif
			mathGetBCDNumber(FIRM_STT_PERIOD, varFirmNum, MATH_ORGI_THOUSAND);
			regFirmOvf |= FIRM_OVF_DIGIT;							// Turn on digit Ovf
#ifdef USE_LED_7SEG
			led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);
#endif
		}
		else															// Notify digit overflow
		{
#ifdef USE_LCD
			lcdNotifyOverFlowDigit(FIRM_STT_PERIOD);
#elif USE_LED_7SEG
			led7segNotifyError();
#endif
		}
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
		if(!(regFirmOvf & FIRM_OVF_DIGIT))								// No digit overflow
		{
#ifdef USE_LCD
			LCD_Display((unsigned char)mathBcdHund(regFirmTimeOff) + 48);	// Print first digit
			LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOff) + 48);	// Print second digit
			LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOff) + 48);	// Print third digit
			LCD_Display(varFirmNum + 48);									// Print fourth digit
#elif USE_LED_7SEG

#endif
			mathGetBCDNumber(FIRM_STT_DUTY, varFirmNum, MATH_ORGI_THOUSAND);
			regFirmOvf |= FIRM_OVF_DIGIT;								// Turn on digit Ovf
#ifdef USE_LED_7SEG
			led7segDisplayNumber(regFirmTimeOn, regFirmTimeOff);
#endif
		}
		else															// Notify digit overflow
		{
#ifdef USE_LCD
			lcdNotifyOverFlowDigit(FIRM_STT_DUTY);
#elif USE_LED_7SEG
			led7segNotifyError();
#endif
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
void firmwareInputValue (unsigned int varPeDu)
{
	if(varPeDu == FIRM_STT_PERIOD)
	{
#ifdef USE_LCD
		LCD_Goto(2, 2);
		LCD_PrintString("Period=");
#elif USE_LED_7SEG
		__delay_cycles(1);												// Reserved
#endif
		if(regFirmStatus & FIRM_STT_OLD_VALUE)
		{
			switch (varFirmMode)
			{
				case 'A':
					LCD_Display((unsigned char)mathBcdThou(regFirmTimeOnA) + 48);
					LCD_Display((unsigned char)mathBcdHund(regFirmTimeOnA) + 48);
					LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOnA) + 48);
					LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOnA) + 48);
					break;
				case 'B':
					LCD_Display((unsigned char)mathBcdThou(regFirmTimeOnB) + 48);
					LCD_Display((unsigned char)mathBcdHund(regFirmTimeOnB) + 48);
					LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOnB) + 48);
					LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOnB) + 48);
					break;
				case 'C':
					LCD_Display((unsigned char)mathBcdThou(regFirmTimeOnC) + 48);
					LCD_Display((unsigned char)mathBcdHund(regFirmTimeOnC) + 48);
					LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOnC) + 48);
					LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOnC) + 48);
					break;
			}
			regFirmStatus &= ~FIRM_STT_OLD_VALUE;
		}
	}
	if(varPeDu == FIRM_STT_DUTY)
	{
#ifdef USE_LCD
		LCD_Goto(2, 2);
		LCD_PrintString("Duty=");
#elif USE_LED_7SEG
		__delay_cycles(1);												// Reserved
#endif
		if(regFirmStatus & FIRM_STT_OLD_VALUE)
		{
			switch (varFirmMode)
			{
				case 'A':
					LCD_Display((unsigned char)mathBcdThou(regFirmTimeOffA) + 48);
					LCD_Display((unsigned char)mathBcdHund(regFirmTimeOffA) + 48);
					LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOffA) + 48);
					LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOffA) + 48);
					break;
				case 'B':
					LCD_Display((unsigned char)mathBcdThou(regFirmTimeOffB) + 48);
					LCD_Display((unsigned char)mathBcdHund(regFirmTimeOffB) + 48);
					LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOffB) + 48);
					LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOffB) + 48);
					break;
				case 'C':
					LCD_Display((unsigned char)mathBcdThou(regFirmTimeOffC) + 48);
					LCD_Display((unsigned char)mathBcdHund(regFirmTimeOffC) + 48);
					LCD_Display((unsigned char)mathBcdDeci(regFirmTimeOffC) + 48);
					LCD_Display((unsigned char)mathBcdUnit(regFirmTimeOffC) + 48);
					break;
			}
			regFirmStatus &= ~FIRM_STT_OLD_VALUE;
		}
	}
	if(regFirmStatus & FIRM_STT_GET_NUM)								// Number is pressed
	{
		regFirmStatus &= ~FIRM_STT_CLEAR;
		regFirmStatus &= ~FIRM_STT_CONFIRM;
		if(firmwareGetDigitOrdinal() == MATH_ORGI_UNIT)					// First digit
		{
			firmwareFirstDigit(varPeDu);
		}
		else if(firmwareGetDigitOrdinal() == MATH_ORGI_DECIMAL)			// Second digit
		{
			firmwareSecondDigit(varPeDu);
		}
		else if(firmwareGetDigitOrdinal() == MATH_ORGI_HUNDRED)			// Third digit
		{
			firmwareThirdDigit(varPeDu);
		}
		else if(firmwareGetDigitOrdinal() == MATH_ORGI_THOUSAND)		// Fourth digit
		{
			firmwareFourthDigit(varPeDu);
		}
	}
	if(regFirmStatus & FIRM_STT_CLEAR)									// * (Clear) is pressed
	{
		firmwareClearTempValue(varPeDu);
	}
	if(regFirmStatus & FIRM_STT_CONFIRM)								// # (Confirm) is pressed
	{
		if(varPeDu == FIRM_STT_PERIOD)
		{
			firmwareConfirmNextValue();
		}
		if(varPeDu == FIRM_STT_DUTY)
		{
			firmwareConfirmAllValue();
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
void firmwareEnalbe (unsigned int varEnable)
{
	regFirmEnalbe = varEnable;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void firmwareCheckEnable (unsigned int varCheck)
{
	//-Mode A-//
	if(varCheck == FIRM_EN_MODE_A)
	{
		if(!(regFirmEnalbe & FIRM_EN_MODE_A))
		{
			regFirmStatus &= ~FIRM_STT_MODE_SEL;
		}
	}
	//-Mode B-//
	if(varCheck == FIRM_EN_MODE_B)
	{
		if(!(regFirmEnalbe & FIRM_EN_MODE_B))
		{
			regFirmStatus &= ~FIRM_STT_MODE_SEL;
		}
	}
	//-Mode C-//
	if(varCheck == FIRM_EN_MODE_C)
	{
		if(!(regFirmEnalbe & FIRM_EN_MODE_C))
		{
			regFirmStatus &= ~FIRM_STT_MODE_SEL;
		}
	}
	//-Mode D-//
	if(varCheck == FIRM_EN_MODE_D)
	{
		if(!(regFirmEnalbe & FIRM_EN_MODE_D))
		{
			regFirmStatus &= ~FIRM_STT_EXIT_SEL;
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
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF LCD.c
 *************************************************************************************************/

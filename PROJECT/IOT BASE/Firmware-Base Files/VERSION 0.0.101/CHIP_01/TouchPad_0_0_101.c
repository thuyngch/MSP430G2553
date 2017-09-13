/*
 *	File			:	TouchPad_0_0_101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for TouchPad
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER01_0.0.101.h"
#include "VERSION 1_0_1/Capacitive Touch/UserStruct.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
const struct Element sCapTouchBtn0 =
{
	.inputPxselRegister 	= (uint8_t*)&P1SEL,
	.inputPxsel2Register 	= (uint8_t*)&P1SEL2,
	.inputBits 				= PIN_TOUCH_00,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn1 =
{
	.inputPxselRegister 	= (uint8_t*)&P2SEL,
	.inputPxsel2Register 	= (uint8_t*)&P2SEL2,
	.inputBits 				= PIN_TOUCH_01,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn2 =
{
	.inputPxselRegister 	= (uint8_t*)&P1SEL,
	.inputPxsel2Register 	= (uint8_t*)&P1SEL2,
	.inputBits 				= PIN_TOUCH_02,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn3 =
{
	.inputPxselRegister 	= (uint8_t*)&P2SEL,
	.inputPxsel2Register 	= (uint8_t*)&P2SEL2,
	.inputBits 				= PIN_TOUCH_03,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn4 =
{
	.inputPxselRegister 	= (uint8_t*)&P2SEL,
	.inputPxsel2Register 	= (uint8_t*)&P2SEL2,
	.inputBits 				= PIN_TOUCH_04,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn5 =
{
	.inputPxselRegister 	= (uint8_t*)&P1SEL,
	.inputPxsel2Register 	= (uint8_t*)&P1SEL2,
	.inputBits 				= PIN_TOUCH_05,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn6 =
{
	.inputPxselRegister 	= (uint8_t*)&P2SEL,
	.inputPxsel2Register 	= (uint8_t*)&P2SEL2,
	.inputBits 				= PIN_TOUCH_06,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn7 =
{
	.inputPxselRegister 	= (uint8_t*)&P2SEL,
	.inputPxsel2Register 	= (uint8_t*)&P2SEL2,
	.inputBits 				= PIN_TOUCH_07,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn8 =
{
	.inputPxselRegister 	= (uint8_t*)&P1SEL,
	.inputPxsel2Register 	= (uint8_t*)&P1SEL2,
	.inputBits 				= PIN_TOUCH_08,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtn9 =
{
	.inputPxselRegister 	= (uint8_t*)&P1SEL,
	.inputPxsel2Register 	= (uint8_t*)&P1SEL2,
	.inputBits 				= PIN_TOUCH_09,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtnClr =
{
	.inputPxselRegister 	= (uint8_t*)&P1SEL,
	.inputPxsel2Register 	= (uint8_t*)&P1SEL2,
	.inputBits 				= PIN_TOUCH_CLR,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Element sCapTouchBtnCfm =
{
	.inputPxselRegister 	= (uint8_t*)&P2SEL,
	.inputPxsel2Register 	= (uint8_t*)&P2SEL2,
	.inputBits 				= PIN_TOUCH_CFM,
	.maxResponse 			= TOUCHPAD_THRESHOLD + 655,
	.threshold 				= TOUCHPAD_THRESHOLD
};

//-------------------------------------------------------------------------------------------------
const struct Sensor sCapTouchSensor =
{
	.halDefinition 		= RO_PINOSC_TA0_WDTp,		// Sensing Method
	.numElements 		= 12,						// # of Elements
	.baseOffset 		= 0,						// First element index = 0
	// Pointer to elements
	.arrayPtr[0] 		= &sCapTouchBtn0,  			// point to Btn0
	.arrayPtr[1] 		= &sCapTouchBtn1,  			// point to Btn1
	.arrayPtr[2] 		= &sCapTouchBtn2,  			// point to Btn2
	.arrayPtr[3] 		= &sCapTouchBtn3,  			// point to Btn3
	.arrayPtr[4] 		= &sCapTouchBtn4,  			// point to Btn4
	.arrayPtr[5] 		= &sCapTouchBtn5,  			// point to Btn5
	.arrayPtr[6] 		= &sCapTouchBtn6,  			// point to Btn6
	.arrayPtr[7] 		= &sCapTouchBtn7,  			// point to Btn7
	.arrayPtr[8] 		= &sCapTouchBtn8,  			// point to Btn8
	.arrayPtr[9] 		= &sCapTouchBtn9,  			// point to Btn9
	.arrayPtr[10] 		= &sCapTouchBtnClr,  		// point to BtnClr
	.arrayPtr[11] 		= &sCapTouchBtnCfm,  		// point to BtnCfm
	// Timer Information
	.measGateSource		= GATE_WDT_ACLK,     		// 0->SMCLK, 1-> ACLK
	.accumulationCycles	= WDTp_GATE_64   			// 64 - Default
};


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	touchPadDetectBtn
 *	Purpose	:	Detect which button is pressed and send info to LCD_RFID chip
 *	Input	:	None
 *	Output	:	None
 */
void
touchPadDetectBtn (void)
{
	/* Declare */
	struct Element* psElement;

	/* Detect */
	psElement = (struct Element *)TI_CAPT_Buttons(&sCapTouchSensor);

	/* Set Status Register */
	if(psElement)
	{
		if		(psElement == &sCapTouchBtn0)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_0);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn1)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_1);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn2)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendToLCD_Button_2);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn3)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendToLCD_Button_3);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn4)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_4);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn5)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_5);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn6)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_6);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn7)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_7);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn8)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_8);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtn9)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_9);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtnClr)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_Clear);
			gpioHigh(PORT2, PIN_LED_TP);
		}
		else if	(psElement == &sCapTouchBtnCfm)
		{
			cmn01Send(I2C_ADDR_LCD_RFID, eTouchPadSendTolCD_Button_Confirm);
			gpioHigh(PORT2, PIN_LED_TP);
		}
	}
	else
	{
		gpioLow(PORT2, PIN_LED_TP);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF TouchPad_0_0_101.c
 *************************************************************************************************/

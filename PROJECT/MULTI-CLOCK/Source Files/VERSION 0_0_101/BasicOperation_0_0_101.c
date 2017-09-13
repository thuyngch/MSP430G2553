/*
 *	File			:	BasicOperation_0_0_101.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source for BasicOperation
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER_0_0_101.h"


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
 *	Function:	setBits8
 *	Purpose	:	Set one bit or bits in a 8-bit register
 *	Input	:	reg_: Register
 *				varBits: One bit or bits
 *	Output	:	None
 */
unsigned int 	setBits8 		(unsigned char reg_, unsigned int varBits)
{
	reg_ |= varBits;
	return reg_;
}
//-------------------------------------------------------------------------------------------------

/*
 *	Function:	clearBits8
 *	Purpose	:	Clear one bit or bits in a 8-bit register
 *	Input	:	reg_: Register
 *				varBits: One bit or bits
 *	Output	:	None
 */
unsigned int 	clearBits8	 	(unsigned char reg_, unsigned int varBits)
{
	reg_ &= ~varBits;
	return reg_;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	setBits16
 *	Purpose	:	Set one bit or bits in a 16-bit register
 *	Input	:	reg_: Register
 *				varBits: One bit or bits
 *	Output	:	None
 */
unsigned int 	setBits16 		(unsigned int reg_, unsigned int varBits)
{
	reg_ |= varBits;
	return reg_;
}
//-------------------------------------------------------------------------------------------------

/*
 *	Function:	clearBits16
 *	Purpose	:	Clear one bit or bits in a 16-bit register
 *	Input	:	reg_: Register
 *				varBits: One bit or bits
 *	Output	:	None
 */
unsigned int 	clearBits16 	(unsigned int reg_, unsigned int varBits)
{
	reg_ &= ~varBits;
	return reg_;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	uintToByte
 *	Purpose	:	Convert an unsigned int variable to two unsigned char variables
 *	Input	:	varUint: Unsigned int variable
 *				pMSB: Address of MSB unsigned char variable
 *				pLSB: Address of LSB unsigned char variable
 *	Output	:	None
 */
void uintToByte (unsigned int varUint, unsigned char *pMSB, unsigned char *pLSB)
{
	*pMSB = (varUint >> 8) & 0xFF;
	*pLSB = varUint & 0xFF;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	byteToUint
 *	Purpose	:	Convert two unsigned char variables to an unsigned int variable
 *	Input	:	varMSB: MSB unsigned char variable
 *				varLSB: LSB unsigned char variable
 *	Output	:	Unsigned intvariable
 */
unsigned int  byteToUint (unsigned char varMSB, unsigned char varLSB)
{
	return ((varMSB << 8) | varLSB);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	digitDivide
 *	Purpose	:	Divide number (9<number<100) into two its digit
 *	Input	:	varNumber: the number
 *				varTenthDigit: tenth digit of number
 *				varUnitDigit: unit digit of number
 *	Output	:	None
 */
void digitDivide (unsigned char varNumber, unsigned char *pTenthDigit, unsigned char *pUnitDigit)
{
	if(varNumber < 10)
	{
		*pTenthDigit = 0;
		*pUnitDigit = varNumber;
	}
	else
	{
		*pUnitDigit = varNumber % 10;
		*pTenthDigit = (unsigned int)varNumber / 10;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	testUart
 *	Purpose	:	Test components of modules by UART
 *	Input	:	MODULE_: which module?
 *				COMPONENT_: which component of module?
 *	Output	:	None
 */
void testUart (unsigned char MODULE_, unsigned char COMPONENT_)
{
	switch (MODULE_)
	{
		case MODULE_BUTTON:
			switch (COMPONENT_)
			{
				case COMPONENT_BTN_UP:
					txdStr("COMPONENT_BTN_UP of MODULE_BUTTON is OK.\n");
					break;
				case COMPONENT_BTN_DOWN:
					txdStr("COMPONENT_BTN_DOWN of MODULE_BUTTON is OK.\n");
					break;
				case COMPONENT_BTN_CONFIRM:
					txdStr("COMPONENT_BTN_CONFIRM of MODULE_BUTTON is OK.\n");
					break;
				case COMPONENT_BTN_EN_TIME:
					txdStr("COMPONENT_BTN_EN_TIME of MODULE_BUTTON is OK.\n");
					break;
				case COMPONENT_BTN_EN_ALARM:
					txdStr("COMPONENT_BTN_EN_ALARM of MODULE_BUTTON is OK.\n");
					break;
				case COMPONENT_BTN_EN_FOCUS:
					txdStr("COMPONENT_BTN_EN_FOCUS of MODULE_BUTTON is OK.\n");
					break;
			}
			break;
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF BasicOperation_0_0_101.c
 *************************************************************************************************/

/*
 *	File			:	BasicOperation_1_0_1.c
 *	Date created	:	16/9/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Source for BasicOperation
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "../Header.h"


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
unsigned char 	setBits8 		(unsigned char reg_, unsigned char varBits)
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
unsigned char 	clearBits8 	(unsigned char reg_, unsigned char varBits)
{
	reg_ &= ! varBits;
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
	reg_ &= ! varBits;
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
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF BasicOperation_1_0_1.c
 *************************************************************************************************/

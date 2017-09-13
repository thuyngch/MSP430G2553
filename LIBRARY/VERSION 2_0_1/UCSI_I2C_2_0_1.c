/*
 *	File			:	USCI_I2C_2_0_1.c
 *	Date created	:	10/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	2.0.1
 *	Description		:	Construct USCI I2C library
 *	Target object	:	MSP430G2553
 */
 #define USE_USCI_I2C_2_0_1_H
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "USCI_I2C_2_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	i2cSetup
 *	Purpose	:	Setup I2C module
 * 	Input	:
 * 	Output	:	None
 */
void i2cSetup(const unsigned char I2C_, const unsigned char ADDR_OWN_,
			  const unsigned int PRE_SCALER,
			  const unsigned char INT_I2C_RX_, const unsigned char INT_I2C_TX_,
			  const unsigned char INT_I2C_STT_)
{
	UCB0CTL1 	|= UCSWRST;							// Enable SW reset
	UCB0CTL0 	 = I2C_ + UCMODE_3 + UCSYNC;		// Master/Slave, synchronous mode
  	UCB0CTL1 	 = UCSSEL_2 + UCSWRST;				// Use SMCLK, keep SW reset
	UCB0I2COA  	 = ADDR_OWN_;						// Own address
    UCB0I2CIE 	|= INT_I2C_STT_;					// Enable STT interrupt
	if(I2C_ == I2C_MASTER)
	{
		UCB0CTL0 |= UCMM;
		UCB0BR0	= (PRE_SCALER & 0xFF);				// Set pre-scaler
		UCB0BR1	= ((PRE_SCALER >> 8) & 0xFF);
	}
	if(I2C_ == I2C_SLAVE) UCB0CTL1  &= ~UCTR;		// Receiver

	P1SEL 		|= BIT6 + BIT7;						// Assign I2C pins to USCI_B0
	P1SEL2		|= BIT6 + BIT7;						// Assign I2C pins to USCI_B0

	UCB0CTL1  	&= ~UCSWRST;						// Clear SW reset, resume operation

    IE2 	  	|= INT_I2C_RX_ + INT_I2C_TX_;		// Enable TX and RX interrupt
    if((INT_I2C_RX_ == INT_I2C_RX_ON) || (INT_I2C_TX_ == INT_I2C_TX_ON) ||
    															(INT_I2C_STT_ == INT_I2C_STT_ON))
    	__bis_SR_register(GIE);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cSlvAddress
 *	Purpose	:	Set slave's address for master
 * 	Input	:	varSlvAddress: Address of slave
 * 	Output	:	None
 */
void i2cSlvAddress(const unsigned int ADDR_SLAVE_)
{
//  	UCB0CTL1 |=  UCSWRST;
  	UCB0I2CSA =  ADDR_SLAVE_;		// Set slave address
//  	UCB0CTL1 &= ~UCSWRST;			// Clear SW reset, resume operation
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cMstWriteByte
 *	Purpose	:	Write a byte of data to slave
 * 	Input	:	varRegAddress: Address of register in slave
 * 				varData: Byte of data
 * 	Output	:	Value of status register (UCB0STAT)
 */
uint8_t i2cMstWriteByte(uint8_t varData)
{
	while (UCB0CTL1 & UCTXSTP);             	// Ensure stop condition got sent
	UCB0CTL1 |= UCTR + UCTXSTT;             	// Transmitter, start condition

	while (!(IFG2 & UCB0TXIFG));				// Wait for ACK

	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault, return value of status register
	UCB0TXBUF = varData;						// Transmit data

	UCB0CTL1 |= UCTR + UCTXSTT;             	// I2C TX, start condition
	while (!(IFG2 & UCB0TXIFG));				// Wait for ACK
	UCB0CTL1 |= UCTXSTP;						// Stop condition
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
	UCB0CTL1 &= ~UCTR;							// Receiver
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cMstWriteArray
 *	Purpose	:	Write an array of data
 * 	Input	:	varRegAddress: Address of register in slave
 * 				arrData: Array of data
 * 				varLength: Length of array
 * 	Output	:	Value of status register (UCB0STAT)
 */
uint8_t i2cMstWriteArray(uint8_t arrData[], int varLength)
{
	int varCount;
	while (UCB0CTL1 & UCTXSTP);					// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;					// Transmitter, Start condition

	while (!(IFG2 & UCB0TXIFG));				// Wait for transmitting Start condition
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	
	for (varCount = 0; varCount < varLength; varCount++)
	{
		UCB0TXBUF = arrData[varCount];				// Transmit data
		while (!(IFG2&UCB0TXIFG));					// Wait for transmission
		IFG2 &= ~UCB0TXIFG;							// Clear flag USCI_B0 TX
		if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	}
	
	UCB0CTL1 |= UCTXSTP;							// Stop condition
	UCB0CTL1 &= ~UCTR;								// Receiver
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cMstReadByte
 *	Purpose	:	Read a byte of data from slave
 * 	Input	:	varRegAddress: Address of register in slave
 * 	Output	:	Value of read data
 */
uint8_t i2cMstReadByte(uint8_t varInfo)
{
	while (UCB0CTL1 & UCTXSTP);		// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;		// Transmitter, Start condition

	while (!(IFG2 & UCB0TXIFG));	// Wait for transmitting Start condition
	UCB0TXBUF = varInfo;			// Transmit information

	while (!(IFG2 & UCB0TXIFG));	// Wait for transmission
	UCB0CTL1 &= ~UCTR;				// Receiver
	UCB0CTL1 |= UCTXSTT;			// Restart condition
	IFG2 &= ~UCB0TXIFG;				// Clear flag USCI_B0 TX

	while (UCB0CTL1 & UCTXSTT);		// Wait for transmitting Restart condition
	UCB0CTL1 |= UCTXSTP;			// STOP condition
	return UCB0RXBUF;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cMstReadArray
 *	Purpose	:	Read an array of data from slave
 * 	Input	:	varRegAddress: Address of register in slave
 * 				varData: Storing array
 * 				varLength: Length of array
 * 	Output	:	None
 */
uint8_t i2cMstReadArray(uint8_t varInfo, uint8_t arrData[], int varLength)
{
	int varCount;
	
	while (UCB0CTL1 & UCTXSTP);             	// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;             	// Transmitter, Start condition

	while (!(IFG2 & UCB0TXIFG));
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	UCB0TXBUF = varInfo;						// Transmit information

	while (!(IFG2 & UCB0TXIFG));
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault

	UCB0CTL1 &= ~UCTR;                      	// Receiver
	UCB0CTL1 |= UCTXSTT;                    	// Restart condition
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
	while (UCB0CTL1 & UCTXSTT);             	// Wait for transmitting Restart condition
	
	for(varCount = 0; varCount < varLength; varCount++)
	{
		while (!(IFG2 & UCB0RXIFG));
		IFG2 &= ~UCB0TXIFG;                     // Clear flag USCI_B0 TX
		arrData[varCount] = UCB0RXBUF;
	}
	
	UCB0CTL1 |= UCTXSTP;                    	// Stop condition
	IFG2 &= ~UCB0TXIFG;							// Clear flag USCI_B0 TX
	UCB0CTL1 &= ~UCTR;							// Receiver
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cSlvWriteByte
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
uint8_t
i2cSlvWriteByte(uint8_t varData)
{
	while (UCB0CTL1 & UCTXSTP);             	// Ensure stop condition got sent
	UCB0CTL1 |= UCTR + UCTXSTT;             	// I2C TX, start condition

	while (!(IFG2 & UCB0TXIFG));				// Wait for ACK

	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault, return value of status register
	UCB0TXBUF = varData;						// Transmit data

	UCB0CTL1 |= UCTR + UCTXSTT;             	// I2C TX, start condition
	while (!(IFG2 & UCB0TXIFG));				// Wait for ACK
	UCB0CTL1 |= UCTXSTP;						// Stop condition
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
	UCB0CTL1 &= ~UCTR;                      	// Receiver
	return 0;
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
 *	END OF USCI_I2C_2_0_1.c
 *************************************************************************************************/

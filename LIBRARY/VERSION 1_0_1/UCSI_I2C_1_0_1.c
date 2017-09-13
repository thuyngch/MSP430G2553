/*
 *	File			:	USCI_I2C_1_0_1.c
 *	Date created	:	10/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct USCI I2C library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "USCI_I2C_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	i2cSetup
 *	Purpose	:	Setup I2C module
 * 	Input	:	varSlvAddress: Address of slave
 * 	Output	:	None
 */
void i2cSetup(const unsigned int I2C_, const unsigned char ADDR_SLAVE_)
{
	P1SEL |= SCL + SDA;						// Assign I2C pins to USCI_B0
	P1SEL2|= SCL + SDA;						// Assign I2C pins to USCI_B0
//	P1REN |= SCL + SDA;						// Enable pull resistor
//	P1OUT |= SCL + SDA;						// Pull up resistor

	UCB0CTL1 |= UCSWRST;					// Enable SW reset
	UCB0CTL0 = I2C_ + UCMODE_3 + UCSYNC;	// Master/Slave, synchronous mode
  	UCB0I2CSA = ADDR_SLAVE_;				// Set slave address
	if(I2C_ == I2C_MASTER)
	{
	  	UCB0CTL1 = UCSSEL_2 + UCSWRST;		// Use SMCLK, keep SW reset
		UCB0BR0 = 40;						// fSCL = SMCLK/40 = ~400kHz
		UCB0BR1 = 0;
		UCB0CTL1 &= ~UCSWRST;				// Clear SW reset, resume operation
	}
	if(I2C_ == I2C_SLAVE)
	{
		UCB0I2COA = ADDR_SLAVE_;			// Own address
		UCB0CTL1 &= ~UCTR;					// Receiver
		UCB0CTL1 &= ~UCSWRST;				// Clear SW reset, resume operation
	    IE2 |= UCB0TXIE + UCB0RXIE;			// Enable TX and RX interrupt
	    UCB0I2CIE |= UCSTTIE;				// Enable STT interrupt
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cSlvAddress
 *	Purpose	:	Set slave's address for master
 * 	Input	:	varSlvAddress: Address of slave
 * 	Output	:	None
 */
void i2cSlvAddress(const unsigned char ADDR_SLAVE_)
{
  	UCB0CTL1 |= UCSWRST;    
  	UCB0I2CSA = ADDR_SLAVE_;		// Set slave address
  	UCB0CTL1 &= ~UCSWRST;			// Clear SW reset, resume operation 
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cMstWriteByte
 *	Purpose	:	Write a byte of data to slave
 * 	Input	:	varRegAddress: Address of register in slave
 * 				varData: Byte of data
 * 	Output	:	Value of status register (UCB0STAT)
 */
unsigned char i2cMstWriteByte(unsigned char varRegAddress, unsigned char varData)
{
	while (UCB0CTL1 & UCTXSTP);					// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;					// Transmitter, Start condition

	while (!(IFG2&UCB0TXIFG));					// Wait for transmitting Start condition
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	UCB0TXBUF = varRegAddress;					// Transmit address of register

	while (!(IFG2&UCB0TXIFG));					// Wait for transmission
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	UCB0TXBUF = varData;						// Transmit data

	while (!(IFG2&UCB0TXIFG));					// Wait for transmission
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	UCB0CTL1 |= UCTXSTP;						// Stop condition
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
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
unsigned char i2cMstWriteArray(unsigned char varRegAddress, unsigned char arrData[], int varLength)
{
	int varCount;
	while (UCB0CTL1 & UCTXSTP);					// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;					// Transmitter, Start condition

	while (!(IFG2&UCB0TXIFG));					// Wait for transmitting Start condition
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	UCB0TXBUF = varRegAddress;					// Transmit address of register

	while (!(IFG2&UCB0TXIFG));					// Wait for transmission
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	
	for (varCount = 0; varCount < varLength; varCount++)
	{
		UCB0TXBUF = arrData[varCount];				// Transmit data
		while (!(IFG2&UCB0TXIFG));					// Wait for transmission
		IFG2 &= ~UCB0TXIFG;							// Clear flag USCI_B0 TX
		if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	}
	
	UCB0CTL1 |= UCTXSTP;						// Stop condition
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	i2cMstReadByte
 *	Purpose	:	Read a byte of data from slave
 * 	Input	:	varRegAddress: Address of register in slave
 * 	Output	:	Value of read data
 */
unsigned char i2cMstReadByte(unsigned char varRegAddress)
{
	while (UCB0CTL1 & UCTXSTP);		// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;		// Transmitter, Start condition

	while (!(IFG2&UCB0TXIFG));		// Wait for transmitting Start condition
	UCB0TXBUF = varRegAddress;		// Transmit address of register

	while (!(IFG2&UCB0TXIFG));		// Wait for transmission

	UCB0CTL1 &= ~UCTR;				// Receiver
	UCB0CTL1 |= UCTXSTT;			// Restart condition
	IFG2 &= ~UCB0TXIFG;				// Clear flag USCI_B0 TX

	while (UCB0CTL1 & UCTXSTT);		// Wait for transmitting Restart condition
	UCB0CTL1 |= UCTXSTP;			// Gui bit STOP
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
unsigned char i2cMstReadArray(unsigned char varRegAddress, unsigned char arrData[], int varLength)
{
	int varCount;
	
	while (UCB0CTL1 & UCTXSTP);             	// Wait for Stop condition
	UCB0CTL1 |= UCTR + UCTXSTT;             	// Transmitter, Start condition

	while (!(IFG2&UCB0TXIFG));
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault
	UCB0TXBUF = varRegAddress;					// Transmit address of register

	while (!(IFG2&UCB0TXIFG));
	if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If fault

	UCB0CTL1 &= ~UCTR;                      	// Receiver
	UCB0CTL1 |= UCTXSTT;                    	// Restart condition
	IFG2 &= ~UCB0TXIFG;                     	// Clear flag USCI_B0 TX
	while (UCB0CTL1 & UCTXSTT);             	// Wait for transmitting Restart condition
	
	for(varCount = 0; varCount < varLength; varCount++)
	{
		while (!(IFG2&UCB0RXIFG));
		IFG2 &= ~UCB0TXIFG;                     // Clear flag USCI_B0 TX
		arrData[varCount] = UCB0RXBUF;
	}
	
	UCB0CTL1 |= UCTXSTP;                    	// Stop condition
	IFG2 &= ~UCB0TXIFG;							// Clear flag USCI_B0 TX
	return 0;
}

/**************************************************************************************************
 *	END OF USCI_I2C_1_0_1.c
 *************************************************************************************************/

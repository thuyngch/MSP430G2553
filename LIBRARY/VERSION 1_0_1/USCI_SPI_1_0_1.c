/*
 * 	File			:	USCI_SPI_1_0_1.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct SPI library
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include "USCI_SPI_1_0_1.h"


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/


/****************************************************************************************
 *	FUNCTIONs
 ***************************************************************************************/
/*
 * 	Function:
 * 	Input	:
 * 	Output	:
 */
void spiA0Setup (const unsigned char SPI_, const unsigned int PRE_SCALER,
				const unsigned char INT_SPIA0_RX_, const unsigned char INT_SPIA0_TX_)
{
	P1SEL  |= SPIA0_SCLK + SPIA0_MISO + SPIA0_MOSI + SPIA0_STE;
	P1SEL2 |= SPIA0_SCLK + SPIA0_MISO + SPIA0_MOSI + SPIA0_STE;
	UCA0CTL1 = UCSWRST | UCSSEL_2;					// SMCLK, Reset
	UCA0CTL0 = SPI_MODE_0 + UCMSB + UCSYNC + SPI_;	// POL = 0, PHA = 0, MSB first, 3-pin
	UCA0BR0 = PRE_SCALER & 0xFF;					// Pre-scaler
	UCA0BR1 = (PRE_SCALER>>8) & 0xFF;
	UCA0CTL1 &= ~UCSWRST;							// Resume operation
	IE2 |= INT_SPIA0_RX_ + INT_SPIA0_TX_;			// RX, TX interrupt enable
	if((INT_SPIA0_RX_ == INT_SPIA0_RX_ON) || (INT_SPIA0_TX_ == INT_SPIA0_TX_ON))
		__bis_SR_register(GIE);
}
//---------------------------------------------------------------------------------------
/*
 * 	Function:
 * 	Input	:
 * 	Output	:
 */
void spiB0Setup (const unsigned char SPI_, const unsigned int PRE_SCALER,
				const unsigned char INT_SPIB0_RX_, const unsigned char INT_SPIB0_TX_)
{
	P1SEL  |= SPIB0_SCLK + SPIB0_MISO + SPIB0_MOSI;
	P1SEL2 |= SPIB0_SCLK + SPIB0_MISO + SPIB0_MOSI;
	UCB0CTL1 = UCSWRST | UCSSEL_2;					// SMCLK, Reset
	UCB0CTL0 = SPI_MODE_0 + UCMSB + UCSYNC + SPI_ + UCMODE_1;	// POL = 0, PHA = 0, MSB first, 4-pin
	if(SPI_ == SPI_MASTER)
	{
		UCB0BR0 = PRE_SCALER & 0xFF;				// Pre-scaler
		UCB0BR1 = (PRE_SCALER>>8) & 0xFF;
	}
	UCB0CTL1 &= ~UCSWRST;							// Resume operation
	IE2 |= INT_SPIB0_RX_ + INT_SPIB0_TX_;			// RX, TX interrupt enable
	if((INT_SPIB0_RX_ == INT_SPIB0_RX_ON) || (INT_SPIB0_TX_ == INT_SPIB0_TX_ON))
	{
		__bis_SR_register(GIE);
	}
}
//---------------------------------------------------------------------------------------
/*
 * 	Function:
 * 	Input	:
 * 	Output	:
 */
void spiA0MstWriteByte (unsigned char varData)
{
	  while (!(IFG2 & UCA0TXIFG));			// USCI_A0 TX buffer ready?
	  UCA0TXBUF = varData;					// Send next value
	  while (UCA0STAT & UCBUSY);			// Wait for transmission
}
//---------------------------------------------------------------------------------------
/*
 * 	Function:
 * 	Input	:
 * 	Output	:
 */
unsigned char spiA0MstReadByte (void)
{
	  while (UCA0STAT & UCBUSY);			// Wait for transmission
	  return UCA0RXBUF;
}
//---------------------------------------------------------------------------------------
/*
 * 	Function:
 * 	Input	:
 * 	Output	:
 */
void spiB0MstWriteByte (unsigned char varData)
{
	  while (!(IFG2 & UCB0TXIFG));			// USCI_B0 TX buffer ready?
	  UCB0TXBUF = varData;					// Send next value
	  while (UCB0STAT & UCBUSY);			// Wait for transmission
}
//---------------------------------------------------------------------------------------
/*
 * 	Function:
 * 	Input	:
 * 	Output	:
 */
unsigned char spiB0MstReadByte (void)
{
	  while (UCB0STAT & UCBUSY);			// Wait for transmission
	  return UCB0RXBUF;
}
//---------------------------------------------------------------------------------------


/****************************************************************************************
 *	END OF USCI_SPI_1_0_1.c
 ***************************************************************************************/

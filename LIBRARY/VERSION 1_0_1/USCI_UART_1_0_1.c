/*
 * 	File			:	USCI_UART_1_0_1.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	28/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct USCI UART library
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "USCI_UART_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	uartSetup
 * 	Purpose	:	Setup USCI_UART default
 * 	Input	:	CLKS_: Clock source
 * 				BAUD_: Baudrate
 * 				INT_RXD_: Turn on/off RXD interrupt
 * 	Output	:	None
 */
void uartSetup (const unsigned int CLKS_, const unsigned int BAUD_, const unsigned int INT_RXD_)
{
	P1SEL    |= TXD + RXD;
	P1SEL2   |= TXD + RXD;
	UCA0CTL0  = 0;		// no parity, LSB, 8-bit, 1 stop, UART mode, asynchronous
	switch (CLKS_)
	{
		case CLKS_SMCLK_1MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 104;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_1 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 52;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 26;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 17;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 8;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 7;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 3;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case CLKS_SMCLK_8MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 833 & 0xFF;
					UCA0BR1   = 833>>8;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 416 & 0xFF;
					UCA0BR1   = 416>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 208;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_3 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 142;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 69;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 62;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 31;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case CLKS_SMCLK_12MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 1250 & 0xFF;
					UCA0BR1   = 1250>>8;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 625 & 0xFF;
					UCA0BR1   = 625>>8;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 312 & 0xFF;
					UCA0BR1   = 312>>8;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 214;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 104;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_1 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 93;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 46;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		case CLKS_SMCLK_16MHZ:
		{
			UCA0CTL1 = UCSSEL_2;
			switch (BAUD_)
			{
				case BAUD_9600:
				{
					UCA0BR0   = 1666 & 0xFF;
					UCA0BR1   = 1666>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_19200:
				{
					UCA0BR0   = 833 & 0xFF;
					UCA0BR1   = 833>>8;
					UCA0MCTL  = UCBRS_2 + UCBRF_0;
					break;
				}
				case BAUD_38400:
				{
					UCA0BR0   = 416 & 0xFF;
					UCA0BR1   = 416>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_56000:
				{
					UCA0BR0   = 285 & 0xFF;
					UCA0BR1   = 285>>8;
					UCA0MCTL  = UCBRS_6 + UCBRF_0;
					break;
				}
				case BAUD_115200:
				{
					UCA0BR0   = 138;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_7 + UCBRF_0;
					break;
				}
				case BAUD_128000:
				{
					UCA0BR0   = 125;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_0 + UCBRF_0;
					break;
				}
				case BAUD_256000:
				{
					UCA0BR0   = 62;
					UCA0BR1   = 0;
					UCA0MCTL  = UCBRS_4 + UCBRF_0;
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	IE2 = INT_RXD_;		// Receive interrupt enable
	if (INT_RXD_ == INT_RXD_ON)
	{
		_BIS_SR(GIE);
	}
	UCA0CTL1 &= ~UCSWRST;		// Initialize USCI state machine
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	txdChar
 * 	Purpose	:	Transmit a byte of data
 * 	Input	:	varChar: data byte
 * 	Output	:	None
 */
void txdChar (unsigned char varChar)
{
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = varChar;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	txdStr
 * 	Purpose	:	Transmit a string of data
 * 	Input	:	strString: String of data
 * 	Output	:	None
 */
void txdStr (unsigned char *strString)
{
	int varCount = 0;
	do
	{
		txdChar(*(strString + varCount));
		varCount++;
	} while(*(strString + varCount - 1) != '\0');
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	txdToStr
 * 	Purpose	:	Transmit to string from ASCII number of char
 * 	Input	:	varChar: data needed to convert and transmit
 * 	Output	:	None
 */
void txdToStr (unsigned char varChar)
{
	unsigned char varA, varB, varC;
	varC = (varChar % 10);
	varB = ((varChar - varC) % 100) / 10;
	varA = (varChar - 10*varB - varC) / 100;
	varC += 48; varB += 48; varA += 48;
	txdChar(varA);
	txdChar(varB);
	txdChar(varC);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	rxdChar
 * 	Purpose	:	Receive a byte of data
 * 	Input	:	None
 * 	Output	:	Byte of data
 */
unsigned char rxdChar (void)
{
	while(!(IFG2 & UCA0RXIFG));
	return UCA0RXBUF;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	rxdStr
 * 	Purpose	:	Receive a string of data
 * 	Input	:	strRxd: Destination of storing
 * 	Output	:	None
 */
void rxdStr (unsigned char strRxd[])
{
	do
	{
		*strRxd = rxdChar();
		strRxd++;
	} while((*(strRxd - 1) != '\n') && (*(strRxd - 1) != '\0'));
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	rxdStrNLandCR
 * 	Purpose	:	Receive a string of data (frame with "\r\n" at the end)
 * 	Input	:	strRxd: Destination of storing
 * 	Output	:	None
 */
void
rxdStrNLandCR(uint8_t strRxd[])
{
	*(strRxd++) = rxdChar();
	*(strRxd++) = rxdChar();
	*(strRxd++) = rxdChar();
	while((*(strRxd - 3) != 13) || (*(strRxd - 2) != 10) || (*(strRxd - 1) != 0))
	{
		*(strRxd++) = rxdChar();
	}
}


/**************************************************************************************************
 *	END OF USCI_UART_1_0_1.c
 *************************************************************************************************/

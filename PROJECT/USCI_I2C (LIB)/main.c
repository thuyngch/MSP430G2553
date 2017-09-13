/*
 *	File			:	main.c
 *	Date created	:	10/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct USCI_I2C library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include "VERSION 1_0_1/CLOCK_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"
#include "VERSION 1_2_1/USCI_UART_1_2_1.h"
#include "VERSION 1_0_1/USCI_I2C_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Addresses */
#define		ADDRESS_MASTER		100
#define		ADDRESS_SLAVE		8

/* Commands */
#define		UART_TEST_OK		'0'	// UART RXD testing
#define		COMMAND_1			1	// Turn a LED
#define		COMMAND_2			2	// Turn 2 LEDs

/* Variables */
char varRxd;
unsigned char varCheck;

/* Externals */
extern const uart_Setup sUartSetup;


/**************************************************************************************************
 *	SUB-ROUTINEs
 *************************************************************************************************/
/*
 * 	Function:	rxdInt
 *	Purpose	:	Use in rxdIsr function
 * 	Input	:	None
 * 	Output	:	None
 */
void rxdInt (void)
{
	varRxd = rxdChar();
	if(varRxd == UART_TEST_OK)
	{
		txdStr("UART testing OK!\n");
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	port1Int
 *	Purpose	:	Use in port1Isr function
 * 	Input	:	None
 * 	Output	:	None
 */
void port1Int (void)
{
	if (P1IFG & BUTTON)
	{
		//-Exit this segment of ISR-//
		P1IFG &= ~BUTTON;
	}
}


/**************************************************************************************************
 *	MAIN-ROUTINE
 *************************************************************************************************/
int main (void)
{
	/* SETUP */
	//-Clock-//
	clkSetup(CLK_DCO_1MHZ, SWDT_ON);

	//-GPIO-//
	gpioSetup(PORT1, LED_RED + BUTTON, LED_RED);

	//-UART-//
	//uartSetup(sUartSetup.sSmclk1Mhz.sBaud9600.sIntRxdOn);

	//-I2C-//
	//i2cSetup(I2C_MASTER);
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;         // I2C Master, synchronous mode
  	UCB0CTL1 = UCSSEL_2 + UCSWRST;              // Use SMCLK, keep SW reset
	UCB0BR0 = 10;                             // fSCL = SMCLK/40 = ~400kHz
	UCB0BR1 = 0;
	UCB0I2CSA = 8;                         // Set slave address
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
//-------------------------------------------------------------------------------------------------
	/* PROCESS */
	while(1)
	{
		//i2cMstWriteByte(ADDRESS_SLAVE, 'a');
		while (UCB0CTL1 & UCTXSTP);             // Cho den khi tin hieu STT duoc gui xong
		UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, Gui bit START

		while (!(IFG2&UCB0TXIFG));				// Cho cho bit START gui xong
		UCB0TXBUF = 8;							// Gui dia chi thanh ghi can ghi


		while (!(IFG2&UCB0TXIFG));					// Cho gui xong
		if(UCB0STAT & UCNACKIFG) return UCB0STAT;	//Neu bao loi thì thoat khoi ham
		UCB0TXBUF = 8;								// Gui du lieu

		while (!(IFG2&UCB0TXIFG));					// Cho gui xong
		UCB0CTL1 |= UCTXSTP;                    	// Gui bit STOP
		IFG2 &= ~UCB0TXIFG;                     	// Xoa co USCI_B0 TX
		__delay_cycles(DL_2S);
	}
	return 1;
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/
/* RXD */
//#pragma vector = USCIAB0RX_VECTOR
//__interrupt void rxdIsr (void)
//{
//	rxdInt();
//}


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

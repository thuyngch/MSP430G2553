/*
 * 	File			:	main.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	19/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.3
 *	Description		:	Generate Communication module by GPIO
 */

/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>
#include "CommunicationGPIO.h"

/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* Arrays */
extern unsigned char arrMask[8];
extern int arrBuff[16];							//The buff memory of communication module
extern int arrData[8];							//Used to get data from Buff

/* Variables */
extern unsigned char varCharacter;
extern int varWrongTimes;
extern unsigned char varAddress;
extern unsigned char varPassword;
extern unsigned char varSecurity;

/****************************************************************************************
 *	MAIN-ROUTINE
 ***************************************************************************************/
int main (void)
{
	/* SETUP */
	WDTCTL = WDTPW + WDTHOLD;
	//What do you choose for your chip's mode? (Master/Slave)
	//And what is your chip's address and password? (0 for Master and 1/2/3/4 for Slave)
	slaveSetup(ADDRESS2, PASSWORD2, SECURITY_OFF, &varSecurity);

	/* PROCESS */
	//Loop//
	while(1);
	return 1;
}

/****************************************************************************************
 * INTERRUPT SERVICE ROUTINEs
 ***************************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void port1Int(void)
{
	/* RXD */
	if(P1IFG & RXD)
	{
		//Get sample from RXD pin//
		rxd(arrBuff);
		//Process data already received//
//		varCharacter = characterConvert(arrBuff);
//		txdChar(varCharacter);
		//Exit interrupt//
		P1IFG &= ~RXD;
	}

	/* MOSI */
	if(P1IFG & MOSI)
	{
		//Get sample from MOSI pin//
		slaveGet(arrBuff);
		//Process data already received//
		slaveCheck(arrBuff, arrData, varSecurity, &varCharacter, &varWrongTimes);
		//Exit interrupt//
		P1IFG &= MOSI;
	}
}

/****************************************************************************************
 *	END OF main.c
 ***************************************************************************************/

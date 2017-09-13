/*
 *	File			:	main.h
 *	Date created	:	08/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct LCD 16x2 library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/CLOCK_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/GPIO_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/LCD_162_1_0_1.h"
#include "C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY/VERSION 1_0_1/WATCHDOG_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	MAIN
 *************************************************************************************************/
void main (void)
{
	clkSetup(CLK_DCO_16MHZ);
	wdtSetup(WDT_OFF, WDT_TIME_32MS);

	lcdSetup(LCD_PORT_2, BIT3, BIT2, 0);
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Mode A: ");
	LCD_Goto(2,4);
	LCD_PrintString("Chinh Thuy");

	while(1);
}


/**************************************************************************************************
 *	INTERRUPT SERVICE ROUTINEs
 *************************************************************************************************/


/**************************************************************************************************
 *	END OF main.c
 *************************************************************************************************/

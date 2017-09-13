/*
 *	File			:	Communication03_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for Communication of Third Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER03_0.0.101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
uint8_t				varI2CData03;					// Temporary received data
uint8_t				arrEachMember03[32];			// Buffer of TX UART


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	cmn03SendToRFID
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
cmn03SendToRFID(void)
{
	/* Test whether Master? */
	if(!(UCB0CTL0 & UCMST))		// If chip is being Slave mode, set it as Master
	{
		i2cSetup(I2C_MASTER, I2C_ADDR_WIFI_SERVO, 40, INT_I2C_RX_ON, INT_I2C_TX_OFF, INT_I2C_STT_OFF);
		__delay_cycles(DL_500MS * FREQUENCY);
	}

	/* Declare */
	int i, j, k = 0;

	/* Set address */
	i2cSlvAddress(I2C_ADDR_LCD_RFID);

	/* Make cmn-frame and send */
	for(i = 0; i < DATA_NUM_MEMBER; i++)
	{
		j = 0;
		arrEachMember03[j++] = I2C_HEADER_WIFI_SERVO;				// Header

		arrEachMember03[j++] = arrUARTBuff03[k++];						// '/'

		arrEachMember03[j++] = arrUARTBuff03[k++];						// '<'
		arrEachMember03[j++] = arrUARTBuff03[k++];						// varNo
		arrEachMember03[j++] = arrUARTBuff03[k++];						// '>'

		arrEachMember03[j++] = arrUARTBuff03[k++];						// '<'
		while(arrUARTBuff03[k] != '>') arrEachMember03[j++] = arrUARTBuff03[k++];	// strName
		while(16 - j) arrEachMember03[j++] = '\0';
		arrEachMember03[j++] = arrUARTBuff03[k++];						// '>'

		arrEachMember03[j++] = arrUARTBuff03[k++];						// '<'
		arrEachMember03[j] 	 = arrUARTBuff03[k++] - 48;					// arrID
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		j++; k++;
		arrEachMember03[j] 	 = arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		j++; k++;
		arrEachMember03[j] 	 = arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		j++; k++;
		arrEachMember03[j] 	 = arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		j++; k++;
		arrEachMember03[j] 	 = arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		arrEachMember03[j] 	 = 10*arrEachMember03[j] + arrUARTBuff03[k++] - 48;
		j++;
		arrEachMember03[j++] = arrUARTBuff03[k++];						// '>'

		arrEachMember03[j++] = arrUARTBuff03[k++];						// '<'
		arrEachMember03[j++] = arrUARTBuff03[k++];						// arrPassword
		arrEachMember03[j++] = arrUARTBuff03[k++];
		arrEachMember03[j++] = arrUARTBuff03[k++];
		arrEachMember03[j++] = arrUARTBuff03[k++];
		arrEachMember03[j++] = arrUARTBuff03[k++];						// '>'

		arrEachMember03[j++] = 10;										// '\n'
		k++;
		arrEachMember03[j++] = I2C_ENDING;								// Ending

		/* Send 32-byte frame */
		i2cMstWriteArray(arrEachMember03, 32);
		__delay_cycles(800000 * FREQUENCY);			// Safe delay
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	cmn03MakeSampleFrame
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
cmn03MakeSampleFrame(void)
{
	/* Declare */
	uint8_t i;
	int j = 0;

	/* Assign */
	for(i = 0; i < DATA_NUM_MEMBER; i++)
	{
		arrUARTBuff03[j++] = '/';			// Starting, offset: 0

		arrUARTBuff03[j++] = '<';			// varNo, offset: 1
		arrUARTBuff03[j++] = i + 48;
		arrUARTBuff03[j++] = '>';

		arrUARTBuff03[j++] = '<';			// strName, offset: 4
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = 'A' + i;
		arrUARTBuff03[j++] = '>';

		arrUARTBuff03[j++] = '<';			// arrID, offset: 16
		arrUARTBuff03[j++] = '0';
		arrUARTBuff03[j++] = '1';
		arrUARTBuff03[j++] = '2';
		arrUARTBuff03[j++] = '3';
		arrUARTBuff03[j++] = '4';
		arrUARTBuff03[j++] = '>';

		arrUARTBuff03[j++] = '<';			// arrPassword, offset: 23
		arrUARTBuff03[j++] = '1';
		arrUARTBuff03[j++] = '2';
		arrUARTBuff03[j++] = '3';
		arrUARTBuff03[j++] = '4';
		arrUARTBuff03[j++] = '>';

		arrUARTBuff03[j++] = '\n';			// Ending, offset: 29
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
 *	END OF Communication03_0.0.101.c
 *************************************************************************************************/

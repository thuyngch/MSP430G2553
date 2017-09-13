/*
 *	File			:	Communication02_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for Communication of Second Chip
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "HEADER02_0.0.101.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
uint8_t				arrCmnBuff[30];
uint8_t				varI2C02Data;
uint8_t				varNoBuff;
uint8_t				strNameBuff[10];
uint8_t				arrIDBuff[5];
uint8_t				arrPasswordBuff[4];
uint8_t				varCountWifiData = 0;


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
cmn02Send (const uint16_t I2C_ADDR_, chip_LCD_RFID_Data eLCDSendTo_)
{
	/* Test whether Master? */
	if(!(UCB0CTL0 & UCMST))		// If chip is being Slave mode, set it as Master
	{
		i2cSetup(I2C_MASTER, I2C_ADDR_LCD_RFID, 40, INT_I2C_RX_ON, INT_I2C_TX_OFF, INT_I2C_STT_OFF);
		__delay_cycles(DL_500MS * FREQUENCY);
	}

	/* Declare */
	uint8_t arrTmp[3];

	/* Make frame */
	arrTmp[0] = I2C_HEADER_LCD_RFID;
	arrTmp[1] = eLCDSendTo_;
	arrTmp[2] = I2C_ENDING;

	/* Set recieved address */
	i2cSlvAddress(I2C_ADDR_);

	/* Send */
	i2cMstWriteArray(arrTmp, 3);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
cmn02BtnDataClear (void)
{
	uint8_t varTmp;
	for(varTmp = 0; varTmp < I2C_NUM_BYTE_OF_FRAME; varTmp++) arrCmnBuff[varTmp] = 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
cmn02StrDecoder (uint8_t* strData, uint8_t* pNo, uint8_t* strName, uint8_t arrID[], uint8_t arrPassword[])
{
	*pNo = strData[2] - 48;

	strName[0] = strData[5];
	strName[1] = strData[6];
	strName[2] = strData[7];
	strName[3] = strData[8];
	strName[4] = strData[9];
	strName[5] = strData[10];
	strName[6] = strData[11];
	strName[7] = strData[12];
	strName[8] = strData[13];
	strName[9] = strData[14];

	arrID[0] = strData[17];
	arrID[1] = strData[18];
	arrID[2] = strData[19];
	arrID[3] = strData[20];
	arrID[4] = strData[21];

	arrPassword[0] = strData[24];
	arrPassword[1] = strData[25];
	arrPassword[2] = strData[26];
	arrPassword[3] = strData[27];
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
cmn02ClearBuff(uint8_t arrBuff[])
{
	uint8_t i;
	for(i = 0; i < 30; i++) arrBuff[i] = 0;
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
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF Communication02_0.0.101.c
 *************************************************************************************************/

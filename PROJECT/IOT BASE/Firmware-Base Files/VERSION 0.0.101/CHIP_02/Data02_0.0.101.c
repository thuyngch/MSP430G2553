/*
 *	File			:	Data02_0.0.101.c
 *	Date created	:	27/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	0.0.101
 *	Description		:	Source file for Data of Second Chip
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
uint8_t			varReaderStatus;
int				varNoCurrent;
int				varNoLast = -1;
bool			varPasswordResult;
uint8_t			arrReaderID[5];
person			sMember02[DATA_NUM_MEMBER]=
{
		{0, "AAAAAAAAA", {149, 181, 218, 82, 168}, {'1', '2', '3', '4'}},
		{1, "BBBBBBBBB", {147, 84, 61, 213, 47}, {'5', '6', '7', '8'}},
		{2, "CCCCCCCCC", {0, 0, 0, 0, 0}, {0, 0, 0, 0}},
		{3, "DDDDDDDDD", {0, 0, 0, 0, 0}, {0, 0, 0, 0}},
		{4, "EEEEEEEEE", {0, 0, 0, 0, 0}, {0, 0, 0, 0}}
};


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	dataCheckID
 *	Purpose	:	Check whether Card is right or wrong?
 *	Input	:	arrID: ID already read
 *				sMember02: Reference
 *	Output	:	No. of Card (0 for wrong Card)
 */
int8_t
data02CheckID (void)
{
	uint8_t i, j;
	bool	varStatus = false;

	for(i = 0; i < DATA_NUM_MEMBER; i++)
	{
		for(j = 0; j < 5; j++)
		{
			if((arrReaderID[j] - sMember02[i].arrID[j]))
			{
				varStatus = false;
				break;
			}
			else varStatus = true;
		}
		if(varStatus == true) return sMember02[i].varNo;
	}
	return -1;		// Wrong Card
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
bool
data02CheckPassword	(char varNo, char arrButtonRxData[])
{
	char 	i;
	bool	varCheck = false;
	for(i = 0; i < 4; i++)
	{
		if(sMember02[varNo].arrPassword[i] == arrButtonRxData[i])	varCheck = true;
		else
		{
			varCheck = false;
			break;
		}
	}
	return varCheck;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
data02SaveAccount (char varNo_)
{
	sMember02[varNo_].varNo 			= varNo_;				// Save varNo_

	sMember02[varNo_].strName[0] 		= strNameBuff[0];		// Save strName
	sMember02[varNo_].strName[1] 		= strNameBuff[1];
	sMember02[varNo_].strName[2] 		= strNameBuff[2];
	sMember02[varNo_].strName[3] 		= strNameBuff[3];
	sMember02[varNo_].strName[4] 		= strNameBuff[4];
	sMember02[varNo_].strName[5] 		= strNameBuff[5];
	sMember02[varNo_].strName[6] 		= strNameBuff[6];
	sMember02[varNo_].strName[7] 		= strNameBuff[7];
	sMember02[varNo_].strName[8] 		= strNameBuff[8];
	sMember02[varNo_].strName[9] 		= strNameBuff[9];

	sMember02[varNo_].arrID[0] 			= arrIDBuff[0];			// Save arrID
	sMember02[varNo_].arrID[1] 			= arrIDBuff[1];
	sMember02[varNo_].arrID[2] 			= arrIDBuff[2];
	sMember02[varNo_].arrID[3] 			= arrIDBuff[3];
	sMember02[varNo_].arrID[4] 			= arrIDBuff[4];

	sMember02[varNo_].arrPassword[0] 	= arrPasswordBuff[0];	// Save arrPassword
	sMember02[varNo_].arrPassword[1] 	= arrPasswordBuff[1];
	sMember02[varNo_].arrPassword[2] 	= arrPasswordBuff[2];
	sMember02[varNo_].arrPassword[3] 	= arrPasswordBuff[3];
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	readerLoadFromFlash
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
data02LoadFromFlash (void)
{
	uint8_t	i, j = 0;
	uint8_t arrTmpC[DATA_SEG_C_BYTE], arrTmpD[DATA_SEG_D_BYTE];

	/* Load from flash */
	flashReadBlock(segC, arrTmpC, DATA_SEG_C_OFF_0, DATA_SEG_C_BYTE);
	flashReadBlock(segD, arrTmpD, DATA_SEG_D_OFF_3, DATA_SEG_D_BYTE);

	/* Read from array */
	for(i = 0; i < 3; i++)
	{
		sMember02[i].varNo 				= arrTmpC[j++];
		sMember02[i].strName[0] 		= arrTmpC[j++];
		sMember02[i].strName[1] 		= arrTmpC[j++];
		sMember02[i].strName[2] 		= arrTmpC[j++];
		sMember02[i].strName[3] 		= arrTmpC[j++];
		sMember02[i].strName[4] 		= arrTmpC[j++];
		sMember02[i].strName[5] 		= arrTmpC[j++];
		sMember02[i].strName[6] 		= arrTmpC[j++];
		sMember02[i].strName[7] 		= arrTmpC[j++];
		sMember02[i].strName[8] 		= arrTmpC[j++];
		sMember02[i].strName[9] 		= arrTmpC[j++];
		sMember02[i].arrID[0] 			= arrTmpC[j++];
		sMember02[i].arrID[1] 			= arrTmpC[j++];
		sMember02[i].arrID[2] 			= arrTmpC[j++];
		sMember02[i].arrID[3] 			= arrTmpC[j++];
		sMember02[i].arrID[4] 			= arrTmpC[j++];
		sMember02[i].arrPassword[0] 	= arrTmpC[j++];
		sMember02[i].arrPassword[1] 	= arrTmpC[j++];
		sMember02[i].arrPassword[2] 	= arrTmpC[j++];
		sMember02[i].arrPassword[3] 	= arrTmpC[j++];
	}
	j = 0;
	for(i = 3; i < 5; i++)
	{
		sMember02[i].varNo 				= arrTmpD[j++];
		sMember02[i].strName[0] 		= arrTmpD[j++];
		sMember02[i].strName[1] 		= arrTmpD[j++];
		sMember02[i].strName[2] 		= arrTmpD[j++];
		sMember02[i].strName[3] 		= arrTmpD[j++];
		sMember02[i].strName[4] 		= arrTmpD[j++];
		sMember02[i].strName[5] 		= arrTmpD[j++];
		sMember02[i].strName[6] 		= arrTmpD[j++];
		sMember02[i].strName[7] 		= arrTmpD[j++];
		sMember02[i].strName[8] 		= arrTmpD[j++];
		sMember02[i].strName[9] 		= arrTmpD[j++];
		sMember02[i].arrID[0] 			= arrTmpD[j++];
		sMember02[i].arrID[1] 			= arrTmpD[j++];
		sMember02[i].arrID[2] 			= arrTmpD[j++];
		sMember02[i].arrID[3] 			= arrTmpD[j++];
		sMember02[i].arrID[4] 			= arrTmpD[j++];
		sMember02[i].arrPassword[0] 	= arrTmpD[j++];
		sMember02[i].arrPassword[1] 	= arrTmpD[j++];
		sMember02[i].arrPassword[2] 	= arrTmpD[j++];
		sMember02[i].arrPassword[3] 	= arrTmpD[j++];
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	readerSaveToFlash
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
data02SaveToFlash (void)
{
	uint8_t j = 0;
	uint8_t arrTmp[DATA_MEM_BYTE];

	/* Make array */
	arrTmp[j++] = sMember02[varNoBuff].varNo;
	arrTmp[j++] = sMember02[varNoBuff].strName[0];
	arrTmp[j++] = sMember02[varNoBuff].strName[1];
	arrTmp[j++] = sMember02[varNoBuff].strName[2];
	arrTmp[j++] = sMember02[varNoBuff].strName[3];
	arrTmp[j++] = sMember02[varNoBuff].strName[4];
	arrTmp[j++] = sMember02[varNoBuff].strName[5];
	arrTmp[j++] = sMember02[varNoBuff].strName[6];
	arrTmp[j++] = sMember02[varNoBuff].strName[7];
	arrTmp[j++] = sMember02[varNoBuff].strName[8];
	arrTmp[j++] = sMember02[varNoBuff].strName[9];
	arrTmp[j++] = sMember02[varNoBuff].arrID[0];
	arrTmp[j++] = sMember02[varNoBuff].arrID[1];
	arrTmp[j++] = sMember02[varNoBuff].arrID[2];
	arrTmp[j++] = sMember02[varNoBuff].arrID[3];
	arrTmp[j++] = sMember02[varNoBuff].arrID[4];
	arrTmp[j++] = sMember02[varNoBuff].arrPassword[0];
	arrTmp[j++] = sMember02[varNoBuff].arrPassword[1];
	arrTmp[j++] = sMember02[varNoBuff].arrPassword[2];
	arrTmp[j++] = sMember02[varNoBuff].arrPassword[3];

	/* Save into flash */
	switch (varNoBuff)
	{
		case 0:
			flashWriteBlock(segC, arrTmp, DATA_SEG_C_OFF_0, DATA_MEM_BYTE);
			break;
		case 1:
			flashWriteBlock(segC, arrTmp, DATA_SEG_C_OFF_1, DATA_MEM_BYTE);
			break;
		case 2:
			flashWriteBlock(segC, arrTmp, DATA_SEG_C_OFF_2, DATA_MEM_BYTE);
			break;
		case 3:
			flashWriteBlock(segD, arrTmp, DATA_SEG_D_OFF_3, DATA_MEM_BYTE);
			break;
		case 4:
			flashWriteBlock(segD, arrTmp, DATA_SEG_D_OFF_4, DATA_MEM_BYTE);
			break;
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
 *	END OF Data02_0.0.101.c
 *************************************************************************************************/

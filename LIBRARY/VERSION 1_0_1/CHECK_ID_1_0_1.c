/*
 * 	File			:	CHECK_ID_1_0_1.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct CHECK_ID library
 */
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include "CHECK_ID_1_0_1.h"
#include "USCI_UART_1_0_1.h"


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* Details about members */
person sMembers[5] =
{
		{1, "Nguyen Chinh Thuy", { 72, 195,  49,   0, 186}},
		{2, "Huynh Hoang Loc"  , {114, 172, 169, 213, 162}},
		{3, "Dang Minh Nguyen" , { 57, 141, 209, 181, 208}},
		{4, "Le Anh Tuan"	   , { 92,  73, 209, 181, 113}},
		{5, "Truong Thien Phuc", { 92, 244, 220, 181, 193}}
};


/****************************************************************************************
 *	FUNCTIONs
 ***************************************************************************************/
/*
 * 	Function:	checkID
 * 	Input	: 	arrID: ID number of card
 * 			  	sMembers: Base data
 * 	Output	:	check whether ID is correct
 */
int checkID (unsigned char arrID[], person sMembers[])
{
	int i, j;
	int varCheck;
	for (i = 0; i < 5; i++)
	{
		varCheck = RIGHT;
		for (j = 0; j < 5; j++)
		{
			if (arrID[j] == sMembers[i].arrID[j])
			{
				varCheck *= RIGHT;
			}
			else
			{
				varCheck *= WRONG;
				break;
			}
		}
		if (varCheck == RIGHT)
		{
			return sMembers[i].varNo;
		}
	}
	return WRONG;
}
//---------------------------------------------------------------------------------------
/*
 * 	Function:	dispID
 * 	Input	: 	arrID: ID number of card
 * 	Output	: 	display ID number of card into screen
 */
void dispID (unsigned char arrID[])
{
	txdStr("-----------------------------------------------------------------------\n\n");
	txdStr("The card's number is: ");
	txdToStr(arrID[0]);
	txdStr(" , ");
	txdToStr(arrID[1]);
	txdStr(" , ");
	txdToStr(arrID[2]);
	txdStr(" , ");
	txdToStr(arrID[3]);
	txdStr(" , ");
	txdToStr(arrID[4]);
	txdStr("\n");
}
//---------------------------------------------------------------------------------------
/*
 * 	Function: 	dispInfo
 * 	Input	: 	varNo: Ordinary number
 * 			  	sMembers: Base data
 * 	Output	: 	display ID number of card into screen
 */
void dispInfo (int varNo, person sMembers[])
{
	txdStr("Hello");
	txdStr(sMembers[varNo - 1].strName);
	txdStr("!\n\n");
}
//---------------------------------------------------------------------------------------
/*
 * 	Function: 	dispInfo
 * 	Input	: 	varNo: Ordinary number
 * 			  	sMembers: Base data
 * 	Output	: 	display ID number of card into screen
 */
void dispScreen (int *varNo, int *varNoOld, unsigned char arrID[], person sMembers[], const int REPEAT_)
{
	if (REPEAT_ == REPEAT_NON)
	{
		if (*varNo != *varNoOld )
		{
			// Display ID number of card //
			dispID(arrID);
			// Notify whether card is correct //
			if (*varNo != WRONG)
			{
				dispInfo(*varNo, sMembers);
			}
			else
			{
				txdStr("Detect a stealer!\n");
			}
		}
		*varNoOld = *varNo;
	}
	else
	{
		// Display ID number of card //
		dispID(arrID);
		// Notify whether card is correct //
		if (*varNo != WRONG)
		{
			dispInfo(*varNo, sMembers);
		}
		else
		{
			txdStr("Detect a stealer!\n");
		}
	}
}


/****************************************************************************************
 *	END OF CHECK_ID_1_0_1.c
 ***************************************************************************************/

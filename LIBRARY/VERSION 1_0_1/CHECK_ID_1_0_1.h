/*
 * 	File			:	CHECK_ID_1_0_1.h
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct CHECK_ID library
 */

#ifndef CHECK_ID_1_0_1_H_
#define CHECK_ID_1_0_1_H_
/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include <msp430.h>


/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* Check whether card or tag is right */
#define		RIGHT			1
#define		WRONG			0

/* Repeat display mode */
#define		REPEAT			1
#define		REPEAT_NON		0

/* Structure of personal information */
typedef struct
{
	int varNo;						// Ordinary number
	unsigned char strName[30];		// Name
	unsigned char arrID[5];			// ID number
} person;


/****************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 ***************************************************************************************/
/* Check */
int checkID (unsigned char arrID[], person sMembers[]);

/* Display */
void dispID (unsigned char arrID[]);
void dispInfo (int varNo, person sMembers[]);
void dispScreen (int *varNo, int *varNoOld, unsigned char arrID[], person sMembers[], const int REPEAT_);
 
/****************************************************************************************
 *	END OF CHECK_ID_1_0_1.h
 ***************************************************************************************/
#endif /* CHECK_ID_1_0_1_H_ */

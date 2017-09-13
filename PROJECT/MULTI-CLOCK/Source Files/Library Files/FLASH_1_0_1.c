/*
 * 	File			:	FLASH_1_0_1.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	12/08/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct Flash Memory library
 */
#define	USE_CLOCK_1_2_3
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "FLASH_1_0_1.h"


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	flashSetup
 * 	Purpose	:	Setup flash module
 * 	Input	:	None
 * 	Output	:	None
 */
void flashSetup (const unsigned int CLK_)
{
	if(CLK_ == CLK_DCO_1MHZ)
	{
		FCTL2 = FWKEY + FSSEL_2 + 2;		// 1Mhz/3 = 333kHz
	}
	else if(CLK_ == CLK_DCO_8MHZ)
	{
		FCTL2 = FWKEY + FSSEL_2 + 23;		// 8Mhz/24 = 333kHz
	}
	else if(CLK_ == CLK_DCO_12MHZ)
	{
		FCTL2 = FWKEY + FSSEL_2 + 35;		// 12Mhz/36 = 333kHz
	}
	else if(CLK_ == CLK_DCO_16MHZ)
	{
		FCTL2 = FWKEY + FSSEL_2 + 47;		// 16Mhz/48 = 333kHz
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	flashReadByte
 * 	Purpose	:	Read a byte from flash memory (Information section)
 * 	Input	:	seg_: segA, segB, segC, segD?
 * 				pData: Pointer points to address of variable that is needed saving data into it
 * 				varPosition: Position of data wanted to get in flash memory
 * 	Output	:	None
 */
void flashReadByte (flash_Segment seg_, unsigned char *pData, unsigned char varPosition)
{
	unsigned char *pAddress;
	switch (seg_)					// Set initial address for pointer
	{
		case segA: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_A; break;
		case segB: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_B; break;
		case segC: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_C; break;
		case segD: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_D; break;
		default: break;
	}
	pAddress +=  varPosition;		// Jump to needed position
	*pData    = *pAddress;			// Read value
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	flashReadBlock
 * 	Purpose	:	Read a block of data from flash memory (Information section)
 * 	Input	:	seg_: segA, segB, segC, segD?
 * 				arrData: Read and save value into this array
 * 				varInitPosition: The initial position for reading of segment
 * 				varNumOfByte : How many bytes of block?
 * 	Output	:	None
 */
void flashReadBlock (flash_Segment seg_, unsigned char arrData[], unsigned char varInitPosition,
						unsigned char varNumOfByte)
{
	while((varInitPosition + varNumOfByte) > FLASH_SEG_LENGTH);	// Trap if exceed segment
	unsigned char *pAddress;
	switch (seg_)					// Set initial address for pointer
	{
		case segA: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_A; break;
		case segB: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_B; break;
		case segC: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_C; break;
		case segD: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_D; break;
		default: break;
	}
	pAddress += varInitPosition;	// Jump to needed address
	while(varNumOfByte > 0)
	{
		*arrData = *pAddress;		// Read value
		arrData++;
		pAddress++;
		varNumOfByte--;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	flashWriteByte
 * 	Purpose	:	Write a byte into flash memory (Information section)
 * 	Input	:	seg_: segA, segB, segC, segD?
 * 				varData: Write data of this variable into the position of segment of flash memory
 * 	Output	:
 */
void flashWriteByte (flash_Segment seg_, unsigned char varData, unsigned char varPosition)
{
	unsigned char *pAddress;
	unsigned char varCount;
	unsigned char arrTempData[FLASH_SEG_LENGTH];
	switch (seg_)				// Set initial address for pointer
	{
		case segA: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_A; break;
		case segB: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_B; break;
		case segC: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_C; break;
		case segD: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_D; break;
		default: break;
	}

	for(varCount = 0; varCount < FLASH_SEG_LENGTH; varCount++)
	{
		arrTempData[varCount]= *(pAddress + varCount); 	// Copy value of segment to variable
	}

	FCTL1 = FWKEY + ERASE;		// Set Erase bit
    FCTL3 = FWKEY;				// Clear Lock bit
    *pAddress = 0;				// Dummy write to erase Flash segment

    while(FCTL3  &BUSY);		// Wait for complete erase
    FCTL1 = FWKEY + WRT;		// Set WRT bit for write operation

    for(varCount = 0; varCount < FLASH_SEG_LENGTH; varCount++)
    {
    	if(varCount == varPosition)
    	{
    		*(pAddress + varCount) = varData;	// Write data to needed position
    	}
    	else
    	{
    		*(pAddress + varCount) = arrTempData[varCount];	// Write old values to flash
    	}
    	while(!(FCTL3 & WAIT));			// Wait for complete erase
	}
    FCTL1 = FWKEY;						// Clear WRT bit
    while(FCTL3 & BUSY);				// Wait for complete erase
    FCTL3 = FWKEY + LOCK + LOCKA;		// Set LOCK bit
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	flashWriteBlock
 * 	Purpose	:	Write an array into flash memory (Information section)
 * 	Input	:	seg_: segA, segB, segC, segD?
 * 				arrData: Write values of this array into block of segment of flash memory
 * 				varInitPosition: The initial position of block
 * 				varNumOfByte: How many bytes of block?
 * 	Output	:
 */
void flashWriteBlock (flash_Segment seg_, unsigned char arrData[], unsigned char varInitPosition,
						unsigned char varNumOfByte)
{
	while((varInitPosition + varNumOfByte) > FLASH_SEG_LENGTH);	// Trap if exceed segment

	unsigned char *pAddress;
	unsigned char varCount;
	unsigned char arrTempData[FLASH_SEG_LENGTH];

	switch (seg_)				// Set initial address for pointer
	{
		case segA: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_A; break;
		case segB: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_B; break;
		case segC: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_C; break;
		case segD: pAddress = (unsigned char*)FLASH_ADDR_INIT_SEG_D; break;
		default: break;
	}

	for(varCount = 0; varCount < FLASH_SEG_LENGTH; varCount++)
	{
		arrTempData[varCount]= *(pAddress + varCount); 	// Copy value of segment to variable
	}

	FCTL1 = FWKEY + ERASE;		// Set Erase bit
    FCTL3 = FWKEY;				// Clear Lock bit
    *pAddress = 0;				// Dummy write to erase Flash segment

    while(FCTL3  &BUSY);		// Wait for complete erase
    FCTL1 = FWKEY + WRT;		// Set WRT bit for write operation

    for(varCount = 0; varCount < FLASH_SEG_LENGTH; varCount++)
    {
    	if((varCount >= varInitPosition) && (varCount < (varInitPosition + varNumOfByte)))
    	{
    		*(pAddress + varCount) = arrData[varCount - varInitPosition];	// Write data to needed position
    	}
    	else
    	{
    		*(pAddress + varCount) = arrTempData[varCount];	// Write old values to flash
    	}
    	while(!(FCTL3 & WAIT));			// Wait for complete erase
	}

    FCTL1 = FWKEY;						// Clear WRT bit
    while(FCTL3 & BUSY);				// Wait for complete erase
    FCTL3 = FWKEY + LOCK + LOCKA;		// Set LOCK bit
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF FLASH_1_0_1.c
 *************************************************************************************************/

/*
 * 	File			:	main.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	23/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.3
 *	Description		:	Generate Communication module by GPIO
 */

/****************************************************************************************
 *	IMPORT
 ***************************************************************************************/
#include "CommunicationGPIO.h"

/****************************************************************************************
 *	DEFINITIONs
 ***************************************************************************************/
/* Arrays */
unsigned char arrMask[8] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};
int arrBuff[16];						//The buff memory of Communication module
int arrData[8];							//Used to get data from Buff

/* Variables */
unsigned char varCharacter;
int varWrongTimes;
unsigned char varAddress;
unsigned char varPassword;
unsigned char varSecurity;

/****************************************************************************************
 *	FUNCTIONs
 ***************************************************************************************/
/*
 *	Function	:	ledOn
 *	Input		:	none
 *	Output		:	none
 */
void ledOn(void)
{
	P1OUT |= LED_RED;
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	ledOff
 *	Input		:	none
 *	Output		:	none
 */
void ledOff(void)
{
	P1OUT &= ~LED_RED;
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	ledToogle
 *	Input		:	none
 *	Output		:	none
 */
void ledToogle(void)
{
	P1OUT ^= LED_RED;
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	arrayPushLow
 *	Input		:	arrSource		: store source data
 *	Output		:	arrDestination	: push data into this array
 */
void arrayPushLow(int arrSource[], int arrDestination[])
{
	int i;
	for (i = 0; i < 8; i++)
	{
		arrDestination[i] = arrSource[i];
	}
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	arrayPushHigh
 *	Input		:	arrSource		: store source data
 *	Output		:	arrDestination	: push data into this array
 */
void arrayPushHigh(int arrSource[], int arrDestination[])
{
	int i;
	for (i = 8; i < 16; i++)
	{
		arrDestination[i-8] = arrSource[i];
	}
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	power
 *	Input		:	varBase			: the base number of power
 *					varExponential	: the exponential number of power
 *	Output		:	the result of calculation
 */
unsigned char power(unsigned char varBase, unsigned char varExponential)
{
	unsigned char i;
	unsigned char varResult = 1;
	for(i = 0; i < varExponential; i++)
	{
		varResult *= varBase;
	}
	return varResult;
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	characterConvert
 *	Input		:	arrData: store data that you want to calculate in ASCII
 *	Output		:	number of data corresponding ASCII
 */
unsigned char characterConvert (int arrArray[])
{
	unsigned char i;
	unsigned char varCharacter = 0;
	for(i = 0; i < 8; i++)
	{
		varCharacter += power(2,i) * (unsigned char)arrArray[i];
	}
	return varCharacter;
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	selectPosition
 *	Input		:	ADDRESS		: constant of address that you want your chip being
 *					PASSWORD	: constant of password that corresponds with address
 *	Output		:	varAddress 	: address of your chip
 *					varPassword	: passwor of your chip
 */
void selectPosition(const unsigned char ADDRESS, const unsigned char PASSWORD, unsigned char *varAddress, unsigned char *varPassword)
{
	*varAddress  = ADDRESS;
	*varPassword = PASSWORD;
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	masterSetup
 *	Input		:	ADDRESS		: constant of address that you want your chip being
 *					PASSWORD	: constant of password that corresponds with address
 *	Output		:	varSecurity	: Configure Security mode
 */
void masterSetup(const unsigned char ADDRESS, const unsigned char PASSWORD, const unsigned char SECURITY, unsigned char *varSecurity)
{
	//DCOCLK = 1MHz//
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	//GPIO//
	P1SEL  = 0;
	P1SEL2 = 0;
	P1DIR  = TXD + MOSI + LED_RED;
	P1REN  = RXD + MISO;
	P1OUT  = RXD + MISO;
	ledOn();
	//Port Interrupt//
	P1IE   = RXD + MISO;
	P1IES  = RXD + MISO;
	P1IFG  = 0;
	_BIS_SR(GIE);
	//Address and Password//
	selectPosition(ADDRESS, PASSWORD, &varAddress, &varPassword);
	//Security mode//
	*varSecurity = SECURITY;
	//Prepare for transmit//
	P1OUT |= TXD + MOSI;
	__delay_cycles(1000000);		//1s
	ledOff();
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	slaveSetup
 *	Input		:	ADDRESS	: constant of address that you want your chip being
 *					PASSWORD: constant of password that corresponds with address
 *	Output		:	varSecurity	: Configure Security mode
 */
void slaveSetup(const unsigned char ADDRESS, const unsigned char PASSWORD, const unsigned char SECURITY, unsigned char *varSecurity)
{
	//DCOCLK = 1MHz//
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	//GPIO//
	P1SEL  = 0;
	P1SEL2 = 0;
	P1DIR  = TXD + MISO + LED_RED;
	P1REN  = RXD + MOSI;
	P1OUT  = RXD + MOSI;
	ledOn();
	//Port Interrupt//
	P1IE   = RXD + MOSI;
	P1IES  = RXD + MOSI;
	P1IFG  = 0;
	_BIS_SR(GIE);
	//Address and Password//
	selectPosition(ADDRESS, PASSWORD, &varAddress, &varPassword);
	//Security mode//
	*varSecurity = SECURITY;
	//Prepare for transmit//
	P1OUT |= TXD + MISO;
	__delay_cycles(1000000);		//1s
	ledOff();
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	txdChar
 *	Input		:	varData:	byte of data that we want to transmit
 *	Output		:	none
 */
void txdChar (unsigned char varData)
{
	unsigned char varBit;
	int varCount;

	P1OUT &= ~TXD;									//Start bit
	__delay_cycles(BAUDRATE_TXD);
	for (varCount = 0; varCount < 8; varCount++)	//8 data bits
	{
		varBit = (varData & arrMask[varCount]) >> varCount;
		if(varBit != 0)
		{
			P1OUT |= varBit<<TXD_TRANS;
			__delay_cycles(BAUDRATE_TXD - BAUD_LAG_PUT);
		}
		else
		{
			P1OUT &= varBit<<TXD_TRANS;
			__delay_cycles(BAUDRATE_TXD - BAUD_LAG_PUT);
		}
	}
	P1OUT |= TXD;									//Stop bit
	__delay_cycles(BAUDRATE_TXD);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	txdStr
 *	Input		:	strData: string of data that we want to transmit
 *	Output		:	none
 */
void txdStr (unsigned char *strData)
{
	int varCount = 0;
	while(*(strData + varCount) != 0)
	{
		txdChar(*(strData + varCount));
		varCount++;
	}
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	rxd
 *	Input		:	none
 *	Output		:	arrBuff: the buff memory of Communication module
 */
void rxd (int arrBuff[])
{
	__delay_cycles(BAUDRATE_RXD - BAUD_LAG_GET);
	arrBuff[0] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[1] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[2] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[3] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[4] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[5] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[6] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
	arrBuff[7] = (P1IN & RXD) >> RXD_TRANS;
	__delay_cycles(BAUDRATE_RXD);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	masterRespond
 *	Input		:	none
 *	Output		:	none
 */
void masterRespond (unsigned char varCharacter)
{
	if (varCharacter == 65)
	{
		ledOn();
		txdChar(65);
		__delay_cycles(2000000);
		ledOff();
	}
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	slaveRespond
 *	Input		:	none
 *	Output		:	none
 */
void slaveRespond (unsigned char varCharacter)
{
	unsigned char varResult;
	//Convert Normal font to Bold font
	varResult = varCharacter % 24;
	varResult += 64;
	slavePut(ADDRESS1 + PASSWORD1, varResult);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	masterPut
 *	Input		:	varByte1: Address and Password
 *					varByte2: Data
 *	Output		:	none
 */
void masterPut (unsigned char varByte1, unsigned char varByte2)
{
	unsigned char varBit;
	int varCount;

	/* Byte1 */
	P1OUT &= ~MOSI;									//Start bit of byte 1
	__delay_cycles(BAUDRATE_MOSI);
	for (varCount = 0; varCount < 8; varCount++)	//8 data bits of byte 1
	{
		varBit = (varByte1 & arrMask[varCount]) >> varCount;
		if(varBit != 0)
		{
			P1OUT |= varBit<<MOSI_TRANS;
			__delay_cycles(BAUDRATE_MOSI - BAUD_LAG_PUT);
		}
		else
		{
			P1OUT &= varBit<<MOSI_TRANS;
			__delay_cycles(BAUDRATE_MOSI - BAUD_LAG_PUT);
		}
	}
	P1OUT |= MOSI;									//Stop bit of byte 1
	__delay_cycles(BAUDRATE_MOSI);

	/* Delay between 2 bytes */
	__delay_cycles(DELAY_MS);

	/* Byte2 */
	P1OUT &= ~MOSI;									//Start bit of byte 2
	__delay_cycles(BAUDRATE_MOSI);
	for (varCount = 0; varCount < 8; varCount++)	//8 data bits of byte 2
	{
		varBit = (varByte2 & arrMask[varCount]) >> varCount;
		if(varBit != 0)
		{
			P1OUT |= varBit<<MOSI_TRANS;
			__delay_cycles(BAUDRATE_MOSI - BAUD_LAG_PUT);
		}
		else
		{
			P1OUT &= varBit<<MOSI_TRANS;
			__delay_cycles(BAUDRATE_MOSI - BAUD_LAG_PUT);
		}
	}
	P1OUT |= MOSI;									//Stop bit of byte 2
	__delay_cycles(BAUDRATE_MOSI);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	masterGet
 *	Input		:	none
 *	Output		:	arrBuff: the buff memory of Communication module
 */
void masterGet (int arrBuff[])
{
	__delay_cycles(BAUDRATE_MISO - BAUD_LAG_GET);
	arrBuff[0] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[1] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[2] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[3] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[4] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[5] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[6] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[7] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);

	__delay_cycles(DELAY_MS);

	__delay_cycles(BAUDRATE_MISO - BAUD_LAG_GET);
	arrBuff[8] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[9] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[10] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[11] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[12] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[13] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[14] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
	arrBuff[15] = (P1IN & MISO) >> MISO_TRANS;
	__delay_cycles(BAUDRATE_MISO);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	slavePut
 *	Input		:	varByte1: Address and Password
 *					varByte2: Data
 *	Output		:	none
 */
void slavePut (unsigned char varByte1, unsigned char varByte2)
{
	unsigned char varBit;
	int varCount;

	/* Byte1 */
	P1OUT &= ~MISO;									//Start bit of byte 1
	__delay_cycles(BAUDRATE_MISO);
	for (varCount = 0; varCount < 8; varCount++)	//8 data bits of byte 1
	{
		varBit = (varByte1 & arrMask[varCount]) >> varCount;
		if(varBit != 0)
		{
			P1OUT |= varBit<<MISO_TRANS;
			__delay_cycles(BAUDRATE_MISO - BAUD_LAG_PUT);
		}
		else
		{
			P1OUT &= varBit<<MISO_TRANS;
			__delay_cycles(BAUDRATE_MISO - BAUD_LAG_PUT);
		}
	}
	P1OUT |= MISO;									//Stop bit of byte 1
	__delay_cycles(BAUDRATE_MISO);

	/* Delay between 2 bytes */
	__delay_cycles(DELAY_MS);

	/* Byte2 */
	P1OUT &= ~MISO;									//Start bit of byte 2
	__delay_cycles(BAUDRATE_MISO);
	for (varCount = 0; varCount < 8; varCount++)	//8 data bits of byte 2
	{
		varBit = (varByte2 & arrMask[varCount]) >> varCount;
		if(varBit != 0)
		{
			P1OUT |= varBit<<MISO_TRANS;
			__delay_cycles(BAUDRATE_MISO - BAUD_LAG_PUT);
		}
		else
		{
			P1OUT &= varBit<<MISO_TRANS;
			__delay_cycles(BAUDRATE_MISO - BAUD_LAG_PUT);
		}
	}
	P1OUT |= MISO;									//Stop bit of byte 2
	__delay_cycles(BAUDRATE_MISO);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	slaveGet
 *	Input		:	none
 *	Output		:	arrBuff: the buff memory of Communication module
 */
void slaveGet (int arrBuff[])
{
	__delay_cycles(BAUDRATE_MOSI - BAUD_LAG_GET);
	arrBuff[0] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[1] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[2] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[3] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[4] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[5] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[6] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[7] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);

	__delay_cycles(DELAY_MS);

	__delay_cycles(BAUDRATE_MOSI - BAUD_LAG_GET);
	arrBuff[8] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[9] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[10] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[11] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[12] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[13] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[14] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
	arrBuff[15] = (P1IN & MOSI) >> MOSI_TRANS;
	__delay_cycles(BAUDRATE_MOSI);
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	masterCheck
 *	Input		:	arrBuff		 : the buff memory of Communication module
 *	Output		:	arrData		 : get data from arrBuff
 *					varCharacter : carry ASCII of any array[8]
 *					varWrongTimes: the number of of password is wrong
 */
void masterCheck (int arrBuff[], int arrData[], unsigned char varSecurity, unsigned char *varCharacter, int *varWrongtime)
{
	arrayPushLow(arrBuff, arrData);
	*varCharacter = characterConvert(arrData);
	//txdChar(*varCharacter);
	//If address is of this master
	if((*varCharacter & ADDR_BIT) == varAddress)
	{
		ledOn();
		//If password is right
		if((*varCharacter & PASS_BIT) == varPassword)
		{
			arrayPushHigh(arrBuff, arrData);
			*varCharacter = characterConvert(arrData);
			masterRespond(*varCharacter);
			varWrongTimes = 0;
		}
		else
		{
			if (varSecurity == SECURITY_ON)
			{
				varWrongTimes++;
				lockSecurity(varWrongTimes);
			}
		}
		ledOff();
	}
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	slaveCheck
 *	Input		:	arrBuff		 : the buff memory of Communication module
 *	Output		:	arrData		 : get data from arrBuff
 *					varCharacter : carry ASCII of any array[8]
 *					varWrongTimes: the number of of password is wrong
 */
void slaveCheck (int arrBuff[], int arrData[], unsigned char varSecurity, unsigned char *varCharacter, int *varWrongtime)
{
	arrayPushLow(arrBuff, arrData);
	*varCharacter = characterConvert(arrData);
	//txdChar(*varCharacter);
	//If address is of this slave, turn on LED_RED
	if((*varCharacter & ADDR_BIT) == varAddress)
	{
		ledOn();
		//If password is right, turn off LED_RED after 1s
		if((*varCharacter & PASS_BIT) == varPassword)
		{
			arrayPushHigh(arrBuff, arrData);
			*varCharacter = characterConvert(arrData);
			slaveRespond(*varCharacter);
			varWrongTimes = 0;
		}
		else
		{
			if (varSecurity == SECURITY_ON)
			{
				varWrongTimes++;
				lockSecurity(varWrongTimes);
			}
		}
		ledOff();
	}
}
//-----------------------------------------------------------------------------
/*
 *	Function	:	lockSecurity
 *	Input		:	varWrongTimes: the number that password is wrong continuously
 *	Output		:	none
 */
void lockSecurity(int varWrongTimes)
{
	if(varWrongTimes == 5)
	{
		int i;

		P1SEL  = 0;
		P1SEL2 = 0;
		P2SEL  = 0;
		P2SEL2 = 0;
		P1DIR  = 0XFF;
		P2DIR  = 0XFF;
		P1OUT  = 0XFF;
		P2OUT  = 0XFF;

		for(i = 0; i < 16; i++)
		{
			arrBuff[i] = 0;
		}
		for(i = 0; i < 8; i++)
		{
			arrData[i] = 0;
		}
		for(i = 0; i < 8; i++)
		{
			arrMask[i] = 0;
		}

		varCharacter  = 0;
		varWrongTimes = 0;

		for(i = 0; i < 3; i++)
		{
			ledToogle();
			__delay_cycles(1000000);
		}
		_BIS_SR(LPM4);
		while(1);
	}
}


/****************************************************************************************
 *	END OF CommunicationGPIO.c
 ***************************************************************************************/

/*
 * 	File			:	MFRC522_1_0_1.c
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct MFRC522 library
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "MFRC522_1_0_1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
static				uint16_t		rfidPinSS;
static				uint16_t		rfidPinRST;
static	volatile	uint8_t*		rfidPort;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * Function: rfidSetup
 * Description: initilize RC522
 * Input parameter: null
 * Return: null
 */
void rfidSetup (volatile uint8_t* RFID_PORT_, const uint16_t RFID_PIN_SS, const uint16_t PIN_RFID_RST)
{
	rfidPinSS = RFID_PIN_SS;
	rfidPinRST = PIN_RFID_RST;
	rfidPort = RFID_PORT_;

	if(RFID_PORT_ == RFID_PORT_1) gpioSetup(PORT1, rfidPinSS | rfidPinRST, rfidPinSS | rfidPinRST);
	else if(RFID_PORT_ == RFID_PORT_2) gpioSetup(PORT2, rfidPinSS | rfidPinRST, rfidPinSS | rfidPinRST);

	*rfidPort |= rfidPinRST;
	*rfidPort &= ~rfidPinSS;
	__delay_cycles(100000*16);

	*rfidPort |= rfidPinRST;
	rfidReset();
	//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
	rfidWriteReg(TModeReg, 0x8D);		//Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	rfidWriteReg(TPrescalerReg, 0x3E);	//TModeReg[3..0] + TPrescalerReg
	rfidWriteReg(TReloadRegL, 30);
	rfidWriteReg(TReloadRegH, 0);
	rfidWriteReg(TxAutoReg, 0x40);		//100%ASK
	rfidWriteReg(ModeReg, 0x3D);
	//ClearBitMask(Status2Reg, 0x08);		//MFCrypto1On=0
	//WriteReg(RxSelReg, 0x86);		//RxWait = RxSelReg[5..0]
	//WriteReg(RFCfgReg, 0x7F);   		//RxGain = 48dB
	rfidAntennaOn();
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidWriteReg
 * Description: write a byte data into one register of MR RC522
 * Input parameter: addr--register address；val--the value that need to write in
 * Return: Null
 */
void rfidWriteReg(unsigned char addr, unsigned char val)
{
	*rfidPort &= ~rfidPinSS;
	spiA0MstWriteByte((addr<<1) & 0x7E);
	spiA0MstWriteByte(val);
	*rfidPort |= rfidPinSS;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidReadReg
 * Description: read a byte data into one register of MR RC522
 * Input parameter: addr--register address
 * Return: return the read value
 */
unsigned char rfidReadReg(unsigned char addr)
{
	unsigned char val;
	*rfidPort &= ~rfidPinSS;
	spiA0MstWriteByte(((addr << 1) & 0x7E) | 0x80);
	spiA0MstWriteByte(0x00);
	val = spiA0MstReadByte();
	*rfidPort |= rfidPinSS;
	return val;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidSetBitMask
 * Description: set RC522 register bit
 * Input parameter: reg--register address;mask--value
 * Return: null
 */
void rfidSetBitMask(unsigned char reg, unsigned char mask)
{
	unsigned char tmp;
	tmp = rfidReadReg(reg);
	rfidWriteReg(reg, tmp | mask);  // set bit mask
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidClearBitMask
 * Description: clear RC522 register bit
 * Input parameter: reg--register address;mask--value
 * Return: null
 */
void rfidClearBitMask(unsigned char reg, unsigned char mask)
{
	unsigned char tmp;
	tmp = rfidReadReg(reg);
	rfidWriteReg(reg, tmp & (~mask));  // clear bit mask
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidAntennaOn
 * Description: Turn on antenna, every time turn on or shut down antenna need at least 1ms delay
 * Input parameter: null
 * Return: null
 */
void rfidAntennaOn(void)
{
	unsigned char temp;
	temp = rfidReadReg(TxControlReg);
	if (!(temp & 0x03))
	{
		rfidSetBitMask(TxControlReg, 0x03);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidAntennaOff
 * Description: Turn off antenna, every time turn on or shut down antenna need at least 1ms delay
 * Input parameter: null
 * Return: null
 */
void rfidAntennaOff(void)
{
	rfidClearBitMask(TxControlReg, 0x03);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidReset
 * Description:  reset RC522
 * Input parameter: null
 * Return: null
 */
void rfidReset(void)
{
	rfidWriteReg(CommandReg, PCD_RESETPHASE);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidRequest
 * Description: Searching card, read card type
 * Input parameter: reqMode--search methods，
 *			 TagType--return card types
 *			 	0x4400 = Mifare_UltraLight
 *				0x0400 = Mifare_One(S50)
 *				0x0200 = Mifare_One(S70)
 *				0x0800 = Mifare_Pro(X)
 *				0x4403 = Mifare_DESFire
 * Return: return MI_OK if successed
 */
unsigned char rfidRequest(unsigned char reqMode, unsigned char *TagType)
{
	unsigned char status;
	unsigned int backBits;

	rfidWriteReg(BitFramingReg, 0x07);		//TxLastBists = BitFramingReg[2..0]	???

	TagType[0] = reqMode;
	status = rfidToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

	if ((status != MI_OK) || (backBits != 0x10))
	{
		status = MI_ERR;
	}

	return status;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidToCard
 * Description: communicate between RC522 and ISO14443
 * Input parameter: command--MF522 command bits
 *			 sendData--send data to card via rc522
 *			 sendLen--send data length
 *			 backData--the return data from card
 *			 backLen--the length of return data
 * Return: return MI_OK if successed
 */
unsigned char rfidToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned int *backLen)
{
	unsigned char status = MI_ERR;
	unsigned char irqEn = 0x00;
	unsigned char waitIRq = 0x00;
	unsigned char lastBits;
	unsigned char n;
	unsigned int i;
	switch (command)
	{
		case PCD_AUTHENT:
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
	}
	rfidWriteReg(CommIEnReg, irqEn|0x80);
	rfidClearBitMask(CommIrqReg, 0x80);
	rfidSetBitMask(FIFOLevelReg, 0x80);
	rfidWriteReg(CommandReg, PCD_IDLE);
	for (i=0; i<sendLen; i++)
	{
		rfidWriteReg(FIFODataReg, sendData[i]);
	}
	rfidWriteReg(CommandReg, command);
	if (command == PCD_TRANSCEIVE)
	{
		rfidSetBitMask(BitFramingReg, 0x80);		//StartSend=1,transmission of data starts
	}
	i = 2000;
	do
	{
		n = rfidReadReg(CommIrqReg);
		i--;
	}
	while ((i!=0) && !(n&0x01) && !(n&waitIRq));
	rfidClearBitMask(BitFramingReg, 0x80);			//StartSend=0
	if (i != 0)
	{
		if(!(rfidReadReg(ErrorReg) & 0x1B))	//BufferOvfl Collerr CRCErr ProtecolErr
		{
			status = MI_OK;
			if (n & irqEn & 0x01)
			{
				status = MI_NOTAGERR;			//??
			}

			if (command == PCD_TRANSCEIVE)
			{
				n = rfidReadReg(FIFOLevelReg);
				lastBits = rfidReadReg(ControlReg) & 0x07;
				if (lastBits)
				{
					*backLen = (n-1)*8 + lastBits;
				}
				else
				{
					*backLen = n*8;
				}
				if (n == 0)
				{
					n = 1;
				}
				if (n > MAX_LEN)
				{
					n = MAX_LEN;
				}

				for (i=0; i<n; i++)
				{
					backData[i] = rfidReadReg(FIFODataReg);
				}
			}
		}
		else
		{
			status = MI_ERR;
		}
	}
//SetBitMask(ControlReg,0x80);           //timer stops
//WriteReg(CommandReg, PCD_IDLE);
	return status;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidAnticoll
 * Description: Prevent conflict, read the card serial number
 * Input parameter: serNum--return the 4 bytes card serial number, the 5th byte is recheck byte
 * Return: return MI_OK if successed
 */
unsigned char rfidAnticoll(unsigned char *serNum)
{
	unsigned char status;
	unsigned char i;
	unsigned char serNumCheck=0;
	unsigned int unLen;
//ClearBitMask(Status2Reg, 0x08);		//TempSensclear
//ClearBitMask(CollReg,0x80);			//ValuesAfterColl
	rfidWriteReg(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
	serNum[0] = PICC_ANTICOLL;
	serNum[1] = 0x20;
	status = rfidToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

	if (status == MI_OK)
	{
		for (i=0; i<4; i++)
		{
			serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i])
		{
			status = MI_ERR;
		}
	}

	//SetBitMask(CollReg, 0x80);		//ValuesAfterColl=1

	return status;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidCalulateCRC
 * Description: Use MF522 to calculate CRC
 * Input parameter: pIndata--the CRC data need to be read，len--data length，pOutData-- the caculated result of CRC
 * Return: Null
 */
void rfidCalulateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData)
{
	unsigned char i, n;

	rfidClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
	rfidSetBitMask(FIFOLevelReg, 0x80);
	//WriteReg(CommandReg, PCD_IDLE);

	for (i=0; i<len; i++)
	{
		rfidWriteReg(FIFODataReg, *(pIndata+i));
	}
	rfidWriteReg(CommandReg, PCD_CALCCRC);

	i = 0xFF;
	do
	{
		n = rfidReadReg(DivIrqReg);
		i--;
	}
	while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	pOutData[0] = rfidReadReg(CRCResultRegL);
	pOutData[1] = rfidReadReg(CRCResultRegM);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidSelectTag
 * Description: Select card, read card storage volume
 * Input parameter: serNum--Send card serial number
 * Return: return the card storage volume
 */
unsigned char rfidSelectTag(unsigned char *serNum)
{
	unsigned char i;
	unsigned char status;
	unsigned char size;
	unsigned int recvBits;
	unsigned char buffer[9];

	//ClearBitMask(Status2Reg, 0x08);			//MFCrypto1On=0

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i=0; i<5; i++)
	{
		buffer[i+2] = *(serNum+i);
	}
	rfidCalulateCRC(buffer, 7, &buffer[7]);		//??
	status = rfidToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

	if ((status == MI_OK) && (recvBits == 0x18))
	{
		size = buffer[0];
	}
	else
	{
		size = 0;
	}

	return size;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidAuth
 * Description: verify card password
 * Input parameters：authMode--password verify mode
                 0x60 = verify A password key
                 0x61 = verify B password key
             BlockAddr--Block address
             Sectorkey--Block password
             serNum--Card serial number ，4 bytes
 * Return: return MI_OK if successed
 */
unsigned char rfidAuth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum)
{
	unsigned char status;
	unsigned int recvBits;
	unsigned char i;
	unsigned char buff[12];

	buff[0] = authMode;
	buff[1] = BlockAddr;
	for (i=0; i<6; i++)
	{
		buff[i+2] = *(Sectorkey+i);
	}
	for (i=0; i<4; i++)
	{
		buff[i+8] = *(serNum+i);
	}
	status = rfidToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

	if ((status != MI_OK) || (!(rfidReadReg(Status2Reg) & 0x08)))
	{
		status = MI_ERR;
	}

	return status;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidReadBlock
 * Description: Read data
 * Input parameters：blockAddr--block address;recvData--the block data which are read
 * Return: return MI_OK if successed
 */
unsigned char rfidReadBlock(unsigned char blockAddr, unsigned char *recvData)
{
	unsigned char status;
	unsigned int unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;
	rfidCalulateCRC(recvData,2, &recvData[2]);
	status = rfidToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

	if ((status != MI_OK) || (unLen != 0x90))
	{
		status = MI_ERR;
	}

	return status;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidWriteBlock
 * Description: write block data
 * Input parameters：blockAddr--block address;writeData--Write 16 bytes data into block
 * Return: return MI_OK if successed
 */
unsigned char rfidWriteBlock(unsigned char blockAddr, unsigned char *writeData)
{
	unsigned char status;
	unsigned int recvBits;
	unsigned char i;
	unsigned char buff[18];

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;
	rfidCalulateCRC(buff, 2, &buff[2]);
	status = rfidToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

	if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
	{
		status = MI_ERR;
	}

	if (status == MI_OK)
	{
		for (i=0; i<16; i++)
		{
			buff[i] = *(writeData+i);
		}
		rfidCalulateCRC(buff, 16, &buff[16]);
		status = rfidToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
		{
			status = MI_ERR;
		}
	}

	return status;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function: rfidHalt
 * Description: Command the cards into sleep mode
 * Input parameters：null
 * Return: null
 */
void rfidHalt(void)
{
	//unsigned char status;
	//unsigned int unLen;
	unsigned char buff[4];

	buff[0] = PICC_HALT;
	buff[1] = 0;
	rfidCalulateCRC(buff, 2, &buff[2]);

	//status = rfidToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function		: rfidGetCardData
 * Description	: Get data from card
 * Input		: none
 * Output		: arrID: ID number of card
 */
unsigned char rfidGetCardID (unsigned char arrID[])
{
	unsigned char varStatus;
	unsigned char strString[MAX_LEN];
	rfidRequest(PICC_REQIDL, strString);
	varStatus = rfidAnticoll(strString);
	memcpy(arrID, strString, 5);
	return varStatus;
}

/**************************************************************************************************
 *	END OF MFRC522_1_0_1.c
 *************************************************************************************************/

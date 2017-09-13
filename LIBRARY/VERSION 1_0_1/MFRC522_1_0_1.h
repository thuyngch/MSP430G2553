/*
 * 	File			:	MFRC522_1_0_1.h
 * 	Author			:	Nguyen Chinh Thuy
 *	Date created	:	31/05/2016
 *	Tool			: 	CCS6.1.2.00015
 *	Current version	:	1.0.1
 *	Description		:	Construct MFRC522 library
 */

/**************************************************************************************************
 *										PIN MAP
 *									   ---------
 *							RFID Module       MSP430 LaunchPads
 *							--------------    -----------------
 *							Pin 1  (SDA)      P2.0  (CS)
 *							Pin 2  (SCK)      P1.5  (SCK)
 *							Pin 3  (MOSI)     P1.7 (MOSI)
 *							Pin 4  (MISO)     P1.6 (MISO)
 *							Pin 5  (IRQ)      Not connected
 *							Pin 6  (GND)      GND
 *							Pin 7  (RST)      P2.2
 *							Pin 8  (3V3)      3V3
 *************************************************************************************************/
#ifndef MFRC522_1_0_1_H_
#define MFRC522_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include <stdint.h>
#include <msp430.h>
#include "GPIO_1_0_1.h"
#include "USCI_SPI_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Hardware */
#define		RFID_PORT_1			(&P1OUT)
#define		RFID_PORT_2			(&P2OUT)

/* Maximum length of string */
#define 	MAX_LEN				16

/* MF522 - Commands */
#define 	PCD_IDLE			0x00
#define 	PCD_AUTHENT			0x0E
#define 	PCD_RECEIVE			0x08
#define 	PCD_TRANSMIT		0x04
#define 	PCD_TRANSCEIVE		0x0C
#define 	PCD_RESETPHASE		0x0F
#define 	PCD_CALCCRC			0x03

/* Mifare_One - Commands */
#define 	PICC_REQIDL			0x26
#define 	PICC_REQALL			0x52
#define 	PICC_ANTICOLL		0x93
#define 	PICC_SElECTTAG		0x93
#define 	PICC_AUTHENT1A		0x60
#define 	PICC_AUTHENT1B		0x61
#define 	PICC_READ			0x30
#define 	PICC_WRITE			0xA0
#define 	PICC_DECREMENT		0xC0
#define 	PICC_INCREMENT		0xC1
#define 	PICC_RESTORE		0xC2
#define 	PICC_TRANSFER		0xB0
#define 	PICC_HALT			0x50

/* MF522 - Status */
#define 	MI_OK				0
#define 	MI_NOTAGERR			1
#define 	MI_ERR				2

/* MF522 - Registers */
// Page 0: Command and Status //
#define     Reserved00			0x00
#define     CommandReg			0x01
#define     CommIEnReg			0x02
#define     DivlEnReg			0x03
#define     CommIrqReg			0x04
#define     DivIrqReg			0x05
#define     ErrorReg			0x06
#define     Status1Reg			0x07
#define     Status2Reg			0x08
#define     FIFODataReg			0x09
#define     FIFOLevelReg		0x0A
#define     WaterLevelReg		0x0B
#define     ControlReg			0x0C
#define     BitFramingReg		0x0D
#define     CollReg				0x0E
#define     Reserved01			0x0F
// Page 1: Command //
#define     Reserved10			0x10
#define     ModeReg				0x11
#define     TxModeReg			0x12
#define     RxModeReg			0x13
#define     TxControlReg		0x14
#define     TxAutoReg			0x15
#define     TxSelReg			0x16
#define     RxSelReg			0x17
#define     RxThresholdReg		0x18
#define     DemodReg			0x19
#define     Reserved11			0x1A
#define     Reserved12			0x1B
#define     MifareReg			0x1C
#define     Reserved13			0x1D
#define     Reserved14			0x1E
#define     SerialSpeedReg		0x1F
// Page 2: CFG //
#define     Reserved20			0x20
#define     CRCResultRegM		0x21
#define     CRCResultRegL		0x22
#define     Reserved21			0x23
#define     ModWidthReg			0x24
#define     Reserved22			0x25
#define     RFCfgReg			0x26
#define     GsNReg				0x27
#define     CWGsPReg			0x28
#define     ModGsPReg			0x29
#define     TModeReg			0x2A
#define     TPrescalerReg		0x2B
#define     TReloadRegH			0x2C
#define     TReloadRegL			0x2D
#define     TCounterValueRegH	0x2E
#define     TCounterValueRegL	0x2F
// Page 3: TestRegister //
#define     Reserved30			0x30
#define     TestSel1Reg			0x31
#define     TestSel2Reg			0x32
#define     TestPinEnReg		0x33
#define     TestPinValueReg		0x34
#define     TestBusReg			0x35
#define     AutoTestReg			0x36
#define     VersionReg			0x37
#define     AnalogTestReg		0x38
#define     TestDAC1Reg			0x39
#define     TestDAC2Reg			0x3A
#define     TestADCReg			0x3B
#define     Reserved31			0x3C
#define     Reserved32			0x3D
#define     Reserved33			0x3E
#define     Reserved34			0x3F


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
void rfidSetup (volatile uint8_t* RFID_PORT_, const uint16_t RFID_PIN_SS, const uint16_t PIN_RFID_RST);

void rfidWriteReg (unsigned char addr, unsigned char val);
unsigned char rfidReadReg (unsigned char addr);
void rfidSetBitMask (unsigned char reg, unsigned char mask);
void rfidClearBitMask (unsigned char reg, unsigned char mask);
void rfidAntennaOn (void);
void rfidAntennaOff (void);
void rfidReset (void);
unsigned char rfidRequest (unsigned char reqMode, unsigned char *TagType);
unsigned char rfidToCard (unsigned char command, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned int *backLen);
unsigned char rfidAnticoll (unsigned char *serNum);
void rfidCalulateCRC (unsigned char *pIndata, unsigned char len, unsigned char *pOutData);
unsigned char rfidSelectTag (unsigned char *serNum);
unsigned char rfidAuth (unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum);
unsigned char rfidReadBlock (unsigned char blockAddr, unsigned char *recvData);
unsigned char rfidWriteBlock (unsigned char blockAddr, unsigned char *writeData);
void rfidHalt (void);
unsigned char rfidGetCardID (unsigned char arrID[]);


/**************************************************************************************************
 *	END OF MFRC522_1_0_1.h
 *************************************************************************************************/
#endif /* MFRC522_1_0_1_H_ */

/*
 *	File			:	ESP8266_1_0_1.c
 *	Date created	:	30/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	MSP430G2553
 *	Current version	:	1.0.1
 *	Description		:	Library of ESP8266
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "ESP8266_1_0_1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
static	volatile	uint8_t*	ESP8266_PORT;
static				uint16_t	ESP8266_PIN_RST;
static				uint16_t	ESP8266_PIN_EN;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
 /*
  * Function:	esp8266Setup
  * Purpose	:
  * Input	:
  * Output	:	None
  */
void
esp8266Setup (volatile uint8_t* ESP8266_PORT_, const uint16_t ESP8266_PIN_RST_,
																const uint16_t ESP8266_PIN_EN_)
{
	/* Assign pins */
	ESP8266_PORT 	= ESP8266_PORT_;
	ESP8266_PIN_RST	= ESP8266_PIN_RST_;
	ESP8266_PIN_EN	= ESP8266_PIN_EN_;

	/* Setup GPIO */
	if(ESP8266_PORT == ESP8266_PORT_1)
		gpioSetup(PORT1, ESP8266_PIN_RST | ESP8266_PIN_EN, ESP8266_PIN_RST | ESP8266_PIN_EN);
	else if(ESP8266_PORT == ESP8266_PORT_2)
		gpioSetup(PORT2, ESP8266_PIN_RST | ESP8266_PIN_EN, ESP8266_PIN_RST | ESP8266_PIN_EN);

	/* Enable module */
	*ESP8266_PORT	|= ESP8266_PIN_EN;

	/* Reset by Hardware */
	esp8266ResetHardware();
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266CheckModule(void)
{
	txdStr(ESP8266_AT_CHECK_MODULE);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
void
esp8266ResetHardware(void)
{
	*ESP8266_PORT	&= ~ESP8266_PIN_RST;
	__delay_cycles(1000);
	*ESP8266_PORT	|= 	ESP8266_PIN_RST;
	__delay_cycles(1000);
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266ResetSofware(void)
{
	txdStr(ESP8266_AT_RESET);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266CheckFirmware(void)
{
	txdStr(ESP8266_AT_CHECK_FIRMWARE);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266ConnectWifi(char strSSID[], char strPassword[])
{
	char strBuff[50];
	strcpy(strBuff, ESP8266_AT_CONNECT_WIFI);
	strcat(strBuff, "\"");
	strcat(strBuff, strSSID);
	strcat(strBuff, "\",\"");
	strcat(strBuff, strPassword);
	strcat(strBuff, "\"\r\n");

	txdStr((uint8_t*)strBuff);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266DisconnectWifi(void)
{
	txdStr(ESP8266_AT_CONNECT_WIFI);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266MakeServer(uint16_t varPort)
{
	char strPort[6];
	sprintf(strPort, "%d", varPort);

	char strBuff[25];
	strcpy(strBuff, ESP8266_AT_MAKE_SERVER);
	strcat(strBuff, strPort);
	strcat(strBuff, "\r\n");

	txdStr((uint8_t*)strBuff);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266SingleConnection(void)
{
	txdStr(ESP8266_AT_SET_TCP_SINGLE);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266MultiConnection(void)
{
	txdStr(ESP8266_AT_SET_TCP_MULTI);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266GetIP(void)
{
	txdStr(ESP8266_AT_GET_IP);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266ConnectTCP(char strIPAddr[], uint16_t varPort)
{
	char strPort[6];
	sprintf(strPort, "%d", varPort);

	char strBuff[50];
	strcpy(strBuff, ESP8266_AT_CONNECT_TCP);
	strcat(strBuff, "\"TCP\",\"");
	strcat(strBuff, strIPAddr);
	strcat(strBuff, "\",");
	strcat(strBuff, strPort);
	strcat(strBuff, "\r\n");

	txdStr((uint8_t*)strBuff);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266DisconnectTCP(void)
{
	txdStr(ESP8266_AT_DISCONNECT_TCP);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
bool
esp8266ChecStatus(void)
{
	txdStr(ESP8266_AT_CHECK_STATUS);
	return false;
}
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
//-------------------------------------------------------------------------------------------------
 /*
  * Function:
  * Purpose	:
  * Input	:
  * Output	:
  */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF ESP8266_1_0_1.c
 *************************************************************************************************/

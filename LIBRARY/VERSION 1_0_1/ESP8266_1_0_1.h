/*
 *	File			:	ESP8266_1_0_1.h
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
#ifndef ESP8266_1_0_1_H_
#define ESP8266_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Producing Library */
#include <msp430g2553.h>

/* My Library */
#include "GPIO_1_0_1.h"
#include "USCI_UART_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* GPIO PORT */
#define	ESP8266_PORT_1							(&P1OUT)
#define	ESP8266_PORT_2							(&P2OUT)

/* AT commands */
#define	ESP8266_AT_CHECK_MODULE					"AT\r\n"
#define	ESP8266_AT_RESET						"AT+RST\r\n"
#define	ESP8266_AT_CHECK_FIRMWARE				"AT+GMR\r\n"

#define	ESP8266_AT_CONNECT_WIFI					"AT+CWJAP="
#define	ESP8266_AT_DISCONNECT_WIFI				"AT+CWQAP\r\n"
#define	ESP8266_AT_GET_IP						"AT+CIFSR\r\n"

#define	ESP8266_AT_SET_TCP_SINGLE				"AT+CIPMUX=0\r\n"
#define	ESP8266_AT_SET_TCP_MULTI				"AT+CIPMUX=1\r\n"
#define	ESP8266_AT_MAKE_SERVER					"AT+CIPSERVER=1,"
#define	ESP8266_AT_CONNECT_TCP					"AT+CIPSTART="
#define	ESP8266_AT_DISCONNECT_TCP				"AT+CIPCLOSE\r\n"

#define	ESP8266_AT_CHECK_STATUS					"AT+CIPSTATUS\r\n"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void
esp8266Setup 			(volatile uint8_t* ESP8266_PORT_, const uint16_t ESP8266_PIN_RST_,
																const uint16_t ESP8266_PIN_EN_);

/* Control */
bool
esp8266CheckModule		(void);
void
esp8266ResetHardware	(void);
bool
esp8266ResetSofware		(void);
bool
esp8266CheckFirmware	(void);

/* Wifi */
bool
esp8266ConnectWifi		(char strSSID[], char strPassword[]);
bool
esp8266DisconnectWifi	(void);
bool
esp8266GetIP			(void);

/* TCP */
bool
esp8266ConnectTCP		(char strIPAddr[], uint16_t varPort);
bool
esp8266DisconnectTCP	(void);
bool
esp8266MakeServer		(uint16_t varPort);
bool
esp8266SingleConnection	(void);
bool
esp8266MultiConnection	(void);

/* Status */
void
esp8266CheckStatus		(void);


/**************************************************************************************************
 *	END OF ESP8266_1_0_1.h
 *************************************************************************************************/
#endif /* ESP8266_1_0_1_H_ */

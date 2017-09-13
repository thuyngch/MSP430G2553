/*
 *	File			:	MPU6050_1_0_1.h
 *	Date created	:	14/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct MPU6050 library
 *	Target object	:	MSP430G2553
 */
#define USE_USCI_UART_1_2_3
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about MPU6050.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
#ifndef MPU6050_1_0_1_H_
#define MPU6050_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include <math.h>
#include "VERSION 1_2_3/USCI_UART_1_2_3.h"
#include "USCI_I2C_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Addresses of MPU6050 */
#define 	MPU6050_ADDRESS 				0x68

#define 	MPU6050_XG_OFFS_TC 				0x00
#define 	MPU6050_YG_OFFS_TC 				0x01
#define 	MPU6050_ZG_OFFS_TC 				0x02
#define 	MPU6050_X_FINE_GAIN 			0x03
#define 	MPU6050_Y_FINE_GAIN 			0x04
#define 	MPU6050_Z_FINE_GAIN 			0x05
#define 	MPU6050_XA_OFFS_H 				0x06
#define 	MPU6050_XA_OFFS_L_TC 			0x07
#define 	MPU6050_YA_OFFS_H 				0x08
#define 	MPU6050_YA_OFFS_L_TC 			0x09
#define 	MPU6050_ZA_OFFS_H 				0x0A
#define 	MPU6050_ZA_OFFS_L_TC 			0x0B
#define 	MPU6050_XG_OFFS_USRH 			0x13
#define 	MPU6050_XG_OFFS_USRL 			0x14
#define 	MPU6050_YG_OFFS_USRH 			0x15
#define 	MPU6050_YG_OFFS_USRL 			0x16
#define 	MPU6050_ZG_OFFS_USRH 			0x17
#define 	MPU6050_ZG_OFFS_USRL 			0x18
#define 	MPU6050_SMPLRT_DIV 				0x19
#define 	MPU6050_CONFIG 					0x1A
#define 	MPU6050_GYRO_CONFIG 			0x1B
#define 	MPU6050_ACCEL_CONFIG 			0x1C
#define 	MPU6050_FF_THR 					0x1D
#define 	MPU6050_FF_DUR 					0x1E
#define 	MPU6050_MOT_THR 				0x1F
#define 	MPU6050_MOT_DUR 				0x20
#define 	MPU6050_ZRMOT_THR 				0x21
#define 	MPU6050_ZRMOT_DUR 				0x22
#define 	MPU6050_FIFO_EN 				0x23
#define 	MPU6050_I2C_MST_CTRL 			0x24
#define 	MPU6050_I2C_SLV0_ADDR 			0x25
#define 	MPU6050_I2C_SLV0_REG 			0x26
#define 	MPU6050_I2C_SLV0_CTRL 			0x27
#define 	MPU6050_I2C_SLV1_ADDR 			0x28
#define 	MPU6050_I2C_SLV1_REG 			0x29
#define 	MPU6050_I2C_SLV1_CTRL 			0x2A
#define 	MPU6050_I2C_SLV2_ADDR 			0x2B
#define 	MPU6050_I2C_SLV2_REG 			0x2C
#define 	MPU6050_I2C_SLV2_CTRL 			0x2D
#define 	MPU6050_I2C_SLV3_ADDR 			0x2E
#define 	MPU6050_I2C_SLV3_REG 			0x2F
#define 	MPU6050_I2C_SLV3_CTRL 			0x30
#define 	MPU6050_I2C_SLV4_ADDR 			0x31
#define 	MPU6050_I2C_SLV4_REG 			0x32
#define 	MPU6050_I2C_SLV4_DO 			0x33
#define 	MPU6050_I2C_SLV4_CTRL 			0x34
#define 	MPU6050_I2C_SLV4_DI 			0x35
#define 	MPU6050_I2C_MST_STATUS 			0x36
#define 	MPU6050_INT_PIN_CFG 			0x37
#define 	MPU6050_INT_ENABLE 				0x38
#define 	MPU6050_DMP_INT_STATUS 			0x39
#define 	MPU6050_INT_STATUS 				0x3A
#define 	MPU6050_ACCEL_XOUT_H 			0x3B
#define 	MPU6050_ACCEL_XOUT_L 			0x3C
#define	 	MPU6050_ACCEL_YOUT_H 			0x3D
#define 	MPU6050_ACCEL_YOUT_L 			0x3E
#define 	MPU6050_ACCEL_ZOUT_H 			0x3F
#define 	MPU6050_ACCEL_ZOUT_L 			0x40
#define 	MPU6050_TEMP_OUT_H 				0x41
#define 	MPU6050_TEMP_OUT_L 				0x42
#define 	MPU6050_GYRO_XOUT_H 			0x43
#define 	MPU6050_GYRO_XOUT_L 			0x44
#define 	MPU6050_GYRO_YOUT_H 			0x45
#define 	MPU6050_GYRO_YOUT_L 			0x46
#define 	MPU6050_GYRO_ZOUT_H 			0x47
#define 	MPU6050_GYRO_ZOUT_L 			0x48
#define 	MPU6050_EXT_SENS_DATA_00 		0x49
#define 	MPU6050_EXT_SENS_DATA_01 		0x4A
#define 	MPU6050_EXT_SENS_DATA_02 		0x4B
#define 	MPU6050_EXT_SENS_DATA_03 		0x4C
#define 	MPU6050_EXT_SENS_DATA_04 		0x4D
#define 	MPU6050_EXT_SENS_DATA_05 		0x4E
#define 	MPU6050_EXT_SENS_DATA_06 		0x4F
#define 	MPU6050_EXT_SENS_DATA_07 		0x50
#define 	MPU6050_EXT_SENS_DATA_08 		0x51
#define 	MPU6050_EXT_SENS_DATA_09 		0x52
#define 	MPU6050_EXT_SENS_DATA_10 		0x53
#define	 	MPU6050_EXT_SENS_DATA_11 		0x54
#define 	MPU6050_EXT_SENS_DATA_12 		0x55
#define 	MPU6050_EXT_SENS_DATA_13 		0x56
#define 	MPU6050_EXT_SENS_DATA_14 		0x57
#define 	MPU6050_EXT_SENS_DATA_15 		0x58
#define 	MPU6050_EXT_SENS_DATA_16 		0x59
#define 	MPU6050_EXT_SENS_DATA_17 		0x5A
#define 	MPU6050_EXT_SENS_DATA_18 		0x5B
#define 	MPU6050_EXT_SENS_DATA_19 		0x5C
#define 	MPU6050_EXT_SENS_DATA_20 		0x5D
#define 	MPU6050_EXT_SENS_DATA_21 		0x5E
#define 	MPU6050_EXT_SENS_DATA_22 		0x5F
#define 	MPU6050_EXT_SENS_DATA_23 		0x60
#define 	MPU6050_MOT_DETECT_STATUS 		0x61
#define 	MPU6050_I2C_SLV0_DO 			0x63
#define 	MPU6050_I2C_SLV1_DO 			0x64
#define 	MPU6050_I2C_SLV2_DO 			0x65
#define 	MPU6050_I2C_SLV3_DO 			0x66
#define 	MPU6050_I2C_MST_DELAY_CTRL 		0x67
#define 	MPU6050_SIGNAL_PATH_RESET 		0x68
#define 	MPU6050_MOT_DETECT_CTRL 		0x69
#define 	MPU6050_USER_CTRL 				0x6A
#define 	MPU6050_PWR_MGMT_1 				0x6B
#define 	MPU6050_PWR_MGMT_2 				0x6C
#define 	MPU6050_BANK_SEL 				0x6D
#define 	MPU6050_MEM_START_ADDR 			0x6E
#define 	MPU6050_MEM_R_W 				0x6F
#define 	MPU6050_DMP_CFG_1 				0x70
#define 	MPU6050_DMP_CFG_2 				0x71
#define 	MPU6050_FIFO_COUNTH 			0x72
#define 	MPU6050_FIFO_COUNTL 			0x73
#define 	MPU6050_FIFO_R_W 				0x74
#define 	MPU6050_WHO_AM_I 				0x75


#ifndef USE_MPU6050_1_0_1
	/* Arraies and variables */
	long GYRO_XFilter[4], GYRO_YFilter[4], GYRO_ZFilter[4];
	long ACCEL_XFilter[10], ACCEL_YFilter[10], ACCEL_ZFilter[10];
	long G_Filter[4];

	/* Error values of MPU6050 */
	unsigned int	TEMP_OUT = 0;
	
	int				GYRO_XOUT = 0,
					GYRO_YOUT = 0,
					GYRO_ZOUT = 0,
					
					GYRO_XOUT_OFFSET = 250,//-237,//104,
					GYRO_YOUT_OFFSET = -170,//-9,
					GYRO_ZOUT_OFFSET = 8,//-197,
					
					GYRO_XRATE = 0,
					GYRO_YRATE = 0,
					GYRO_ZRATE = 0,
					
					GYRO_XANGLE = 0,
					GYRO_YANGLE = 0,
					GYRO_ZANGLE = 0,
					
					gyrotio = 4;

	char			dt = 1;		// Derivative of time => Sampling
	
	int				ACCEL_XOUT = 0,
					ACCEL_YOUT = 0,
					ACCEL_ZOUT = 0,
					
					ACCEL_XOFFSET,
					ACCEL_YOFFSET,
					ACCEL_ZOFFSET,

					ACCEL_XOUT_PAST = 0,
					ACCEL_YOUT_PAST = 0,
					ACCEL_ZOUT_PAST = 0,
					
					ACCEL_XA    = 0,
					ACCEL_YA    = 0,
					ACCEL_ZA    = 0,
					
					ACCEL_XV    = 0,
					ACCEL_YV    = 0,
					ACCEL_ZV    = 0,
					
					ACCEL_XDECAC = 0,
					ACCEL_YDECAC = 0,
					ACCEL_ZDECAC = 0;

	float			ACCEL_XANGLE = 0,
					ACCEL_YANGLE = 0,
					ACCEL_ZANGLE = 0;

	long			Decac_X0 = 0,
					Decac_X1 = 0,
					
					Decac_Y0 = 0,
					Decac_Y1 = 0,
					
					Decac_Z0 = 0,
					Decac_Z1 = 0;
#endif	/* USE_MPU6050 */


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* MPU6050 */
void mpu6050Setup(void);
void mpu6050TestI2c(void);
unsigned char mpu6050CheckRegister(void);
void mpu6050CalibGyro(void);

void mpu6050GetGyroValue(void);
void mpu6050GetGyroRate(void);
void mpu6050GetAccelValue(void);
void mpu6050GetAccelDescartes(void);
void mpu6050GetAccelAngle(void);
unsigned int mpu6050GetTempValue(void);

//void mpu6050TestGyroValue(void);
//void mpu6050TestGyroRate(void);
//void mpu6050TestAccelValue(void);

/* Filters */
void mpu6050FilterG(void);
void mpu6050FilterGyro(void);
void mpu6050FilterAccel(void);

/* Print result */
void mpu6050PrintGyroValue(void);
void mpu6050PrintAccelValue(void);
void mpu6050PrintAccelAngle(void);


/**************************************************************************************************
 *	END OF MPU6050_1_0_1.h
 *************************************************************************************************/
#endif /* MPU6050_1_0_1_H_ */

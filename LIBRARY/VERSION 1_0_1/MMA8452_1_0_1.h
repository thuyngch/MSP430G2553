/*
 *	File			:	MMA8452_1_0_1.h
 *	Date created	:	04/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct MMA8452 library
 *	Target object	:	MSP430G2553
 */
 /*************************************************************************************************
 *						PROGRESS
 *		This is the version 1.0.1 of this library about MMA8452.
 *		In this version, functions operate with parameters as const unsigned char/int numbers.
 *************************************************************************************************/
#ifndef MMA8452_1_0_1_H_
#define MMA8452_1_0_1_H_
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include <msp430.h>
#include "VERSION 1_0_1/USCI_I2C_1_0_1.h"
#include "VERSION 1_0_1/GPIO_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* ID & address of MMA8452 */
#define			MMA8452_ADDRESS				0x1D
#define			MMA8452_ID					0x2A	// Also the address in I2C communication

/* Registers of MMA8452 */
#define			MMA8452_STATUS				0x00	// Overwrite data, data ready
#define			MMA8452_OUT_X_MSB			0x01	// Value X
#define			MMA8452_OUT_X_LSB			0x02	// Value X
#define			MMA8452_OUT_Y_MSB			0x03	// Value Y
#define			MMA8452_OUT_Y_LSB			0x04	// Value Y
#define			MMA8452_OUT_Z_MSB			0x05	// Value Z
#define			MMA8452_OUT_Z_LSB			0x06	// Value Z
#define			MMA8452_RESERVED1			0x07	//
#define			MMA8452_RESERVED2			0x08	//
#define			MMA8452_SYSMOD				0x0B	// Standby, wake, sleep mode
#define			MMA8452_INT_SOURCE			0x0C	// System interrupt status
#define			MMA8452_WHO_AM_I			0x0D	// Device ID
#define			MMA8452_XYZ_DATA_CFG		0x0E	// Dynamic range, high-pass filter
#define			MMA8452_HP_FILTER_CUTOFF	0x0F	// Highpass cutoff fre, pulse processing function
#define			MMA8452_PL_STATUS			0x10	// Portrait/Landscape status
#define			MMA8452_PL_CFG				0x11	// Portrait/Landscape configuration
#define			MMA8452_PL_COUNT			0x12	// Portrait/landscape debounce counter
#define			MMA8452_PL_BF_ZCOMP			0x13	// Back/front and Z compensation
#define			MMA8452_PL_THS_REG			0x14	// Portrait/landscape threshold and hysteresis
#define			MMA8452_FF_MT_CFG			0x15	// Freefall/motion configuration
#define			MMA8452_FF_MT_SRC			0x16	// Freefall/motion source
#define			MMA8452_FF_MT_THS			0x17	// Freefall/motion threshold
#define			MMA8452_FF_MT_COUNT			0x18	// Freefall/motion debounce
#define			MMA8452_RESERVED3			0x19	//
#define			MMA8452_RESERVED4			0x1A	//
#define			MMA8452_RESERVED5			0x1B	//
#define			MMA8452_RESERVED6			0x1C	//
#define			MMA8452_TRANSIENT_CFG		0x1D	// Transient configuration
#define			MMA8452_TRANSIENT_SRC		0x1E	// Transient source
#define			MMA8452_TRANSIENT_THS		0x1F	// Transient threshold
#define			MMA8452_TRANSIENT_COUNT		0x20	// Transient debounce
#define			MMA8452_PULSE_CFG			0x21	// Pulse configuration
#define			MMA8452_PULSE_SRC			0x22	// Pulse source
#define			MMA8452_PULSE_THSX			0x23	// Pulse threshold X
#define			MMA8452_PULSE_THSY			0x24	// Pulse threshold Y
#define			MMA8452_PULSE_THSZ			0x25	// Pulse threshold Z
#define			MMA8452_PULSE_TMLT			0x26	// Pulse time window 1
#define			MMA8452_PULSE_LTCY			0x27	// Pulse latency timer
#define			MMA8452_PULSE_WIND			0x28	// Pulse time window 2
#define			MMA8452_ASLP_COUNT			0x29	// Auto-wake/sleep count
#define			MMA8452_CTRL_REG1			0x2A	// Control 1
#define			MMA8452_CTRL_REG2			0x2B	// Control 2
#define			MMA8452_CTRL_REG3			0x2C	// Control 3

/* State of MMA8452 */
#define			MMA8452_STATE_ADDR_FALSE			0	// Wrong ID address
#define			MMA8452_STATE_SETUP_SUCCESS			1
#define			MMA8452_STATE_DATA_AVAILABLE		2
#define			MMA8452_STATE_DATA_UNAVAILABLE		3
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_
#define			MMA8452_STATE_

/* Length of filter */
#define			MMA8452_FILTER_LENGTH				5

/* Scale */
#define			MMA8452_SCALE_2						0x00
#define			MMA8452_SCALE_4						0x01
#define			MMA8452_SCALE_8						0x02

/* Output Data Rate */
#define			MMA8452_ODR_800HZ					0x00
#define			MMA8452_ODR_400HZ					0x08
#define			MMA8452_ODR_200HZ					0x10
#define			MMA8452_ODR_100HZ					0x18
#define			MMA8452_ODR_50HZ					0x20
#define			MMA8452_ODR_12_5HZ					0x28
#define			MMA8452_ODR_6_25HZ					0x30
#define			MMA8452_ODR_1_56HZ					0x38

/* Struct */
typedef struct
{
	unsigned char varScaleRange;
	unsigned char varOutDataRate;
	unsigned char varThsX;
	unsigned char varThsY;
	unsigned char varThsZ;
} mma8452_Parameter;
typedef struct
{
	unsigned int 	arrX_Uint[MMA8452_FILTER_LENGTH],	// Used in normal read mode (16-bit)
					arrY_Uint[MMA8452_FILTER_LENGTH],
					arrZ_Uint[MMA8452_FILTER_LENGTH];
	unsigned char 	arrX_Byte[MMA8452_FILTER_LENGTH],	// Used in fast read mode (8-MSB-bit)
					arrY_Byte[MMA8452_FILTER_LENGTH],
					arrZ_Byte[MMA8452_FILTER_LENGTH];
} mma8452_Accel_Filter;
typedef struct
{
	unsigned int 	varX_Uint,	// Used in normal read mode (16-bit)
					varY_Uint,
					varZ_Uint;
	unsigned char 	varX_Byte,	// Used in fast read mode (8-MSB-bit)
					varY_Byte,
					varZ_Byte;
} mma8452_Accel_Value;
typedef struct
{
	unsigned int 	varX_Uint,	// Used in normal read mode (16-bit)
					varY_Uint,
					varZ_Uint;
	unsigned char 	varX_Byte,	// Used in fast read mode (8-MSB-bit)
					varY_Byte,
					varZ_Byte;
} mma8452_Accel_Angle;
typedef struct
{
	unsigned int 	varX_Uint,	// Used in normal read mode (16-bit)
					varY_Uint,
					varZ_Uint;
	unsigned char 	varX_Byte,	// Used in fast read mode (8-MSB-bit)
					varY_Byte,
					varZ_Byte;
} mma8452_Accel_Offset;


/**************************************************************************************************
 *	GLOBALs
 *************************************************************************************************/
#ifndef USE_MMA8452_1_0_1

	/* Scale of range */
	mma8452_Parameter sMma8452Parameter;

	/* Accel filter */
	mma8452_Accel_Filter sMma8452AccelFilter;

	/* Accel Output */
	mma8452_Accel_Value sMma8452AccelValue;

	/* Accel Angle */
	mma8452_Accel_Angle sMma8452AccelAngle;

	/* Accel Offset */
	mma8452_Accel_Offset sMma8452AccelOffset;

#endif	/* USE_MMA8452_1_0_1 */


/**************************************************************************************************
 *	FUNCTION'S PROTOTYPEs
 *************************************************************************************************/
/* MMA8452 */
unsigned char mma8452Setup (unsigned char varScale, unsigned char varOutDataRate,
							unsigned char varThsX, unsigned char varThsY, unsigned char varThsZ);
unsigned char mma8452DataAvailable (void);
void mma8452GetAccelValue(void);
void mma8452GetAccelAngle(void);

/* Filters */
void mma8452FilterAccel(void);

/* Print result */
void mma8452PrintAccelValue(void);
void mma8452PrintAccelAngle(void);


/**************************************************************************************************
 *	END OF MMA8452_1_0_1.h
 *************************************************************************************************/
#endif /* MMA8452_1_0_1_H_ */

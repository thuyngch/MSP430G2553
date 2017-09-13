/*
 *	File			:	MMA8452_1_0_1.c
 *	Date created	:	04/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct MMA8452 library
 *	Target object	:	MSP430G2553
 */
 #define	USE_MMA8452_1_0_1
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "MMA8452_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Externals */
extern mma8452_Parameter 	sMma8452Parameter;
extern mma8452_Accel_Filter	sMma8452AccelFilter;
extern mma8452_Accel_Value	sMma8452AccelValue;
extern mma8452_Accel_Offset	sMma8452AccelOffset;
extern mma8452_Accel_Angle	sMma8452AccelAngle;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	mma8452Setup
 *	Purpose	:	Setup MMA8452 module
 * 	Input	:	varScale:
 * 				varOutDataRate:
 * 				varThsX:
 * 				varThsY:
 * 				varThsZ:
 * 	Output	:	State of MMA8452
 */
unsigned char mma8452Setup (unsigned char varScale, unsigned char varDataRate,
							unsigned char varThsX, unsigned char varThsY, unsigned char varThsZ)
{
	//-Set scale range-//
	sMma8452Parameter.varScaleRange = varScale;
	sMma8452Parameter.varOutDataRate = varDataRate;
	sMma8452Parameter.varThsX = varThsX;
	sMma8452Parameter.varThsY = varThsY;
	sMma8452Parameter.varThsZ = varThsZ;

	//-Check ID address-//
	unsigned char varBuff;
	varBuff = i2cMstReadByte(MMA8452_WHO_AM_I);
	if(varBuff != MMA8452_ID)
	{
		return MMA8452_STATE_ADDR_FALSE;	// if wrong ID addr
	}

	//-Standby-//
	varBuff = i2cMstReadByte(MMA8452_CTRL_REG1);
	i2cMstWriteByte(MMA8452_CTRL_REG1, (varBuff & (~0x01)));

	//-Scale-//
	varBuff = i2cMstReadByte(MMA8452_XYZ_DATA_CFG);
	varBuff &= 0xFC;
	varBuff |= sMma8452Parameter.varScaleRange;
	i2cMstWriteByte(MMA8452_XYZ_DATA_CFG, varBuff);

	//-Output data rate-//
	varBuff = i2cMstReadByte(MMA8452_CTRL_REG1);
	varBuff &= 0xCF;
	varBuff |= sMma8452Parameter.varOutDataRate;
	i2cMstWriteByte(MMA8452_CTRL_REG1, varBuff);

	//-Landscape/Portrait-//
	varBuff = i2cMstReadByte(MMA8452_PL_CFG);
	varBuff |= 0x40;
	i2cMstWriteByte(MMA8452_PL_CFG, varBuff);	// Set PL_EN
	i2cMstWriteByte(MMA8452_PL_COUNT, 0x50);	// Debounce counter at 100ms (at 800 hz)

	//-Tap-//
	varBuff = 0;
	if (!(sMma8452Parameter.varThsX & 0x80)) // If top bit ISN'T set
	{
		varBuff |= 0x03; // Enable taps on x
		i2cMstWriteByte(MMA8452_PULSE_THSX, sMma8452Parameter.varThsX);
	}
	if (!(sMma8452Parameter.varThsY & 0x80))
	{
		varBuff |= 0x0C; // Enable taps on y
		i2cMstWriteByte(MMA8452_PULSE_THSY, sMma8452Parameter.varThsY);
	}
	if (!(sMma8452Parameter.varThsZ & 0x80))
	{
		varBuff |= 0x30; // Enable taps on z
		i2cMstWriteByte(MMA8452_PULSE_THSZ, sMma8452Parameter.varThsZ);
	}
	varBuff |= 0x40;
	i2cMstWriteByte(MMA8452_PULSE_CFG, varBuff);
	i2cMstWriteByte(MMA8452_PULSE_TMLT, 0x30);
	i2cMstWriteByte(MMA8452_PULSE_LTCY, 0xA0);
	i2cMstWriteByte(MMA8452_PULSE_WIND, 0xFF);

	//-Active-//
	varBuff = i2cMstReadByte(MMA8452_CTRL_REG1);
	varBuff |= 0x01;
	i2cMstWriteByte(MMA8452_CTRL_REG1, varBuff); //Set the active bit to begin detection
	return MMA8452_STATE_SETUP_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	mma8452Available
 *	Purpose	:
 * 	Input	:	None
 * 	Output	:	Available or not?
 */
unsigned char mma8452DataAvailable (void)
{
	unsigned char varBuff;
	varBuff = i2cMstReadByte(MMA8452_STATUS);
	varBuff &= 0x08;
	varBuff = (varBuff >> 3);
	if(varBuff == 1)
	{
		return MMA8452_STATE_DATA_AVAILABLE;
	}
	return MMA8452_STATE_DATA_UNAVAILABLE;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	mma8452GetAccelValue
 *	Purpose	:	Read value of accel value
 * 	Input	:	None
 * 	Output	:	None
 */
void mma8452GetAccelValue(void)
{
	unsigned char arrRawData[6];
	i2cMstReadArray(MMA8452_OUT_X_MSB, arrRawData, 6);

	sMma8452AccelValue.varX_Uint = (arrRawData[0]<<8 | arrRawData[1]);
	sMma8452AccelValue.varY_Uint = (arrRawData[2]<<8 | arrRawData[3]);
	sMma8452AccelValue.varZ_Uint = (arrRawData[4]<<8 | arrRawData[5]);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	mma8452GetAccelAngle
 *	Purpose	:	Read value of accel angle
 * 	Input	:	None
 * 	Output	:	None
 */
void mma8452GetAccelAngle(void)		// Not true
{
	sMma8452AccelAngle.varX_Byte =
	(unsigned char)((float)(sMma8452AccelValue.varX_Uint) / (float)(0xFFFF) * (float)(sMma8452Parameter.varScaleRange));

	sMma8452AccelAngle.varY_Byte =
	(unsigned char)((float)(sMma8452AccelValue.varY_Uint) / (float)(0xFFFF) * (float)(sMma8452Parameter.varScaleRange));

	sMma8452AccelAngle.varZ_Byte =
	(unsigned char)((float)(sMma8452AccelValue.varZ_Uint) / (float)(0xFFFF) * (float)(sMma8452Parameter.varScaleRange));
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	mma8452FilterAccel
 *	Purpose	:	Filter value of accel
 * 	Input	:	None
 * 	Output	:	None
 */
void mma8452FilterAccel(void)
{
	unsigned int varCount;
	unsigned int varSum;

	//-Assignment of X-//
	for(varCount = MMA8452_FILTER_LENGTH - 1; varCount >= 1 ; varCount--)
	{
		sMma8452AccelFilter.arrX_Uint[varCount] = sMma8452AccelFilter.arrX_Uint[varCount - 1];
	}
	sMma8452AccelFilter.arrX_Uint[0] = sMma8452AccelValue.varX_Uint;

	//-Assignment of Y-//
	for(varCount = MMA8452_FILTER_LENGTH - 1; varCount >= 1 ; varCount--)
	{
		sMma8452AccelFilter.arrY_Uint[varCount] = sMma8452AccelFilter.arrY_Uint[varCount - 1];
	}
	sMma8452AccelFilter.arrY_Uint[0] = sMma8452AccelValue.varY_Uint;

	//-Assignment of Z-//
	for(varCount = MMA8452_FILTER_LENGTH - 1; varCount >= 1 ; varCount--)
	{
		sMma8452AccelFilter.arrZ_Uint[varCount] = sMma8452AccelFilter.arrZ_Uint[varCount - 1];
	}
		sMma8452AccelFilter.arrZ_Uint[0] = sMma8452AccelValue.varZ_Uint;

	//-Calculate mean value of X-//
	varSum = 0;
	for(varCount = 0; varCount < MMA8452_FILTER_LENGTH; varCount++)
	{
		varSum += sMma8452AccelFilter.arrX_Uint[varCount];
	}
	sMma8452AccelValue.varX_Uint = varSum / MMA8452_FILTER_LENGTH;

	//-Calculate mean value of Y-//
	varSum = 0;
	for(varCount = 0; varCount < MMA8452_FILTER_LENGTH; varCount++)
	{
		varSum += sMma8452AccelFilter.arrY_Uint[varCount];
	}
	sMma8452AccelValue.varY_Uint = varSum / MMA8452_FILTER_LENGTH;

	//-Calculate mean value of Z-//
	varSum = 0;
	for(varCount = 0; varCount < MMA8452_FILTER_LENGTH; varCount++)
	{
		varSum += sMma8452AccelFilter.arrZ_Uint[varCount];
	}
	sMma8452AccelValue.varZ_Uint = varSum / MMA8452_FILTER_LENGTH;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */


/**************************************************************************************************
 *	END OF MMA8452_1_0_1.c
 *************************************************************************************************/

/*
 *	File			:	MPU6050_1_0_1.c
 *	Date created	:	14/07/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	Construct MPU6050 library
 *	Target object	:	MSP430G2553
 */
 #define	USE_MPU6050_1_0_1
/**************************************************************************************************
 *	IMPORT
 *************************************************************************************************/
#include "MPU6050_1_0_1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Externals */
extern long GYRO_XFilter[4], GYRO_YFilter[4], GYRO_ZFilter[4];
extern long ACCEL_XFilter[10], ACCEL_YFilter[10], ACCEL_ZFilter[10];
extern long G_Filter[4];
extern unsigned int	TEMP_OUT;
extern int	GYRO_XOUT, GYRO_YOUT, GYRO_ZOUT,
			GYRO_XOUT_OFFSET, GYRO_YOUT_OFFSET, GYRO_ZOUT_OFFSET,
			GYRO_XRATE, GYRO_YRATE, GYRO_ZRATE,
			GYRO_XANGLE, GYRO_YANGLE, GYRO_ZANGLE,
			gyro_ratio;
extern char	dt;
extern int	ACCEL_XOUT, ACCEL_YOUT, ACCEL_ZOUT,
			ACCEL_XOUT_PAST, ACCEL_YOUT_PAST, ACCEL_ZOUT_PAST,
			ACCEL_XA, ACCEL_YA, ACCEL_ZA,
			ACCEL_XV, ACCEL_YV, ACCEL_ZV,
			ACCEL_XDECAC, ACCEL_YDECAC, ACCEL_ZDECAC,
			ACCEL_XANGLE, ACCEL_YANGLE, ACCEL_ZANGLE;
extern long	Decac_X0, Decac_X1,
			Decac_Y0, Decac_Y1,
			Decac_Z0, Decac_Z1;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function: mpu6050Setup
 *	Purpose	: Setup module MPU-6050
 * 	Input	: None
 * 	Output	: None
 */
void mpu6050Setup(void)
{
	//-General-//
	// 0x68: Reset GYRO, ACCEL, and TEMP
	while(i2cMstWriteByte(MPU6050_SIGNAL_PATH_RESET, 0x07));
	// 0x19: Sample rate = 1kHz/(1+0) = 1kHz
	while(i2cMstWriteByte(MPU6050_SMPLRT_DIV, 0));
	// 0x1A: Disable FSync, 44Hz(Accel) & 42Hz(Gyro) DLPF
	while(i2cMstWriteByte(MPU6050_CONFIG, 0x03));
	// 0x1B: Disable gyro self-test, scale of 500 degrees/s
	while(i2cMstWriteByte(MPU6050_GYRO_CONFIG, 0x18));
	// 0x1C: Disable accel self-test, scale of +-4g, no DHPF
	while(i2cMstWriteByte(MPU6050_ACCEL_CONFIG, 0x18));
	// 0x23: Disable sensor output to FIFO buffer
	while(i2cMstWriteByte( MPU6050_FIFO_EN, 0x00));
	
	//-AUX I2C setup-//
	// 0x24: Sets AUX I2C to single master control, plus other config
	while(i2cMstWriteByte( MPU6050_I2C_MST_CTRL, 0x00));
	// 0x25: Setup AUX I2C slaves
 	while(i2cMstWriteByte( MPU6050_I2C_SLV0_ADDR, 0x00));
 	// 0x26:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV0_REG, 0x00));
 	// 0x27:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV0_CTRL, 0x00));
 	// 0x28:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV1_ADDR, 0x00));
 	// 0x29:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV1_REG, 0x00));
 	// 0x2A:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV1_CTRL, 0x00));
 	// 0x2B:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV2_ADDR, 0x00));
 	// 0x2C:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV2_REG, 0x00));
 	// 0x2D:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV2_CTRL, 0x00));
 	// 0x2E:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV3_ADDR, 0x00));
 	// 0x2F:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV3_REG, 0x00));
 	// 0x30:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV3_CTRL, 0x00));
 	// 0x31:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV4_ADDR, 0x00));
 	// 0x32:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV4_REG, 0x00));
 	// 0x33:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV4_DO, 0x00));
 	// 0x34:
 	while(i2cMstWriteByte(MPU6050_I2C_SLV4_CTRL, 0x00));
 	// 0x35:
 	while(i2cMstWriteByte( MPU6050_I2C_SLV4_DI, 0x00));
 	// 0x37: Setup INT pin and AUX I2C pass through
	while(i2cMstWriteByte( MPU6050_INT_PIN_CFG, 0x00));
	// 0x38: Enable data ready interrupt
	while(i2cMstWriteByte(MPU6050_INT_ENABLE, 0x00));
	// 0x63-0x66: Slave out, dont care
	while(i2cMstWriteByte( MPU6050_I2C_SLV0_DO, 0x00));
	while(i2cMstWriteByte( MPU6050_I2C_SLV1_DO, 0x00));
	while(i2cMstWriteByte(MPU6050_I2C_SLV2_DO, 0x00));
	while(i2cMstWriteByte(MPU6050_I2C_SLV3_DO, 0x00));
	// 0x67: More slave config
	while(i2cMstWriteByte( MPU6050_I2C_MST_DELAY_CTRL, 0x00));
	// 0x68: Reset sensor signal paths
	while(i2cMstWriteByte(MPU6050_SIGNAL_PATH_RESET, 0x00));
	// 0x69: Motion detection control
	while(i2cMstWriteByte(MPU6050_MOT_DETECT_CTRL, 0x00));
	// 0x6A: Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
	while(i2cMstWriteByte(MPU6050_USER_CTRL, 0x00));
	// 0x6B: Sets clock source to gyro reference w/PLL
	while(i2cMstWriteByte(MPU6050_PWR_MGMT_1, 0x00));
	// 0x6C: Controls frequency of wakeups in accel low power mode plus the sensor standby modes
	while(i2cMstWriteByte(MPU6050_PWR_MGMT_2, 0x00));
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050TestI2c
 *	Purpose	: Test I2C communication
 * 	Input	: None
 * 	Output	: None
 */
void mpu6050TestI2c(void)
{
	unsigned char varMpu6050Address;
	txdStr("Test_I2C: ");
	varMpu6050Address = i2cMstReadByte(MPU6050_WHO_AM_I);
	if(varMpu6050Address == MPU6050_ADDRESS)
	{
		txdStr("Pass Test I2C!\n");
	}
	else
	{
		txdStr("ERROR!\n");
	}	
}	
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050CheckRegister
 *	Purpose	: Check whether registers are ready
 * 	Input	: None
 * 	Output	: The number of failed registers
 */
 unsigned char mpu6050CheckRegister(void)
{
	unsigned char varData;
	unsigned char varFail = 0;

	varData = i2cMstReadByte(MPU6050_SMPLRT_DIV);
	if(varData != 0x01)  varFail ++;
	varData = i2cMstReadByte(MPU6050_CONFIG);
	if(varData != 0x03)  varFail ++;
	varData = i2cMstReadByte(MPU6050_GYRO_CONFIG);
	if(varData != 0x18)  varFail ++;
	varData = i2cMstReadByte(MPU6050_ACCEL_CONFIG);
	if(varData != 0x18)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_FF_THR, &varData));
//	if(varData != 0x00) varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_FF_DUR, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_MOT_THR, &varData));
//	if(varData != 0x00) varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_MOT_DUR, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_ZRMOT_THR, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_ZRMOT_DUR, &varData));
//	if(varData != 0x00)  varFail = 1;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_FIFO_EN, &varData));
//	if(varData != 0x00)  varFail ++;
//	//AUX I2C Setup
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_MST_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
//	//Setup AUX I2C Slaves
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV0_ADDR, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV0_REG, &varData));
//	if(varData != 0x00) varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV0_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV1_ADDR, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV1_REG, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV1_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV2_ADDR, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV2_REG, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV2_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV3_ADDR, &varData));
//	if(varData != 0x00) varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV3_REG, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV3_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV4_ADDR, &varData));
//	if(varData != 0x00) varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV4_REG, &varData));
//	if(varData != 0x00) varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV4_DO, &varData));
//	if(varData != 0x00) varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV4_CTRL, &varData));
//	if(varData != 0x00) varFail ++;
// 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV4_DI, &varData));
//
// 	//MPU6050_I2C_MST_STATUS //Read-only
// 	//Setup INT pin and AUX I2C pass through
//	if(varData != 0x00) varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_INT_PIN_CFG, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_INT_ENABLE, &varData));
//	if(varData != 0x00)  varFail ++;
//
//	//Slave out, dont care
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV0_DO, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV1_DO, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV2_DO, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_SLV3_DO, &varData));
//	if(varData != 0x00)  varFail ++;
//
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_I2C_MST_DELAY_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_SIGNAL_PATH_RESET, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_MOT_DETECT_CTRL, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_USER_CTRL, &varData));
//	if(varData != 0x00) varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, &varData));
//	if(varData != 0x02)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_PWR_MGMT_2, &varData));
//	if(varData != 0x00)  varFail ++;
//	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_FIFO_R_W, &varData));
//	if(varData != 0x00)  varFail ++;

	if (varFail == 0)
	{
		txdStr("Every registers are well!\n");
	}
	else 
	{
		txdStr("ERROR!\n");
	}
	
	return(varFail);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050GetTempValue
 *	Purpose	: Get value of temperature
 * 	Input	: None
 * 	Output	: Value of temperature
 */
unsigned int mpu6050GetTempValue(void)
{
	unsigned char arrTemp[2];
	arrTemp[0] = i2cMstReadByte(MPU6050_TEMP_OUT_L);	// Low byte
	arrTemp[1] = i2cMstReadByte(MPU6050_TEMP_OUT_H);	// High byte
	TEMP_OUT = ((arrTemp[1]<<8) | arrTemp[0]);
	return TEMP_OUT;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050CalibGyro
 *	Purpose	: Calibrate Gyro offset
 * 	Input	: None
 * 	Output	: None
 */
void mpu6050CalibGyro(void)
{
	int varCount = 0;
	unsigned char arrBuff[10];
	unsigned char arrData[6];
	long	GYRO_XOUT_OFFSET_4096SUM = 0,
			GYRO_YOUT_OFFSET_4096SUM = 0,
			GYRO_ZOUT_OFFSET_4096SUM = 0;
	for(varCount = 0; varCount < 4096; varCount++)
	{
		while(i2cMstReadArray(MPU6050_GYRO_XOUT_H, arrData, 6));
		GYRO_XOUT_OFFSET_4096SUM += ((arrData[1]<<8) | arrData[0]);
		GYRO_YOUT_OFFSET_4096SUM += ((arrData[3]<<8) | arrData[2]);
		GYRO_ZOUT_OFFSET_4096SUM += ((arrData[5]<<8) | arrData[4]);
		GYRO_XOUT_OFFSET_4096SUM += GYRO_XOUT;
		GYRO_YOUT_OFFSET_4096SUM += GYRO_YOUT;
		GYRO_ZOUT_OFFSET_4096SUM += GYRO_ZOUT;
		txdStr("1: ");
		sprintf((char*)arrBuff, "%d", varCount);
		txdStr(arrBuff);
		txdChar(' ');
	}
	GYRO_XOUT_OFFSET = GYRO_XOUT_OFFSET_4096SUM>>12;
	GYRO_YOUT_OFFSET = GYRO_YOUT_OFFSET_4096SUM>>12;
	GYRO_ZOUT_OFFSET = GYRO_ZOUT_OFFSET_4096SUM>>12;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050GetGyroValue
 *	Purpose	: Get value of Gyro
 * 	Input	: None
 * 	Output	: None
 */
void mpu6050GetGyroValue(void)
{
	unsigned char arrData[6];
	i2cMstReadArray(MPU6050_GYRO_XOUT_H, arrData, 6);
	GYRO_XOUT = ((arrData[1]<<8) | arrData[0]) + GYRO_XOUT_OFFSET;
	GYRO_YOUT = ((arrData[3]<<8) | arrData[2]) + GYRO_YOUT_OFFSET;
	GYRO_ZOUT = ((arrData[5]<<8) | arrData[4]) + GYRO_ZOUT_OFFSET;
	mpu6050FilterGyro();
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050GetAccelValue
 *	Purpose	: Get value of Accel
 * 	Input	: None
 * 	Output	: None
 */
void mpu6050GetAccelValue(void)
{
	unsigned char arrData[6];
	i2cMstReadArray(MPU6050_ACCEL_XOUT_H, arrData, 6);
	ACCEL_XOUT = ((arrData[1]<<8) | arrData[0]);
//	ACCEL_YOUT = ((arrData[3]<<8) | arrData[2]);
	ACCEL_ZOUT = ((arrData[5]<<8) | arrData[4]);
	mpu6050FilterAccel();
}	
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050GetGyroRate
 *	Purpose	: Get Gyro rate (degree/s)
 * 	Input	: None
 * 	Output	: None
 */ 
void mpu6050GetGyroRate(void)
{
	unsigned char arrData[6];
	i2cMstReadArray(MPU6050_GYRO_XOUT_H, arrData, 6);
	GYRO_XOUT = ((arrData[1]<<8) | arrData[0]) + GYRO_XOUT_OFFSET;
	GYRO_YOUT = ((arrData[3]<<8) | arrData[2]) + GYRO_YOUT_OFFSET;
	GYRO_ZOUT = ((arrData[5]<<8) | arrData[4]) + GYRO_ZOUT_OFFSET;
	mpu6050FilterGyro();

	if(GYRO_XOUT>0)
	{
		GYRO_XRATE += (GYRO_XOUT/48);
	}
	else
	{
		GYRO_XRATE += (GYRO_XOUT>>5);
	}
	GYRO_YRATE += (GYRO_YOUT>>5);
	GYRO_ZRATE += (GYRO_ZOUT>>5);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050GetAccelDescartes
 *	Purpose	: Get value of Accel as Descartes
 * 	Input	: None
 * 	Output	: None
 */ 
 void mpu6050GetAccelDescartes(void)
{
	unsigned char rData[6];
	i2cMstReadArray(MPU6050_ACCEL_XOUT_H, rData, 6);
	ACCEL_XOUT = ((rData[1]<<8) | rData[0]);
	ACCEL_YOUT = ((rData[3]<<8) | rData[2]);
	ACCEL_ZOUT = ((rData[5]<<8) | rData[4]);
	mpu6050FilterAccel();

	ACCEL_XA = ACCEL_XOUT - ACCEL_XOUT_PAST;
	ACCEL_YA = ACCEL_XOUT - ACCEL_YOUT_PAST;
	ACCEL_ZA = ACCEL_XOUT - ACCEL_ZOUT_PAST;

	ACCEL_XV += ACCEL_XA;
	ACCEL_YV += ACCEL_YA;
	ACCEL_ZV += ACCEL_ZA;

	ACCEL_XDECAC += (ACCEL_XV>>8);
	ACCEL_YDECAC += (ACCEL_YV>>8);
	ACCEL_ZDECAC += (ACCEL_ZV>>8);

	ACCEL_XOUT_PAST = ACCEL_XOUT;	
	ACCEL_YOUT_PAST = ACCEL_YOUT;
	ACCEL_ZOUT_PAST = ACCEL_ZOUT;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050GetAccelAngle
 *	Purpose	: Get Accel angle as 3D euler angle
 * 	Input	: None
 * 	Output	: None
 */
void mpu6050GetAccelAngle(void)
{
	ACCEL_XANGLE = (int)( 57.296 * (float)atan((float)ACCEL_YOUT / (float)ACCEL_ZOUT));
//	ACCEL_YANGLE = 57.296*atan((float)- ACCEL_XOUT / sqrt(pow((float)ACCEL_ZOUT, 2) + pow((float)ACCEL_YOUT, 2)));
//	ACCEL_ZANGLE = (int)atan(sqrtf((float)(ACCEL_XOUT*ACCEL_XOUT + ACCEL_YOUT*ACCEL_YOUT)) / ACCEL_ZOUT);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050FilterG
 *	Purpose	:
 * 	Input	: None
 * 	Output	: None
 */ 
 void mpu6050FilterG(void)
{
	G_Filter[3] = G_Filter[2];
	G_Filter[2] = G_Filter[1];
	G_Filter[1] = G_Filter[0];
	G_Filter[0] = ACCEL_ZDECAC;
	ACCEL_ZDECAC = (G_Filter[3] + G_Filter[2] + G_Filter[1] + G_Filter[0]) / 4;
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050FilterGyro
 *	Purpose	:
 * 	Input	: None
 * 	Output	: None
 */ 
 void mpu6050FilterGyro(void)
{
	GYRO_XFilter[3] = GYRO_XFilter[2];
	GYRO_XFilter[2] = GYRO_XFilter[1];
	GYRO_XFilter[1] = GYRO_XFilter[0];
	GYRO_XFilter[0] = GYRO_XOUT;

	GYRO_XOUT = ((GYRO_XFilter[3] + GYRO_XFilter[2] + GYRO_XFilter[1] + GYRO_XFilter[0]) >> 2);

	GYRO_YFilter[3] = GYRO_YFilter[2];
	GYRO_YFilter[2] = GYRO_YFilter[1];
	GYRO_YFilter[1] = GYRO_YFilter[0];
	GYRO_YFilter[0] = GYRO_YOUT;

	GYRO_YOUT = ((GYRO_YFilter[3] + GYRO_YFilter[2] + GYRO_YFilter[1] + GYRO_YFilter[0]) >> 2);

	GYRO_ZFilter[3] = GYRO_ZFilter[2];
	GYRO_ZFilter[2] = GYRO_ZFilter[1];
	GYRO_ZFilter[1] = GYRO_ZFilter[0];
	GYRO_ZFilter[0] = GYRO_ZOUT;

	GYRO_ZOUT = ((GYRO_ZFilter[3] + GYRO_ZFilter[2] + GYRO_ZFilter[1] + GYRO_ZFilter[0]) >> 2);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function: mpu6050FilterAccel
 *	Purpose	:
 * 	Input	: None
 * 	Output	: None
 */ 
 void mpu6050FilterAccel(void)
{
//	ACCEL_XFilter[3] = ACCEL_XFilter[2];
//	ACCEL_XFilter[2] = ACCEL_XFilter[1];
//	ACCEL_XFilter[1] = ACCEL_XFilter[0];
//	ACCEL_XFilter[0] = ACCEL_XOUT;
//	ACCEL_XOUT = (ACCEL_XFilter[3] + ACCEL_XFilter[2] + ACCEL_XFilter[1] + ACCEL_XFilter[0]) / 4;
//
//	ACCEL_YFilter[3] = ACCEL_YFilter[2];
//	ACCEL_YFilter[2] = ACCEL_YFilter[1];
//	ACCEL_YFilter[1] = ACCEL_YFilter[0];
//	ACCEL_YFilter[0] = ACCEL_YOUT;
//	ACCEL_YOUT = (ACCEL_YFilter[3] + ACCEL_YFilter[2] + ACCEL_YFilter[1] + ACCEL_YFilter[0]) / 4;

	ACCEL_ZFilter[9] = ACCEL_ZFilter[8];
	ACCEL_ZFilter[8] = ACCEL_ZFilter[7];
	ACCEL_ZFilter[7] = ACCEL_ZFilter[6];
	ACCEL_ZFilter[6] = ACCEL_ZFilter[5];
	ACCEL_ZFilter[5] = ACCEL_ZFilter[4];
	ACCEL_ZFilter[4] = ACCEL_ZFilter[3];
	ACCEL_ZFilter[3] = ACCEL_ZFilter[2];
	ACCEL_ZFilter[2] = ACCEL_ZFilter[1];
	ACCEL_ZFilter[1] = ACCEL_ZFilter[0];
	ACCEL_ZFilter[0] = ACCEL_ZOUT;
	ACCEL_ZOUT = (ACCEL_ZFilter[9] + ACCEL_ZFilter[8] + ACCEL_ZFilter[7] + ACCEL_ZFilter[6] +
			ACCEL_ZFilter[5] + ACCEL_ZFilter[4] + ACCEL_ZFilter[3] + ACCEL_ZFilter[2] +
			ACCEL_ZFilter[1] + ACCEL_ZFilter[0]) / 10;
}
 //-------------------------------------------------------------------------------------------------
 /*
  * Function: printGyroValue
  *	Purpose	: Print Gyro value
  * Input	: None
  * Output	: None
  */
 void mpu6050PrintGyroValue(void)
 {
	 unsigned char arrBuff[10];
	 txdStr("GyroX: ");
	 sprintf((char*)arrBuff, "%d", GYRO_XOUT);
	 txdStr(arrBuff);
	 txdChar(' ');
	 txdStr("GyroY: ");
	 sprintf((char*)arrBuff, "%d", GYRO_YOUT);
	 txdStr(arrBuff);
	 txdChar(' ');
	 txdStr("GyroZ: ");
	 sprintf((char*)arrBuff, "%d", GYRO_ZOUT);
	 txdStr(arrBuff);
	 txdChar(10);
 }
 //-------------------------------------------------------------------------------------------------
 /*
  * Function: printAccelValue
  *	Purpose	: Print Accel value
  * Input	: None
  * Output	: None
  */
 void mpu6050PrintAccelValue(void)
 {
	 unsigned char arrBuff[10];
	 txdStr("AccelX: ");
	 sprintf((char*)arrBuff, "%d", ACCEL_XOUT);
	 txdStr(arrBuff);
	 txdChar(' ');
	 txdStr("AccelY: ");
	 sprintf((char*)arrBuff, "%d", ACCEL_YOUT);
	 txdStr(arrBuff);
	 txdChar(' ');
	 txdStr("AccelZ: ");
	 sprintf((char*)arrBuff, "%d", ACCEL_ZOUT);
	 txdStr(arrBuff);
	 txdChar(10);
 }
 //-------------------------------------------------------------------------------------------------
 /*
  * Function: printAccelAngle
  *	Purpose	: Print Accel angle
  * Input	: None
  * Output	: None
  */
 void mpu6050PrintAccelAngle(void)
 {
	 unsigned char arrBuff[5];
	 txdStr("Accel_Z_Angle: ");
	 sprintf((char*)arrBuff, "%d", ACCEL_ZANGLE);
	 txdStr(arrBuff);
	 txdChar(10);
 }

/**************************************************************************************************
 *	END OF MPU6050_1_0_1.c
 *************************************************************************************************/

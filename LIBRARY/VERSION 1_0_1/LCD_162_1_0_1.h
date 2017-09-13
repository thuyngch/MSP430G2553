/*
 *	File			:	LCD_162_1_0_1.h
 *	Date created	:	08/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	LCD 16x2 library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef LCD_162_1_0_1_H_
#define LCD_162_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/**/
#define	LCD_PORT_1			(&P1OUT)
#define	LCD_PORT_2			(&P2OUT)

/**/
#define lcd_delay 	500

/* Chon kieu hien thi tang/giam, shift hoac khong shift */
#define LCD_DEC_CUR_SHIFT_ON()	LCD_Command(0x05);
#define LCD_DEC_CUR_SHIFT_OFF()	LCD_Command(0x04);
#define LCD_INC_CUR_SHIFT_ON()	LCD_Command(0x07);
#define LCD_INC_CUR_SHIFT_OFF()	LCD_Command(0x06);	// khuyen khich su dung cach nay


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
void
lcdSetup(volatile uint8_t* LCD_PORT_, const uint16_t LCD_PIN_RS, const uint16_t LCD_PIN_EN,
																	const uint8_t LCD_DATA_OFFSET);

void LCD_Init_write(unsigned char b);		  //Ghi du lieu 8bit len lcd
void LCD_Command(unsigned char chr); 	  //ghi 2 nibbles vao lcd
char LCD_Read2Nib();	
void LCD_Init();				              //khoi dong lcd
void LCD_Clear();			                  //xoa lcd
void LCD_Home();	
void LCD_Display(unsigned char chr);          //hien thi ki tu 
void LCD_Goto(unsigned char row, unsigned char column);       /* Di chuyen con tro toi vi tri hang row, cot column */
/* Dich chuyen con tro sang trai(direct=0) hoac sang phai(direct=1) "step" vi tri */
void LCD_CursorShift(unsigned char direct, unsigned char step);
void LCD_PrintString(char *str);				/* In ra man hinh xau ki tu str[] */
/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, unsigned char length);
/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintUnDecimal(long n, unsigned char length);
void LCD_PrintFloat(float x, unsigned char length, unsigned char coma);


/**************************************************************************************************
 *	END OF LCD_162_1_0_1.h
 *************************************************************************************************/
#endif /* LCD_162_1_0_1_H_ */

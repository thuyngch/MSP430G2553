/*
 *	File			:	LCD_162_1_0_1.c
 *	Date created	:	08/08/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Tool			:	CCS6.1.2.00015 (C programming)
 *	Current version	:	1.0.1
 *	Description		:	LCD 16x2 library
 *	Target object	:	MSP430G2553
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "LCD_162_1_0_1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
static	volatile	uint8_t*		lcdPort;
static				uint16_t		lcdPinRS;
static				uint16_t		lcdPinEN;
static				uint8_t			lcdDataOffset;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 * 	Function:	
 *	Purpose	:	
 * 	Input	:	
 * 	Output	:	
 */
void
lcdSetup(volatile uint8_t* LCD_PORT_, const uint16_t LCD_PIN_RS, const uint16_t LCD_PIN_EN,
																const uint8_t LCD_DATA_OFFSET)
{
	//-Assign variable-//
	lcdPort 		 =  LCD_PORT_;
	lcdPinRS 		 =  LCD_PIN_RS;
	lcdPinEN 		 =  LCD_PIN_EN;
	lcdDataOffset 	 =  LCD_DATA_OFFSET;

	//-Setup GPIO-//
	if(LCD_PORT_ == LCD_PORT_1)
	{
		P1SEL			&= ~(0xF0>>lcdDataOffset);
		P1SEL2	 		&= ~(0xF0>>lcdDataOffset);
		P1DIR			|=  (0xF0>>lcdDataOffset);
		P1REN			&= ~(0xF0>>lcdDataOffset);
		P1OUT			&= ~(0xF0>>lcdDataOffset);

		P1DIR			|=  lcdPinEN;
		P1DIR			|=  lcdPinRS;
		P1OUT			&= ~lcdPinRS;
		P1OUT			&= ~lcdPinEN;
	}
	else if (LCD_PORT_ == LCD_PORT_2)
	{
		P2SEL			&= ~(0xF0>>lcdDataOffset);
		P2SEL2	 		&= ~(0xF0>>lcdDataOffset);
		P2DIR			|=  (0xF0>>lcdDataOffset);
		P2REN			&= ~(0xF0>>lcdDataOffset);
		P2OUT			&= ~(0xF0>>lcdDataOffset);

		P2DIR			|=  lcdPinEN;
		P2DIR			|=  lcdPinRS;
		P2OUT			&= ~lcdPinRS;
		P2OUT			&= ~lcdPinEN;
	}


	__delay_cycles(lcd_delay*40);				  								//delay 1.64mS
	LCD_Init_write(0x20);					//4 bit mode						//delay 40uS
	LCD_Command(0x28);
	_delay_cycles(lcd_delay);
	LCD_Command(0x0C);					  	// Bat hien thi,tat con tro			//delay 40uS
	///////////////////////////////////////////
	_delay_cycles(lcd_delay);
	LCD_Command(6);							//hien thi tang va khong shift		//delay 40uS
	///////////////////////////////////////////
	__delay_cycles(lcd_delay);
	LCD_Command(0x01);						//Xoa man hinh hien thi
	///////////////////////////////////////////
	__delay_cycles(lcd_delay*40);				   								//delay 1.64mS
	LCD_Command(0x02);						//Tro ve dau dong
	__delay_cycles(lcd_delay*40);												//delay 1.64mS
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//Ghi du lieu 8 bit len lcd ban dau
//Cac lenh Init co delay dai hon binh thuong de dam bao chac chan
void LCD_Init_write(unsigned char b)
{
	*lcdPort &= ~(0xF0 >> lcdDataOffset);
	*lcdPort &= ~lcdPinRS;
	__delay_cycles(lcd_delay*40);
	b &= 0xF0;
	*lcdPort |= (b >> lcdDataOffset);
	*lcdPort  |= lcdPinEN;
	__delay_cycles(lcd_delay);
	*lcdPort &= ~lcdPinEN;
	__delay_cycles(lcd_delay*40);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//Ham goi lenh vao LCD
void LCD_Command(unsigned char chr)
{
	unsigned char HNib,LNib,temp_data; 
	temp_data = (*lcdPort & ~(0xF0 >> lcdDataOffset));
	HNib = (chr & 0xF0);
	LNib = ((chr<<4) & 0xF0);
	
	*lcdPort = ((HNib >> lcdDataOffset) | temp_data);
	*lcdPort = ((HNib >> lcdDataOffset) | temp_data);
	*lcdPort |=  lcdPinEN;
	*lcdPort &= ~lcdPinEN ;
	__delay_cycles(lcd_delay);
	
	*lcdPort = ((LNib >> lcdDataOffset) | temp_data);
	*lcdPort = ((LNib >> lcdDataOffset) | temp_data);
	*lcdPort |=  lcdPinEN;
	*lcdPort &= ~lcdPinEN;
	__delay_cycles(lcd_delay);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//Doc du lieu tu LCD
char LCD_Read2Nib()
{
	char HNib,LNib;
	*lcdPort |= (0xF0 >> lcdDataOffset);
	
	*lcdPort |=  lcdPinEN;
	HNib    = ((P1IN & (0xF0 >> lcdDataOffset)) << lcdDataOffset);
	*lcdPort &= ~lcdPinEN;

	*lcdPort |= lcdPinEN;
	LNib = ((P1IN &(0xF0 >> lcdDataOffset)) << lcdDataOffset);
	*lcdPort &=~lcdPinEN;
	LNib >>= 4;
	return (HNib | LNib);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//Xoa LCD
void LCD_Clear()
{
	*lcdPort &= ~lcdPinRS;
	LCD_Command(0x01);
	__delay_cycles(lcd_delay*40);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//Dua con tro ve home
void LCD_Home()
{
	*lcdPort &= ~lcdPinRS;
	LCD_Command(0x02);
	__delay_cycles(lcd_delay*40);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//Hien thi ki tu
void LCD_Display(unsigned char chr)
{
	*lcdPort |= lcdPinRS;
	LCD_Command(chr);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
/* Di chuyen con tro toi vi tri hang row, cot column */
void LCD_Goto(unsigned char row, unsigned char column)
{
	*lcdPort &= ~lcdPinRS;
	if(row == 2)
		LCD_Command(0xC0 + column - 1);
	else
		LCD_Command(0x80 + column - 1);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
/* Dich chuyen con tro sang trai(direct=0) hoac sang phai(direct=1) "step" vi tri */
void LCD_CursorShift(unsigned char direct, unsigned char step)
{
	unsigned char i;
	*lcdPort &= ~lcdPinRS;
	if (direct == 0)
		for(i=0; i<step; i++)
			LCD_Command(0x10);
	else
		for(i=0; i<step; i++)
			LCD_Command(0x14);
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
/* In ra man hinh xau ki tu str[] */
void LCD_PrintString(char *str)
{
	while(*str)
	{
		LCD_Display(*str);
		str++;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, unsigned char length)
{
	unsigned char du,luu=length;
	// de trong 1 ki tu o dau cho hien thi dau
	if(n>=0)LCD_Display(' ');		//In so duong	
	else 
	{
		LCD_Display('-');			//In so am
		n*=-1;
	}	
	
	length--;
	LCD_CursorShift(1,length-1);	// dich con tro sang phai length-1 vi tri
	*lcdPort &= ~lcdPinRS;
	__delay_cycles(lcd_delay);
	LCD_DEC_CUR_SHIFT_OFF();		// chuyen sang che do in lui
	// Bat dau in lan luot cac chu so tu hang don vi
	while(length)
	{
		du = n % 10;
		n = n / 10;
		LCD_Display(0x30 + du);
		length--;
	}
	LCD_CursorShift(1,luu);		// dua con tro sang phai length+1 vi tri de in tiep
	*lcdPort &= ~lcdPinRS;
	__delay_cycles(lcd_delay);
	LCD_INC_CUR_SHIFT_OFF();		// chuyen lai ve che do in xuoi
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
void LCD_PrintUnDecimal(long n, unsigned char length)
{
	unsigned char du,luu=length;
	LCD_CursorShift(1,length-1);	// dich con tro sang phai length-1 vi tri
	*lcdPort &=~ lcdPinRS;
	__delay_cycles(lcd_delay);
	LCD_DEC_CUR_SHIFT_OFF();		// chuyen sang che do in lui
	// Bat dau in lan luot cac chu so tu hang don vi
	while(length)
	{
		du = n % 10;
		n = n / 10;
		LCD_Display(0x30 + du);
		length--;
	}
	LCD_CursorShift(1,luu+1);		// dua con tro sang phai length+1 vi tri de in tiep
	*lcdPort &= ~lcdPinRS;
	__delay_cycles(lcd_delay);
	LCD_INC_CUR_SHIFT_OFF();		// chuyen lai ve che do in xuoi
	
	
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintFloat(float x, unsigned char length, unsigned char coma)
{
	// de trong 1 ki tu o dau cho hien thi dau
	if(x>=0)LCD_Display(' ');
	else 
	{
		LCD_Display('-');			//In so am
		x*=-1;
	}
	unsigned long n;
	unsigned char store,temp;
	store = length;						// Luu lai do dai so thuc.
	length--;								// Giam di 1 cho dau "."						
	for(temp=0;temp<coma;temp++)
		x = x*10;
	
	n = x;									// Chuyan thanh so nguyen.
	if((x-n)>=0.5)n++;

	LCD_CursorShift(1,length);				// Dich chuyen con tro sang phai
	*lcdPort &= ~lcdPinRS;
	__delay_cycles(lcd_delay);
	LCD_DEC_CUR_SHIFT_OFF();				// Chuyen sang che do in nguoc.

	while(coma)								// In ra phan truoc dau phay
	{
		temp = n % 10;
		n = n / 10;
		LCD_Display(0x30 + temp);
		coma--;
		length--;
	}

	LCD_Display('.');							// In ra dau "."
	
		while(length)							// In ra phan thap phan
		{
			temp = n % 10;
			n = n / 10;
			//if(temp!=n)
			LCD_Display(0x30 + temp);			
			length--;
		}
		*lcdPort &= ~lcdPinRS;
	__delay_cycles(lcd_delay);
	LCD_INC_CUR_SHIFT_OFF();				// Chuyen lai che do in thuan.
	LCD_CursorShift(1,store+1);					// Nhay den vi tri tiep theo.
}
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:	
 *	Purpose	:	
 * 	Input	:	
 * 	Output	:	
 */
//-------------------------------------------------------------------------------------------------
/*
 * 	Function:
 *	Purpose	:
 * 	Input	:
 * 	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF LCD_162_1_0_1.c
 *************************************************************************************************/

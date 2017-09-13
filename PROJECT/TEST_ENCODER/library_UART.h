//#include <msp430.h>
//#include "library_DC.h"
//#include "library_DC.c"
/*
 * library_UART.h
 *
 *  Created on: Jul 22, 2016
 *      Author: K.V.D.T
 */




////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY UART
//
// nguon :	http://thuanbk55.blogspot.com/
// .................................................................
// MSP430x2xx LIBRARY
//******************************************************************/

#ifndef LIBRARY_UART_H_
#define LIBRARY_UART_H_

unsigned long SMCLK_F=1000000;                 // frequency of Sub-System Master Clock in Hz
unsigned long BAUDRATE=9600;                   // may be ... 1200, 2400, 4800, 9600, 19200, ...


//*****************************************************************************
// Bien toan cuc
//*****************************************************************************

/*
 * Cac ky tu dac biet
 * 	0 Ky tu rong
 * 	1 Bat dau header
 * 	2 Bat dau van ban
 * 	3 Ket thuc van ban
 * 	4 Ket thuc truyen
 * 	5 Truy van
 * 	7 Tab ngang
 * 	8 Xoa nguoc
 * 	9 Tab ngang
 * 	10 Xuong dong
 * 	11 Tab doc
 */

//*****************************************************************************
// Transfer  UART
//*****************************************************************************
void UART_Init();						       	//Khoi tao UART
void UART_Write_Char(unsigned char data);	   	//Gui ki tu
void UART_Write_String(char* string);		  	//Gui chuoi ki tu
void UART_Write_Int(unsigned long n);		   	//Goi so kieu int
void UART_Write_Reg(char *name, int n);			//In ra gia tri bit cua thanh ghi
void UART_Write_Float(float x,unsigned char coma);		//coma<=4
//In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma
//*****************************************************************************
// Receive  UART
//*****************************************************************************
char UART_Read_Char();							//Nhan ki tu
void UART_Read_String(char *s);					//Nhan chuoi ky tu
char UART_Data_Ready();							//Kien tra module san sang

/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/

//Init UART
void UART_Init()
{
	unsigned int tempfactor;
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1SEL |= BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2;
	UCA0CTL0 =0 ;		//Tat Parity ,LSB first,8-bit data,one stop bits
	UCA0CTL1 |= UCSSEL_2; // SMCLK

 	tempfactor = SMCLK_F/BAUDRATE;
    UCA0BR0 = (unsigned char) tempfactor&0x00FF;
    tempfactor >>= 8;
    UCA0BR1 = (unsigned char) (tempfactor&0x00FF);
    UCA0MCTL |=UCBRS_5;	// Modulation UCBRSx = 5
	UCA0CTL1 &=~ UCSWRST; // **Initialize USCI state machine**
	IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
	__bis_SR_register(GIE); // Interrupts enabled
}

//*****************************************************************************
// Transfer  UART
//*****************************************************************************
//In KyTu
void UART_Write_Char(unsigned char data)
{
	while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
	UCA0TXBUF= data; // Moi cho phep gui ky tu tiep theo
}
/////////////////////////////////////////
//In Xau
void UART_Write_String(char* string)
{
	while(*string) // Het chuoi ky tu thi thoat
		{
		while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
		UCA0TXBUF= *string; // Moi cho phep gui ky tu tiep theo
		string ++; // Lay ky tu tiep theo
		}
	UART_Write_Char(0);
}


void UART_Write_Int(unsigned long n)
{
     unsigned char buffer[16];
     unsigned char i,j;

     if(n == 0) {
    	 UART_Write_Char('0');
          return;
     }

     for (i = 15; i > 0 && n > 0; i--)
	 {
          buffer[i] = (n%10)+'0';
          n /= 10;
     }

     for(j = i+1; j <= 15; j++)
	 {
    	 UART_Write_Char(buffer[j]);
     }
}
//Gui ma bit
void UART_Write_Reg(char *name, int n)
{
	int size = 8;
    int i;

    UART_Write_String((char *)"- ");
    UART_Write_String(name);
    UART_Write_String((char *)": ");

    int mask = 1 << (size - 1);

    for(i = 0; i < size; i++) {
         if((n & (mask >> i)) != 0) {
        	 UART_Write_Char('1');
         } else {
        	 UART_Write_Char('0');
         }
    }
    UART_Write_String(" (");
	UART_Write_Int(n);
	UART_Write_String(")\n\r");
}


//In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma
void UART_Write_Float(float x, unsigned char coma)
{
	unsigned long temp;
	if(coma>4)coma=4;
	// de trong 1 ki tu o dau cho hien thi dau
	if(x<0)
	{
		UART_Write_Char('-');			//In so am
		x*=-1;
	}
	temp = (unsigned long)x;									// Chuyan thanh so nguyen.

	UART_Write_Int(temp);

	x=((float)x-temp);//*mysqr(10,coma);
	if(coma!=0)UART_Write_Char('.');	// In ra dau "."
	while(coma>0)
	{
		x*=10;
		coma--;
	}
	temp=(unsigned long)(x+0.5);	//Lam tron
	UART_Write_Int(temp);
}

//*****************************************************************************
// Receive  UART
//*****************************************************************************
char UART_Read_Char()
{
	while (!(IFG2&UCA0RXIFG)); // Doi gui xong ky tu truoc
	return UCA0RXBUF; // Moi cho phep nhan ky tu tiep theo
}

//*****************************************************************************
// Wait to receive a string through UART
// Note that the string is ended with '/0' (or 0x00)
//*****************************************************************************
void UART_Read_String(char *s)
{
	*s = UART_Read_Char();
	while(*s!='\0')
	{
		s++;
		*s = UART_Read_Char();
	}
}

//*****************************************************************************
// Check if USCI_A0 RX Buffer contain a complete character
//*****************************************************************************
char UART_Data_Ready()
{
	if(UCA0RXIFG) return 1;
	else return 0;
}

//////////////////////////////////////////
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG));                // USCI_A0 TX buffer ready?
    _delay_cycles(1000);
	UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
	P1OUT|=BIT0;
    _delay_cycles(1000);
    P1OUT^=BIT0;
}

#endif /* LIBRARY_UART_H_ */

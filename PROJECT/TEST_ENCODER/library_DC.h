#include <msp430.h>
//#include "library_DC.h"
#include "library_UART.h"
/*
 * library_DC.c
 *
 *  Created on: Jul 22, 2016
 *      Author: K.V.D.T
 */

volatile unsigned int count, recount, redirection;
int respeed;

#define		Encoder			BIT5
#define		Dir_encoder		BIT4
#define		Time_Ecoder		50000	// 50ms
#define		PWM_add			BIT6
#define		Dir_motor		BIT7
#define		Large_pulse		50000

/******************************************************************************\
*					     Function (noi dung ham)	                           *
 \******************************************************************************/
void config_motor() {

	BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài đặt tần số hoạt động
	DCOCTL = CALDCO_1MHZ;        //Ở đây là 1 Mhz

	//Config_Interrupt
	P2SEL = 0;
	P2SEL2 = 0;
	P2DIR &= ~(Encoder + Dir_encoder);	 // BIT5 chanel A, BIT4 chanel B
	P2REN |= Encoder + Dir_encoder;		//cho phep tro keo
	P2OUT |= Encoder + Dir_encoder;
	P2IE |= Encoder;	//cho phep ngat encoder
	P2IES |= Encoder;	//ngat suon xuong
	P2IFG &= ~Encoder;
	_BIS_SR(GIE);

	//config_Timer
	TA0CTL |= TASSEL_2 + MC_1 + TAIE;		//mode2 dem 0 -> Ta0CCR0
	TA0CCR0 = Time_Ecoder;		//chon thoi gian lay mau

	//config_PWM
	P1SEL=0;
	P1SEL2=0;
	P1SEL |= PWM_add;	 // BIT6 address PWM, BIT7 direction
	P1DIR |= PWM_add + Dir_motor;
	P1OUT &= ~ Dir_motor;
	TA0CTL |= TASSEL_2 + MC_1;		//mode1
	TA0CCTL1 = OUTMOD_7;
	TA0CCR0 = Large_pulse;		//do rong xung

}

void control(int speed, char direction) 
{
	switch (direction) 
	{
		case 1: 
		{
			unsigned int Large_pulse_1 = 0;
			P1OUT |= BIT7; // right direction
			Large_pulse_1 = (Large_pulse - 10 * speed);
			TA0CCR1 = Large_pulse_1; // PWM
			break;
		}
		case 0: 
		{
			P1OUT &= ~BIT7; // opposite direction
			TA0CCR1 = 10 * speed; // PWM
			break;
		}
	}
//	TA0CCR1 = 10 * speed; // PWM
}

unsigned int pulse_counter()
{
//	delay_ms(Time_Ecoder);
	if (count==0)
	{
		respeed = 1000 * 10 * recount / 167;
	}
	return respeed;
}

//void delay_ms(unsigned int ms)
//{
//	unsigned int i;
//	for (i = 0; i < ms; i++) {
//		_delay_cycles(1000);
//	}
//}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
	switch (TA0IV) {
//	case 2: {
//	break; // CCR1
//		}
//	case 4: {
//		break; // CCR2
//		}
	case 10:
	{
//		recount = count;
//		count = 0;
//		// over flow or CCR0
//		UART_Write_Char(10);
//		UART_Write_String("van toc tra ve la");
//		UART_Write_Int(recount);
//		delay_ms(1000);
		break;
	}
	}
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void) {
	if (P1IFG & Encoder == Encoder)
	{
		count++;
//		UART_Write_Char(10);
//		UART_Write_String("van toc tra ve la");
//		UART_Write_Int(recount);
	}
	P2IFG &= ~Encoder;
}


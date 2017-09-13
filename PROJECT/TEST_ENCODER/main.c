#include <msp430.h> 
#include "library_DC.h"
#include "library_UART.h"
/**************
 *  22-7-2016
 * ***********
 *   K.V.D.T
 *   *******
 *   test_control_motor_secvor_DC
 */
volatile int re_speed;
extern int respeed;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	config_motor();	//setup motor
    UART_Init();	//setup UART

	while (1) {

		control(5000, 1);
//		delay_ms(2000);
		control(0, 1);
//		delay_ms(2000);
		control(5000, 0);
//		delay_ms(2000);
		control(0, 0);
//		delay_ms(2000);
	}
}

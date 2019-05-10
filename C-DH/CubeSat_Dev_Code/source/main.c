/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "TransmitReceive.c"
#include "SDCARD_Interface.c"

/*!
 * @brief Application entry point.
 */
int main(void){


	/* Init board hardware. */
	Board_Init();
	/* Add your code here */
	while(1){
		printf("\n\rC&DH Monitor>");
		int i = 0;
		char a;

		a = getchar();
		printf("%c\n\r",a);
		switch ( a ){

		case 'l':
			Transmit_RTR();
			break;

		case 't':
			Transmit();
			break;

		case 'r':
			Receive();
			break;

		case 's':
			SDCARD_Interface();
			break;
		default:
			break;
		}
	}

	for(;;) { /* Infinite loop to avoid leaving the main function */
		__asm("NOP"); /* something to use as a breakpoint stop while looping */
	}
}

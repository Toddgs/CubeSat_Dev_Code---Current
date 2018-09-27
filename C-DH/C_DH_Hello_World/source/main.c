/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_uart.h"

/*!
 * @brief Application entry point.
 */

int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  uart_config_t user_config;
  UART_GetDefaultConfig(&user_config);
  user_config.baudRate_Bps = 115200U;//115200
  user_config.enableTx = true;
  user_config.enableRx = true;
  UART_Init(UART0,&user_config,20971520U);//120000000U

  //PORT_SetPinMux(PORTB, 22u, kPORT_MuxAsGpio); //Pin 68: Bit 22 of PORTB functions as PTB22
  //PORT_SetPinMux(PORTB, 23u, kPORT_MuxAsGpio); //Pin 69: Bit 23 of PORTB functions as PTB23
  gpio_pin_config_t pin_config = { kGPIO_DigitalOutput, 0, };
  GPIO_PinInit(GPIOB, 22U, &pin_config);       //Blinky light on D1
  GPIO_PinInit(GPIOB, 23U, &pin_config);	   //Blinky light on D2

  GPIO_SetPinsOutput(GPIOB, 1U << 22U);
  GPIO_ClearPinsOutput(GPIOB, 1U << 23U);
  printf("\rPress h for commands\r\n");

  for(;;) { /* Infinite loop to avoid leaving the main function */
    		// Command Parser
    		char z;
    		z = getchar();
    		switch (z) {

    		case 'a': ;
    			printf("\rCommand 'a' detected\n\r");
    		    GPIO_PortToggle(GPIOB, 1U << 22U);
    		    GPIO_PortToggle(GPIOB, 1U << 23U);
    			break;
    		case 'b': ;
    			printf("\rHello world\n\r");
    			break;

    		case 'h':
    			printf("\rSupported commands:\n\r");
    			printf("\ra - Toggles D1 and D2\n\r");
    			printf("\rb - Hello world\n\r");
    			break;

    		default:
    			printf("\rUnrecognized command\n\r");
    			break;

    		}
  	  	  }
}

void delay(int j) {
	volatile uint32_t i = 0;
	for (i = 0; i < j; ++i) {
		__asm("NOP");
	}
}




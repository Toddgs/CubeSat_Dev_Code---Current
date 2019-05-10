/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/


// Main ADCS Board Software - Version 0.1
// Board TODO:
// * LEDs are not blinking but MOSFETS are getting power.
// Board Notes:
// Add the CPU_MK22.. to Project Properties > Tools > Preprocessor
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"

// Function Declarations
void delay(void);

// Main
int main(void) {
	// Board Init
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	printf("\rBegin program.\n\r");

	// GPIO Init
	//gpio_pin_config_t pin_config = { kGPIO_DigitalOutput, 0, };
	//GPIO_PinInit(GPIOA, 6U, &pin_config); // pin 58
	//GPIO_PinInit(GPIOA, 7U, &pin_config); // pin 59

	//GPIO_SetPinsOutput(GPIOA, 1U << 6U);
	for (;;) {
		//GPIO_TogglePinsOutput(GPIOA, 1U << 7U);
		//delay();
		// Command Parser
		printf("EPS Ready>");
		char z;
		z = getchar();
		//z = 'a';
		printf("%c\r\n",z);
		switch (z) {

		case 'a': ;
			printf("\rCommand 'a' detected\n\r");
			ReadPowerStatus();
			ReadSwitchStatus();
			break;
		case 'b':
			printf("\rCommand 'b' detected\n\r");
			TurnOnAllSwitches();
			break;
		case 'c':
			printf("\rCommand 'c' detected\n\r");
			TurnOffAllSwitches();
			break;
		case 'd':
			printf("\rCommand 'd' detected\n\r");
			ReadChargerStatus();
			break;
		case 'e':
			printf("\rCommand 'e' detected\n\r");
			ReadCharger1UART();
			break;
		case 'h':
			printf("\r\nHelp Function:\r\n");
			printf("a - read status: 5V, 3.3V, Switches\r\n");
			printf("b - Turn on all switches\r\n");
			printf("c - Turn off all switches\r\n");
			printf("d - Read charger status\r\n");
			printf("e - Read Charger 1 UART\r\n");
			break;
		default:
			printf("\rUnrecognized command\n\r");
			break;
		}

		__asm("NOP");
		/* something to use as a breakpoint stop while looping */
	}
}

void delay(void) {
	volatile uint32_t i = 0;
	for (i = 0; i < 100000; ++i) {
		__asm("NOP");
		/* delay */
	}
}

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
#include "fsl_i2c.h"
#include "SPI.c"
#include "I2C.h"
//extern int DOF_Test(void);

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
	gpio_pin_config_t pin_config = { kGPIO_DigitalOutput, 0, };
	GPIO_PinInit(GPIOA, 6U, &pin_config); // pin 58
	GPIO_PinInit(GPIOA, 7U, &pin_config); // pin 59

	GPIO_SetPinsOutput(GPIOA, 1U << 6U);
	for (;;) {
		GPIO_TogglePinsOutput(GPIOA, 1U << 7U);
		delay();
		// Command Parser
		char z;
		z = getchar();
		//z = 'f';
		// Echo is no-worky; there is no "why"; it just is...
		//printf("!!\r\n");
		//printf("%c",z);
		//printf("!!\r\n");
		switch (z) {

		case 'a': ;
			printf("\rCommand 'a' detected\n\r");
			//Should we put in a blinky light??
			break;
		case 's': // "Who am I" test
			printf("\rCommand 's' detected\n\r");
			printf("\rRunning SPI test\n\r");
			DOF_Test();
			break;
		case 'f': // Detect flash
			printf("\rCommand 'f' detected\n\r");
			printf("\rTesting Flash\n\r");
			Flash_Test();
			break;
		case 'g': // Gyro test
			printf("\rCommand 'g' detected\n\r");
			printf("\rTesting Gyro\n\r");
			SPI_Test();
			break;
		case 'i': // Magnetometer (I2C)
			printf("\rCommand 'i' detected\n\r");
			printf("\rTesting Magnetometer\n\r");
			I2C_Test();
			I2C_X();
			I2C_Y();
			I2C_Z();
			break;
		case 't': // Temperature test
			printf("\rCommand 't' detected\n\r");
			printf("\rTesting Gyro Temp Sensor\n\r");
			Temp_Test();
			break;
		case 'u': // Temperature test
				printf("\rCommand 'u' detected\n\r");
				printf("\rTesting Analog Temp Sensor\n\r");
				Temp_Test_ADC();
				break;
		case 'h':
			printf("\rSupported commands:\n\r");
			printf("\ra - Does Nothing\n\r");
			printf("\rf - Detect flash\n\r");
			printf("\rg - Gyro Test\n\r");
			printf("\ri - Magnetometer Test\n\r");
			printf("\rs - Test 9DOF SPI Interface\n\r");
			printf("\rt - 9DOF SPI Temperature Test\n\r");
			printf("\ru - Analog Temp Sensor Test\n\r");
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

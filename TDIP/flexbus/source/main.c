/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_flexbus.h"

#define FLEX_START_ADDRESS 0x60000000U
// State Lights
#define RedLEDPin 13U
#define GreenLEDPin 12U
// State GPIO Defines
#define S4 15U // KPin 87 => CPin 4 => addr_in[3]
#define S3 16U // KPin 90 => CPin 3 => addr_in[2]
#define S2 17U // KPin 91 => CPin 2 => addr_in[1]
#define S1 18U // KPin 92 => CPin 1 => addr_in[0]

void delay(int j);
void setState(int statenum);

int main(void) {
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	// Delay control
	int i = 5000000;

	// Starting address
	uint32_t *address = (uint32_t *) FLEX_START_ADDRESS;
	// GPIO Logic struct
	gpio_pin_config_t pin_config = { kGPIO_DigitalOutput, 1, };

	// Pin Init
	GPIO_PinInit(GPIOC, RedLEDPin, &pin_config);
	GPIO_PinInit(GPIOC, GreenLEDPin, &pin_config);
	GPIO_PinInit(GPIOC, S1, &pin_config);
	GPIO_PinInit(GPIOC, S2, &pin_config);
	GPIO_PinInit(GPIOC, S3, &pin_config);
	GPIO_PinInit(GPIOC, S4, &pin_config);

	GPIO_ClearPinsOutput(GPIOC, 1u << GreenLEDPin);
	setState(0);

	while(1){
		GPIO_ClearPinsOutput(GPIOC, 1u << GreenLEDPin);
		delay(i);
		GPIO_SetPinsOutput(GPIOC, 1u << GreenLEDPin);
	}


	/* Initialize Flexbus */
	flexbus_config_t flexbusUserConfig;
	FLEXBUS_GetDefaultConfig(&flexbusUserConfig); //Gets the default configuration.
	//Configure some parameters
	flexbusUserConfig.waitStates = 0U;                  //Wait 2 states
	flexbusUserConfig.portSize = kFLEXBUS_4Bytes;
	flexbusUserConfig.byteLaneShift = kFLEXBUS_Shifted;
	flexbusUserConfig.chipBaseAddress = FLEX_START_ADDRESS; //address for using FlexBus
	flexbusUserConfig.chipBaseAddressMask = 7U;      //512 kilobytes memory size
	FLEXBUS_Init(FB, &flexbusUserConfig); //Initializes and configures the FlexBus module

	// State Machine Initialization
	setState(0);
	setState(1);
	setState(2);
	setState(3);
	setState(4);
	GPIO_SetPinsOutput(GPIOC, 1u << GreenLEDPin);
	delay(i);

	/*
	// 12 bit
	int num1 = 0b111111111111;
	int num2 = 0b001111111111;
	int num3 = 0b000000000000;
	int num4 = 0b111111000000;

	int a = 1;
	switch (a) {
	case (0):
		// Top rail
		GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		for (int i = 0; i < (16384 / 2); i++) {
			*address = num1;
		}
		GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S4);
		while (1) {
		}
		break;

	case (1):
		// Bottom rail
		GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		for (int i = 0; i < (16384 / 2); i++) {
			*address = num3;
		}
		GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S4);
		while (1) {
		}
		break;

	case (2):
		// Oscillate
		while (1) {
			GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
			GPIO_SetPinsOutput(GPIOC, 1u << S3);
			GPIO_ClearPinsOutput(GPIOC, 1u << S4);
			for (int i = 0; i < (16384 / 2); i++) {
				*address = num1;
			}
			GPIO_ClearPinsOutput(GPIOC, 1u << RedLEDPin);
			GPIO_SetPinsOutput(GPIOC, 1u << S4);
			int num4 = 0b11110000;
			delay(i);

			GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
			GPIO_ClearPinsOutput(GPIOC, 1u << S4);
			for (int i = 0; i < (16384 / 2); i++) {
				*address = num3;
			}
			GPIO_ClearPinsOutput(GPIOC, 1u << RedLEDPin);
			GPIO_SetPinsOutput(GPIOC, 1u << S4);
			delay(i);
		}

	case (3):
		// Half Top/Half Bottom Rail
		GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		for (int i = 0; i < (16384 / 2); i++) {
			*address = num4;
		}
		GPIO_SetPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S4);
		while (1) {
		}
		break;



		// Set CPLD to State 4 - Read Out
		GPIO_ClearPinsOutput(GPIOC, 1u << RedLEDPin);
		GPIO_SetPinsOutput(GPIOC, 1u << S4);
		break;

	default:
		break;
	}

	*/

	FLEXBUS_Deinit(FB);

	for (;;) {
		__asm("NOP");
	}
}

void delay(int j) {
	volatile uint32_t i = 0;
	for (i = 0; i < j; ++i) {
		__asm("NOP");
	}
}

// Sets the state control pins appropriately
// States 4 and 5 must be accompanied by a flexbus write
void setState(int statenum) {
	GPIO_SetPinsOutput(GPIOC, 1u << S4);
	switch(statenum) {
	case 0 :
		GPIO_ClearPinsOutput(GPIOC, 1u << S1);
		GPIO_ClearPinsOutput(GPIOC, 1u << S2);
		GPIO_ClearPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 0001 :
		GPIO_SetPinsOutput(GPIOC, 1u << S1);
		GPIO_ClearPinsOutput(GPIOC, 1u << S2);
		GPIO_ClearPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 2 :
		GPIO_SetPinsOutput(GPIOC, 1u << S1);
		GPIO_SetPinsOutput(GPIOC, 1u << S2);
		GPIO_ClearPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 3 :
		GPIO_ClearPinsOutput(GPIOC, 1u << S1);
		GPIO_SetPinsOutput(GPIOC, 1u << S2);
		GPIO_ClearPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 4 :
		GPIO_ClearPinsOutput(GPIOC, 1u << S1);
		GPIO_SetPinsOutput(GPIOC, 1u << S2);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 5 :
		GPIO_SetPinsOutput(GPIOC, 1u << S1);
		GPIO_SetPinsOutput(GPIOC, 1u << S2);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 6 :
		GPIO_SetPinsOutput(GPIOC, 1u << S1);
		GPIO_ClearPinsOutput(GPIOC, 1u << S2);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	case 7 :
		GPIO_ClearPinsOutput(GPIOC, 1u << S1);
		GPIO_ClearPinsOutput(GPIOC, 1u << S2);
		GPIO_SetPinsOutput(GPIOC, 1u << S3);
		GPIO_ClearPinsOutput(GPIOC, 1u << S4);
		break;
	}
}


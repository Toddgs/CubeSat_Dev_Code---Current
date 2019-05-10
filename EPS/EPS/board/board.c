/* This is a template for board specific configuration created by New Kinetis SDK 2.x Project Wizard. Enjoy! */

#include <stdint.h>
#include "board.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"

/*!
 /* @brief initialize debug console to enable printf for this demo/example
 */
void BOARD_InitDebugConsole(void) {
	/* The user initialization should be placed here */
	uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

		DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

void BOARD_InitPins(void)
{

	gpio_pin_config_t OutConfig;

	OutConfig.pinDirection = kGPIO_DigitalOutput;
	OutConfig.outputLogic = 0;


CLOCK_EnableClock(kCLOCK_PortE); //Enables the clock on PORTE
CLOCK_EnableClock(kCLOCK_PortD); //Enables the clock on PORTD
CLOCK_EnableClock(kCLOCK_PortC); //Enables the clock on PORTC
CLOCK_EnableClock(kCLOCK_PortB); //Enables the clock on PORTB
CLOCK_EnableClock(kCLOCK_PortA); //Enables the clock on PORTA

PORT_SetPinMux(PORTE, 0u, kPORT_MuxAsGpio); //Pin 1
PORT_SetPinMux(PORTE, 1u, kPORT_MuxAlt3); //Pin 2 *activating UART1 RX to read charger status
//PORT_SetPinMux(VDD, *u, kPORT_MuxALt*); //Pin 3 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VSS, *u, kPORT_MuxALt*); //Pin 4 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(USB0_DP, *u, kPORT_MuxALt*); //Pin 5 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(USB0_DM, *u, kPORT_MuxALt*); //Pin 6 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VOUT33, *u, kPORT_MuxALt*); //Pin 7 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VREGIN, *u, kPORT_MuxALt*); //Pin 8 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(ADC0_DP0, *u, kPORT_MuxALt*); //Pin 9 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(ADC0_DM0, *u, kPORT_MuxALt*); //Pin 10 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(ADC1_DP0, *u, kPORT_MuxALt*); //Pin 11 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(ADC1_DM0, *u, kPORT_MuxALt*); //Pin 12 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VDDA, *u, kPORT_MuxALt*); //Pin 13 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VREFH, *u, kPORT_MuxALt*); //Pin 14 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VREFL, *u, kPORT_MuxALt*); //Pin 15 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VSSA, *u, kPORT_MuxALt*); //Pin 16 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VREF_OUT, *u, kPORT_MuxALt*); //Pin 17 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(DAC0_OUT, *u, kPORT_MuxALt*); //Pin 18 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(XTAL32, *u, kPORT_MuxALt*); //Pin 19 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(EXTAL32, *u, kPORT_MuxALt*); //Pin 20 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VBAT, *u, kPORT_MuxALt*); //Pin 21 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(PORTA, 0u, kPORT_MuxALt); //Pin 22 - Default pin option was desirable
PORT_SetPinMux(PORTA, 1u, kPORT_MuxAlt2); //Pin 23 - UART0 RX -- MAY BREAK JTAG DEBUGGING!!
PORT_SetPinMux(PORTA, 2u, kPORT_MuxAlt2); //Pin 24 - UART0 TX
//PORT_SetPinMux(PORTA, 3u, kPORT_MuxALt*); //Pin 25 - Default was desirable
//PORT_SetPinMux(PORTA, 4u, kPORT_MuxALt*); //Pin 26 - Default was desirable
PORT_SetPinMux(PORTA, 5u, kPORT_MuxAsGpio); //Pin 27 - *****CAN standby - NEEDS CONSULT WITH RUSS****
PORT_SetPinMux(PORTA, 12u, kPORT_MuxAlt2); //Pin 28 - CAN0_TX
PORT_SetPinMux(PORTA, 13u, kPORT_MuxAlt2); //Pin 29 -CAN0_RX
//PORT_SetPinMux(VDD, *u, kPORT_MuxALt*); //Pin 30 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VSS, *u, kPORT_MuxALt*); //Pin 31 - Pin only had a ALT0 function, which was default
PORT_SetPinMux(PORTA, 18u, kPORT_MuxAsGpio); //Pin 32
PORT_SetPinMux(PORTA, 19u, kPORT_MuxAsGpio); //Pin 33
//PORT_SetPinMux(RESET_b, *u, kPORT_MuxALt*); //Pin 34 - Pin only had a ALT0 function, which was default
PORT_SetPinMux(PORTB, 0u, kPORT_MuxAlt2); //Pin 35 - I2C0_SCL

PORT_SetPinMux(PORTB, 1u, kPORT_MuxAlt2); //Pin 36 - I2C0_SDA
PORT_SetPinMux(PORTB, 2u, kPORT_MuxAsGpio); //Pin 37 - "ALERT"
PORT_SetPinMux(PORTB, 3u, kPORT_MuxAsGpio); //Pin 38 - "I2C1_SCL - This is not wired correctly
PORT_SetPinMux(PORTB, 16u, kPORT_MuxAsGpio); //Pin 39 - "I2C1_SDA - This is not wired correctly
PORT_SetPinMux(PORTB, 17u, kPORT_MuxAsGpio); //Pin 40 -
PORT_SetPinMux(PORTB, 18u, kPORT_MuxAsGpio); //Pin 41 -
PORT_SetPinMux(PORTB, 19u, kPORT_MuxAsGpio); //Pin 42 -
PORT_SetPinMux(PORTC, 0u, kPORT_MuxAsGpio); //Pin 43 -
PORT_SetPinMux(PORTC, 1u, kPORT_MuxAsGpio); //Pin 44 -
GPIO_PinInit(GPIOC,1U,&OutConfig); // SW 9 enable
GPIO_PinWrite(GPIOC,1U,0);

PORT_SetPinMux(PORTC, 2u, kPORT_MuxAsGpio); //Pin 45 -
PORT_SetPinMux(PORTC, 3u, kPORT_MuxAsGpio); //Pin 46 -
GPIO_PinInit(GPIOC,3U,&OutConfig); // SW 10 enable
GPIO_PinWrite(GPIOC,3U,0);

//PORT_SetPinMux(VSS, *u, kPORT_MuxALt*); //Pin 47 - Pin only had a ALT0 function, which was default
//PORT_SetPinMux(VDD, *u, kPORT_MuxALt*); //Pin 48 - Pin only had a ALT0 function, which was default
PORT_SetPinMux(PORTC, 4u, kPORT_MuxAsGpio); //Pin 49 -
PORT_SetPinMux(PORTC, 5u, kPORT_MuxAsGpio); //Pin 50 -
PORT_SetPinMux(PORTC, 6u, kPORT_MuxAsGpio); //Pin 51 -
PORT_SetPinMux(PORTC, 7u, kPORT_MuxAsGpio); //Pin 52 -
GPIO_PinInit(GPIOC,7U,&OutConfig); // SW 8 enable
GPIO_PinWrite(GPIOC,7U,0);

PORT_SetPinMux(PORTC, 8u, kPORT_MuxAsGpio); //Pin 53 -
PORT_SetPinMux(PORTC, 9u, kPORT_MuxAsGpio); //Pin 54 -
GPIO_PinInit(GPIOC,9U,&OutConfig); //SW 5 enable: default to OFF
GPIO_PinWrite(GPIOC,9U,0);

PORT_SetPinMux(PORTC, 10u, kPORT_MuxAsGpio); //Pin 55 -
GPIO_PinInit(GPIOC,10U,&OutConfig); // SW 7 enable
GPIO_PinWrite(GPIOC,10U,0);

PORT_SetPinMux(PORTC, 11u, kPORT_MuxAsGpio); //Pin 56 -
PORT_SetPinMux(PORTD, 0u, kPORT_MuxAsGpio); //Pin 57 -
GPIO_PinInit(GPIOD,0U,&OutConfig); // SW 6 enable
GPIO_PinWrite(GPIOD,0U,0);

PORT_SetPinMux(PORTD, 1u, kPORT_MuxAsGpio); //Pin 58 -
PORT_SetPinMux(PORTD, 2u, kPORT_MuxAsGpio); //Pin 59 -
PORT_SetPinMux(PORTD, 3u, kPORT_MuxAsGpio); //Pin 60 -
PORT_SetPinMux(PORTD, 4u, kPORT_MuxAsGpio); //Pin 61 -
PORT_SetPinMux(PORTD, 5u, kPORT_MuxAsGpio); //Pin 62 -
PORT_SetPinMux(PORTD, 6u, kPORT_MuxAsGpio); //Pin 63 -
PORT_SetPinMux(PORTD, 7u, kPORT_MuxAsGpio); //Pin 64 -
}


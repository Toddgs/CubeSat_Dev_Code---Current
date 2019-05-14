/* This is a template file for pins configuration created by New Kinetis SDK 2.x Project Wizard. Enjoy! */

#include "fsl_device_registers.h"
#include "fsl_port.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize all pins used in this example
 */
void BOARD_InitPins(void)
{
	CLOCK_EnableClock(kCLOCK_PortA); //Enables the clock on PORTE
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORT_SetPinMux(PORTE, 0u, kPORT_MuxAlt2); //Pin 1: Bit 0 of PORTE functions as SPI1_PCS1
	PORT_SetPinMux(PORTE, 1u, kPORT_MuxAlt2); //Pin 2: Bit 1 of PORTE functions as SPI1_SOUT
	PORT_SetPinMux(PORTE, 2u, kPORT_MuxAlt2); //Pin 3: Bit 2 of PORTE functions as SPI1_SCK
	PORT_SetPinMux(PORTE, 3u, kPORT_MuxAlt2); //Pin 4: Bit 3 of PORTE functions as SPI1_SIN
	PORT_SetPinMux(PORTE, 4u, kPORT_MuxAlt2); //Pin 5: Bit 4 of PORTE functions as SPI1_PCS0
	PORT_SetPinMux(PORTE, 5u, kPORT_MuxAsGpio); //Pin 6: Bit 5 of PORTE functions as PTE5
	PORT_SetPinMux(PORTE, 6u, kPORT_MuxAsGpio); //Pin 7: Bit 6 of PORTE functions as PTE6
	//Fix PORT_SetPinMux(PORTE, 24u, kPORT_   //Pin 31: Bit 24 of PORTE functions as Enable volt regulator for TDIP Analog
	//Fix PORT_SetPinMux(PORTE, 25u,          //Pin 32: Bit 25 of PORTE functions as DAC2 power down enable (active high)
	//Fix PORT_SetPinMux(PORTE, 26u           //Pin 33: Bit 36 of PORTE functions as Enables Variable Gain Amplifier
	PORT_SetPinMux(PORTA, 0u, kPORT_MuxAlt7); //Pin 34: Bit 0 of PORTA functions as JTAG_TCLK (ezport)
	PORT_SetPinMux(PORTA, 1u, kPORT_MuxAlt7); //Pin 35: Bit 1 of PORTA functions as JTAG_TDI
	PORT_SetPinMux(PORTA, 2u, kPORT_MuxAlt7); //Pin 36: Bit 2 of PORTA functions as JTAG_TDO
	PORT_SetPinMux(PORTA, 3u, kPORT_MuxAlt7); //Pin 37: Bit 3 of PORTA functions as JTAG_TMS
	//Fix PORT_SetPinMux(PORTA, 4u, );        //Pin 38: Bit 4 of PORTA functions as EZ_PORT_b
	//Fix PORT_SetPinMux(PORTA, 5u, );        //Pin 39: Bit 5 of PORTA functions as CAN Standby enable
	PORT_SetPinMux(PORTA, 12u, kPORT_MuxAlt2); //Pin 42: Bit 12 of PORTA functions as CAN Transmit Line
	PORT_SetPinMux(PORTA, 13u, kPORT_MuxAlt2); //Pin 43: Bit 13 of PORTA functions as CAN Receive Line
	PORT_SetPinMux(PORTA, 14u, kPORT_MuxAsGpio); //Pin 44: Bit 14 of PORTA functions as PTA14
	PORT_SetPinMux(PORTA, 15u, kPORT_MuxAsGpio); //Pin 45: Bit 15 of PORTA functions as PTA15
	PORT_SetPinMux(PORTA, 16u, kPORT_MuxAsGpio); //Pin 46: Bit 16 of PORTA functions as ADC power down enable (PTA16)
	PORT_SetPinMux(PORTA, 17u, kPORT_MuxAsGpio); //Pin 47: Bit 17 of PORTA functions as DAC0 power down enable (PTA17)
	PORT_SetPinMux(PORTA, 18u, kPORT_MuxAsGpio); //Pin 50: Bit 18 of PORTA functions as PTA18
	PORT_SetPinMux(PORTA, 19u, kPORT_MuxAsGpio); //Pin 51: Bit 19 of PORTA functions as PTA19
	PORT_SetPinMux(PORTB, 0u, kPORT_MuxAlt2); //Pin 53: Bit 0 of PORTB functions aas I^2C SCL
	PORT_SetPinMux(PORTB, 1u, kPORT_MuxAlt2); //Pin 54: Bit 1 of PORTB functions as I^2C SDA
	PORT_SetPinMux(PORTB, 2u, kPORT_MuxAlt2); //Pin 55: Bit 2 of PORTB functions as I^2C Alert (Low)
	PORT_SetPinMux(PORTB, 3u, kPORT_MuxAsGpio); //Pin 56: Bit 3 of PORTB functions as PTB3
	PORT_SetPinMux(PORTB, 9u, kPORT_MuxAsGpio); //Pin 57: Bit 9 of PORTB functions as PTB9
	PORT_SetPinMux(PORTB, 10u, kPORT_MuxAlt3); //Pin 58: Bit 10 of PORTB functions as UART RX
	PORT_SetPinMux(PORTB, 11u, kPORT_MuxAlt3); //Pin 59: Bit 11 of PORTB functions as UART TX
	PORT_SetPinMux(PORTB, 16u, kPORT_MuxAsGpio); //Pin 62: Bit 16 of PORTB functions as PTB16
	PORT_SetPinMux(PORTB, 17u, kPORT_MuxAsGpio); //Pin 63: Bit 17 of PORTB functions as PTB17
	PORT_SetPinMux(PORTB, 20u, kPORT_MuxAsGpio); //Pin 66: Bit 20 of PORTB functions as PTB20
	PORT_SetPinMux(PORTB, 21u, kPORT_MuxAsGpio); //Pin 67: Bit 21 of PORTB functions as PTB21
	PORT_SetPinMux(PORTB, 22u, kPORT_MuxAsGpio); //Pin 68: Bit 22 of PORTB functions as PTB22
	PORT_SetPinMux(PORTB, 23u, kPORT_MuxAsGpio); //Pin 69: Bit 23 of PORTB functions as PTB23
	PORT_SetPinMux(PORTC, 3u, kPORT_MuxAlt5); //Pin 73: Bit 3 of PORTC functions as CLKOUT
	PORT_SetPinMux(PORTC, 12u, kPORT_MuxAsGpio); //Pin 84: Bit 12 of PORTC functions as RED LED enable active high
	PORT_SetPinMux(PORTC, 13u, kPORT_MuxAsGpio); //Pin 85: Bit 13 of PORTC functions as GREEN LED enable active high
	PORT_SetPinMux(PORTC, 14u, kPORT_MuxAsGpio); //Pin 86: Bit 14 of PORTC functions as PTC14
	PORT_SetPinMux(PORTC, 15u, kPORT_MuxAsGpio); //Pin 87: Bit 15 of PORTC functions as PTC15
	PORT_SetPinMux(PORTC, 16u, kPORT_MuxAsGpio); //Pin 90: Bit 16 of PORTC functions as PTC16
	PORT_SetPinMux(PORTC, 17u, kPORT_MuxAsGpio); //Pin 91: Bit 17 of PORTC functions as PTC17
	PORT_SetPinMux(PORTC, 18u, kPORT_MuxAsGpio); //Pin 92: Bit 18 of PORTC functions as PTC18
	PORT_SetPinMux(PORTD, 1u, kPORT_MuxAsGpio); //Pin 94: Bit 1 of PORTD functions as 120 mhz enable for CPLD
	PORT_SetPinMux(PORTD, 7u, kPORT_MuxAsGpio); //Pin 100: Bit 7 of PORTD functions as CPLD Output Enable

	// Flexbus ADs
	PORT_SetPinMux(PORTB, 18u, kPORT_MuxAlt5); //Pin 64: Bit 18 of PORTB functions as FB_AD15
	PORT_SetPinMux(PORTC, 0u, kPORT_MuxAlt5); //Pin 70: Bit 0 of PORTC functions as FB_AD14
	PORT_SetPinMux(PORTC, 1u, kPORT_MuxAlt5); //Pin 71: Bit 1 of PORTC functions as FB_AD13
	PORT_SetPinMux(PORTC, 2u, kPORT_MuxAlt5); //Pin 72: Bit 2 of PORTC functions as FB_AD12
	PORT_SetPinMux(PORTC, 4u, kPORT_MuxAlt5); //Pin 76: Bit 4 of PORTC functions as FB_AD11
	PORT_SetPinMux(PORTC, 5u, kPORT_MuxAlt5); //Pin 77: Bit 5 of PORTC functions as FB_AD10
	PORT_SetPinMux(PORTC, 6u, kPORT_MuxAlt5); //Pin 78: Bit 6 of PORTC functions as FB_AD9
	PORT_SetPinMux(PORTC, 7u, kPORT_MuxAlt5); //Pin 79: Bit 7 of PORTC functions as FB_AD8
	PORT_SetPinMux(PORTC, 8u, kPORT_MuxAlt5); //Pin 80: Bit 8 of PORTC functions as FB_AD7
	PORT_SetPinMux(PORTC, 9u, kPORT_MuxAlt5); //Pin 81: Bit 9 of PORTC functions as FB_AD6
	PORT_SetPinMux(PORTC, 10u, kPORT_MuxAlt5); //Pin 82: Bit 10 of PORTC functions as FB_AD5
	PORT_SetPinMux(PORTD, 2u, kPORT_MuxAlt5); //Pin 95: Bit 2 of PORTD functions as FB_AD4
	PORT_SetPinMux(PORTD, 3u, kPORT_MuxAlt5); //Pin 96: Bit 3 of PORTD functions as FB_AD3
	PORT_SetPinMux(PORTD, 4u, kPORT_MuxAlt5); //Pin 97: Bit 4 of PORTD functions as FB_AD2
	PORT_SetPinMux(PORTD, 5u, kPORT_MuxAlt5); //Pin 98: Bit 5 of PORTD functions as FB_AD1
	PORT_SetPinMux(PORTD, 6u, kPORT_MuxAlt5); //Pin 99: Bit 6 of PORTD functions as FB_AD0

	// Flexbus other lines
	PORT_SetPinMux(PORTC, 3u, kPORT_MuxAlt5); //Pin 73: Bit 3 of PORTC functions as CLKOUT
	PORT_SetPinMux(PORTD, 0u, kPORT_MuxAlt5); //Pin 93: Bit 0 of PORTD functions as FB_ALE
	PORT_SetPinMux(PORTC, 11u, kPORT_MuxAlt5); //Pin 83: Bit 11 of PORTC functions as FB_RW_b
	PORT_SetPinMux(PORTB, 19u, kPORT_MuxAlt5); //Pin 65: Bit 19 of PORTB functions as FB_OE_b
}

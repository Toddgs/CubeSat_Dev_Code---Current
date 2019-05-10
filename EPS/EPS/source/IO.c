/*
 * IO.c
 *
 *  Created on: Jun 18, 2018
 *      Author: edmundspencer
 */


#include "fsl_gpio.h"
#include "fsl_debug_console.h"
#include "fsl_uart.h"

	uint8_t V5_en, V5_pgood;
	uint8_t V33_en, V33_pgood;

	uint8_t Charger_1_status;
	uint8_t Charger_1_faults;
	uint8_t Charger_2_status;
	uint8_t Charger_2_faults;

	uint8_t SW6_en, SW6_OCflag;
	uint8_t SW7_en, SW7_OCflag;
	uint8_t SW5_en, SW5_OCflag;
	uint8_t SW8_en, SW8_OCflag;
	uint8_t SW10_en, SW10_OCflag;
	uint8_t SW9_en, SW9_OCflag;
	uint8_t V33D_en, V33D_OCflag;   // This is the enable and OC for the 3.3 V Digital Switch
								// Not that you would ever use it, this switches power to the microcontroller itself

	uart_config_t UARTConfig;

void ReadCharger1UART(void){

	char Charger1Stat[2];

	printf("Initializing UART 1... \r\n");

	UART_GetDefaultConfig(&UARTConfig);
	UARTConfig.baudRate_Bps = 2400U;
	UARTConfig.enableTx = true;
	UARTConfig.enableRx = true;\
	UART_Init(UART1, &UARTConfig, 20971520U);

	printf("Waiting for 2 chars... \r\n");

	UART_ReadBlocking(UART1, Charger1Stat, 2);

	printf("Charger 1 status: %X %X\r\n",Charger1Stat[0],Charger1Stat[1]);


}

void ReadPowerStatus(void){

	V5_en = GPIO_PinRead(GPIOD,3);
	V5_pgood = GPIO_PinRead(GPIOD,2);

	V33_en = GPIO_PinRead (GPIOD, 1);
	V33_pgood = GPIO_PinRead (GPIOC, 11);
	printf("5V enable: %X, 5V pgood: %X \r\n", V5_en, V5_pgood);
	printf("33V enable: %X, 33V pgood: %X \r\n", V33_en, V33_pgood);

}

void ReadChargerStatus(void){

	Charger_1_status = GPIO_PinRead (GPIOD, 7) ;
	Charger_1_faults = GPIO_PinRead (GPIOD, 6) ;

	Charger_2_status = GPIO_PinRead (GPIOD, 5);
	Charger_2_faults= GPIO_PinRead (GPIOD, 4);
	printf("Charger 1 status: %X, faults: %X \r\n", Charger_1_status, Charger_1_faults);
	printf("Charger 2 status: %X, faults: %X \r\n", Charger_2_status, Charger_2_faults);

}

void ReadSwitchStatus(void){

	SW6_en = GPIO_PinRead(GPIOD,0);
	SW6_OCflag = GPIO_PinRead(GPIOC,4);

	SW7_en = GPIO_PinRead (GPIOC, 10);
	SW7_OCflag = GPIO_PinRead (GPIOC, 5);

	SW5_en = GPIO_PinRead (GPIOC, 9);
	SW5_OCflag = GPIO_PinRead (GPIOC, 8);

	SW8_en = GPIO_PinRead (GPIOC, 7);
	SW8_OCflag = GPIO_PinRead (GPIOC, 6);

	SW10_en = GPIO_PinRead (GPIOC, 3);
	SW10_OCflag = GPIO_PinRead (GPIOC, 2);

	SW9_en = GPIO_PinRead (GPIOC, 1);
	SW9_OCflag = GPIO_PinRead (GPIOC, 0);

	V33D_en = GPIO_PinRead (GPIOB, 19);
	V33D_OCflag = GPIO_PinRead (GPIOB, 18);

	printf("SW5  enable: %X, OC: %X \r\n", SW5_en, SW5_OCflag);
	printf("SW6  enable: %X, OC: %X \r\n", SW6_en, SW6_OCflag);
	printf("SW7  enable: %X, OC: %X \r\n", SW7_en, SW7_OCflag);
	printf("SW8  enable: %X, OC: %X \r\n", SW8_en, SW8_OCflag);
	printf("SW9  enable: %X, OC: %X \r\n", SW9_en, SW9_OCflag);
	printf("SW10 enable: %X, OC: %X \r\n", SW10_en, SW10_OCflag);
	printf("V33D enable: %X, OC: %X \r\n", V33D_en, V33D_OCflag);

}

void TurnOnAllSwitches(void){

	GPIO_PinWrite(GPIOD,0,1U); //SW 6

	GPIO_PinWrite (GPIOC, 10, 1U); //SW 7

	GPIO_PinWrite (GPIOC, 9, 1U); //SW 5

	GPIO_PinWrite (GPIOC, 7, 1U); //SW 8

	GPIO_PinWrite (GPIOC, 3, 1U); // SW 10

	GPIO_PinWrite (GPIOC, 1, 1U); //SW 9

	printf("All switches enabled.\r\n");

}
void TurnOffAllSwitches(void){

	GPIO_PinWrite(GPIOD,0,0U); //SW 6

	GPIO_PinWrite (GPIOC, 10, 0U); //SW 7

	GPIO_PinWrite (GPIOC, 9, 0U); //SW 5

	GPIO_PinWrite (GPIOC, 7, 0U); //SW 8

	GPIO_PinWrite (GPIOC, 3, 0U); // SW 10

	GPIO_PinWrite (GPIOC, 1, 0U); //SW 9

	printf("All switches disabled.\r\n");

}


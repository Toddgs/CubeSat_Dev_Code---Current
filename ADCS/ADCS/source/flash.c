/*
 * flash.c
 *
 *  Created on: Apr 18, 2018
 *      Author: edmundspencer
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"
#include "fsl_adc16.h"
#include "fsl_flexbus.h"

#define FLEX_START_ADDRESS 0x60000000U

flexbus_config_t MyConfig; //Holds the details of our Flexbus config

uint32_t *address = (uint32_t *)FLEX_START_ADDRESS;
uint32_t *ptr1;

/* to init Flexbus...  Contents of flexbus_config_t data structure													Default
    uint8_t chip;                                      /*!< Chip FlexBus for validation 							0
    uint8_t waitStates;                                /*!< Value of wait states
    uint32_t chipBaseAddress;                          /*!< Chip base address for using FlexBus
    uint32_t chipBaseAddressMask;                      /*!< Chip base address mask
    bool writeProtect;                                 /*!< Write protected 										0
    bool burstWrite;                                   /*!< Burst-Write enable 										0
    bool burstRead;                                    /*!< Burst-Read enable 										0
    bool byteEnableMode;                               /*!< Byte-enable mode support 								0
    bool autoAcknowledge;                              /*!< Auto acknowledge setting 								true
    bool extendTransferAddress;                        /*!< Extend transfer start/extend address latch enable 		0
    bool secondaryWaitStates;                          /*!< Secondary wait states number 							0
    flexbus_port_size_t portSize;                      /*!< Port size of transfer
    flexbus_bytelane_shift_t byteLaneShift;            /*!< Byte-lane shift enable 									Not shifted
    flexbus_write_address_hold_t writeAddressHold;     /*!< Write address hold or deselect option 					1 cycle
    flexbus_read_address_hold_t readAddressHold;       /*!< Read address hold or deselect option 					0 cycles
    flexbus_address_setup_t addressSetup;              /*!< Address setup setting 									First rising edge
    flexbus_multiplex_group1_t group1MultiplexControl; /*!< FlexBus Signal Group 1 Multiplex control 				ALE
    flexbus_multiplex_group2_t group2MultiplexControl; /*!< FlexBus Signal Group 2 Multiplex control 				CS4
    flexbus_multiplex_group3_t group3MultiplexControl; /*!< FlexBus Signal Group 3 Multiplex control 				CS5
    flexbus_multiplex_group4_t group4MultiplexControl; /*!< FlexBus Signal Group 4 Multiplex control 				TBST
    flexbus_multiplex_group5_t group5MultiplexControl; /*!< FlexBus Signal Group 5 Multiplex control 				TA
 */


void FLASH_Init(void){
	FLEXBUS_GetDefaultConfig(&MyConfig);

	MyConfig.waitStates = 2U;  // Just guessing N=2 wait states...
	MyConfig.portSize = kFLEXBUS_1Byte;  // Trying 1 byte for now to get addressing correct...
	MyConfig.byteLaneShift = kFLEXBUS_Shifted;
	MyConfig.chipBaseAddress = FLEX_START_ADDRESS;
	MyConfig.chipBaseAddressMask = 0x00FFU; // Need 24 bits of address, so 16 bits of BAM
	MyConfig.readAddressHold = kFLEXBUS_Hold2Or1Cycles; //Extending Read address for kicks...
	MyConfig.writeAddressHold = kFLEXBUS_Hold2Cycles; // Extending 2 cycles for a write.  Keeps data on bus after CS goes high.
	MyConfig.addressSetup = kFLEXBUS_SecondRisingEdge; // Delay after asserting address so that DFF can latch it in before using it.
	FLEXBUS_Init(FB,&MyConfig);

}

void Flash_Test(void){

#define	FType	uint8_t

	FType TestWord;
	volatile FType *FlashPtr;

	printf("Init flash and Flexbus...\r\n");
	FLASH_Init();

	printf("Reading flash...\r\n");

	printf("Reading words of flash..\r\n");
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x055);
	TestWord = *FlashPtr;
	printf("Read 0x55.  Result =%04x\r\n",TestWord);
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x0AA);
	TestWord = *FlashPtr;
	printf("Read 0xAA.  Result =%04x\r\n",TestWord);
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x000);
	TestWord = *FlashPtr;
	printf("Read 0x00.  Result =%04x\r\n",TestWord);

	//Read Device ID:
	//Write AA to 555
	//Write 55 to 2AA
	//Write 90 to 555
	//Read X01, expect 227E
	//Read X0E, expect XX21
	//Read X0F, expect XX01

	//printf("Resetting Flash Memory...\r\n");
	//GPIO_PinWrite(GPIOD,15U,0);
	//GPIO_PinWrite(GPIOD,15U,1);

	printf("Reading device ID...\r\n");

	//Put Flash in Autoselect
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x555);
	*FlashPtr = 0x00AA;
	printf("Wrote to 0x555...");
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x2AA);
	*FlashPtr = 0x0055;
	printf("Wrote to 0x2aa...");
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x555);
	*FlashPtr = 0x0090;
	printf("Wrote to 0x555...\r\n");

	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x000);
	TestWord = *FlashPtr;
	printf("Read 0x00.  Result =%04x\r\n",TestWord);
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x001);
	TestWord = *FlashPtr;
	printf("Read 0x01.  Result =%04x\r\n",TestWord);
    FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x00E);
	TestWord = *FlashPtr;
	printf("Read 0x0E.  Result =%04x\r\n",TestWord);
	FlashPtr = (FType *)(FLEX_START_ADDRESS + 0x00F);
	TestWord = *FlashPtr;
	printf("Read 0x0F.  Result =%04x\r\n",TestWord);

}



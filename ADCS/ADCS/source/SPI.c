/*
 * SPI.c
 *
 *  Created on: Mar 5, 2018
 *      Author: Student
 */
#include "fsl_dspi.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"


#define MAX_TRANSFER_SIZE 4

dspi_master_config_t masterConfig;
SPI_Type base;
dspi_transfer_t transfer;


static uint8_t ReceiveData[MAX_TRANSFER_SIZE];
static uint8_t SendData[MAX_TRANSFER_SIZE];

//  Definition of dspi_transfer_t //TODO can prolly get rid of this as we can just peek the definition...
// 	uint8_t *txData;          /*!< Send buffer. */
//    uint8_t *rxData;          /*!< Receive buffer. */
//    volatile size_t dataSize; /*!< Transfer bytes. */
//
//    uint32_t
//        configFlags; /*!< Transfer transfer configuration flags; set from _dspi_transfer_config_flag_for_master if the
//                        transfer is used for master or _dspi_transfer_config_flag_for_slave enumeration if the transfer
//                        is used for slave.*/

//WHO AM I
int DOF_Test(void) {


	printf("\rInitializingSPI...\n\r");
	DSPI_MasterGetDefaultConfig(&masterConfig);
	DSPI_MasterInit(SPI0, &masterConfig, 20971520U);

	printf("\rInitializing struct...\n\r");
	transfer.txData = SendData;
	transfer.rxData = ReceiveData;
	transfer.dataSize = 2;
	transfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterPcs0 | kDSPI_MasterCtar0;

	SendData[0] = 0xf5; //Address of Who Am I register
	SendData[1] = 0x00;  //Dummy data for Who Am I
	printf("\rSending... %3d or 0x%x\n\r",SendData[0],SendData[0]);

	printf("\rTransferring...\n\r");
	DSPI_MasterTransferBlocking(SPI0, &transfer);

	printf("\rSPI Dummy Data Byte 0: %3d or 0x%x\r\n",ReceiveData[0],ReceiveData[0]);
	printf("\rSPI Dummy Data Byte 1: %3d or 0x%x\r\n",ReceiveData[1],ReceiveData[1]); //Should be 0x68

	return(0);
}

int SPI_Test(void) {


	printf("\rInitializingSPI...\n\r");
	DSPI_MasterGetDefaultConfig(&masterConfig);
	DSPI_MasterInit(SPI0, &masterConfig, 20971520U);

	printf("\rInitializing struct...\n\r");
	transfer.txData = SendData;
	transfer.rxData = ReceiveData;
	transfer.dataSize = 2;
	transfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterPcs0 | kDSPI_MasterCtar0;

	for(;;){

		SendData[0] = (0x43 | (1 << 7)); //Address of Gyro Xmsb
		SendData[1] = 0xff;  //Dummy data
		SendData[2] = (0x44 | (1 << 7)); //Address of Gyro Xlsb
		SendData[3] = 0xff;  //Dummy data
		DSPI_MasterTransferBlocking(SPI0, &transfer);
		printf("\rSPI Dummy Data Byte X: 0x%x\r\n",(ReceiveData[0] << 8) | (ReceiveData[1]));

		SendData[0] = (0x45 | (1 << 7)); //Address of Gyro Ymsb
		SendData[1] = 0xff;  //Dummy data
		SendData[2] = (0x46 | (1 << 7)); //Address of Gyro Ylsb
		SendData[3] = 0xff;  //Dummy data
		DSPI_MasterTransferBlocking(SPI0, &transfer);
		printf("\rSPI Dummy Data Byte Y: 0x%x\r\n",(ReceiveData[0] << 8) | (ReceiveData[1]));

		SendData[0] = (0x47 | (1 << 7)); //Address of Gyro Zmsb
		SendData[1] = 0xff;  //Dummy data
		SendData[2] = (0x48 | (1 << 7)); //Address of Gyro Zlsb
		SendData[3] = 0xff;  //Dummy data
		DSPI_MasterTransferBlocking(SPI0, &transfer);
		printf("\rSPI Dummy Data Byte Z: 0x%x\r\n",(ReceiveData[0] << 8) | (ReceiveData[1]));

		printf("\r\n");

		delay(5000);
	}
	return(0);
}

// Temperature Test
int Temp_Test(void) {


	printf("\rInitializingSPI...\n\r");
	DSPI_MasterGetDefaultConfig(&masterConfig);
	DSPI_MasterInit(SPI0, &masterConfig, 20971520U);

	printf("\rInitializing struct...\n\r");
	transfer.txData = SendData;
	transfer.rxData = ReceiveData;
	transfer.dataSize = 2;
	transfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterPcs0 | kDSPI_MasterCtar0;

	for(;;){ //TODO Maybe change this to while(true)? Dunno why they used this infinite loop.

		SendData[0] = (0x41 | (1 << 7)); //Address of Temp msb
		SendData[1] = 0xff;  //Dummy data
		SendData[2] = (0x42 | (1 << 7)); //Address of Temp lsb
		SendData[3] = 0xff;  //Dummy data
		DSPI_MasterTransferBlocking(SPI0, &transfer);
		printf("\rSPI Dummy Data Byte X: 0x%x\r\n",(ReceiveData[0] << 8) | (ReceiveData[1]));


		delay(5000);
	}
	return(0);
}




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
#include "fsl_i2c.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
//#include "MK22FA12.h"

#define MAX_TRANSFER_SIZE 8   //unsure max size (TODO: We should prolly find out what the max size is...)

#define MAG_I2C_ADDR	0x0E
#define MAG_CMDREG		0x10
#define MAG_WHOAMI		0x07
#define	MAG_X			0x01
#define MAG_Y			0x03
#define	MAG_Z			0x05

i2c_master_config_t masterConfig;
I2C_Type base;
i2c_master_transfer_t transfer;

static uint8_t ReceiveData[MAX_TRANSFER_SIZE];
static uint8_t SendData[MAX_TRANSFER_SIZE];

// For reference
//typedef struct _i2c_master_transfer
//{
    //uint32_t flags;            /*!< A transfer flag which controls the transfer. */
    //uint8_t slaveAddress;      /*!< 7-bit slave address. */
    //i2c_direction_t direction; /*!< A transfer direction, read or write. */
    //uint32_t subaddress;       /*!< A sub address. Transferred MSB first. */
    //uint8_t subaddressSize;    /*!< A size of the command buffer. */
    //uint8_t *volatile data;    /*!< A transfer buffer. */
    //volatile size_t dataSize;  /*!< A transfer size. */
//} i2c_master_transfer_t;

void I2C_Init(I2C_Type *i2cType)
{
	int SendData;

	printf("\rInitializingI2C...\n\r");
	I2C_MasterGetDefaultConfig(&masterConfig);
	I2C_MasterInit(i2cType, &masterConfig, 20971520U);

}



void I2C_Write(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, uint8_t *WriteData)
{
	i2c_master_transfer_t transfer;

	printf("\rInitializing struct...\n\r");
	transfer.flags = 0; /*!< A transfer flag which controls the transfer. */
	transfer.slaveAddress = DeviceAddress; /*!< 7-bit slave address. */
	transfer.direction = kI2C_Write; /*!< A transfer direction, read or write. */
	transfer.subaddress = StartAddress; /*!< A sub address. Transferred MSB first. */
	transfer.subaddressSize = WriteDataNumBytes; /*!< A size of the command buffer. */
	transfer.data = WriteData; /*!< A transfer buffer. */
	transfer.dataSize = WriteDataNumBytes; /*!< A transfer size. */
	printf("\rSending ... \n\r" );

	I2C_MasterTransferBlocking(i2cType, &transfer);

}

void I2C_Read(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, uint8_t *WriteData)
{
	i2c_master_transfer_t transfer;

	printf("\rInitializing struct...\n\r");
	transfer.flags = 0; /*!< A transfer flag which controls the transfer. */
	transfer.slaveAddress = DeviceAddress; /*!< 7-bit slave address. */
	transfer.direction = kI2C_Read; /*!< A transfer direction, read or write. */
	transfer.subaddress = StartAddress; /*!< A sub address. Transferred MSB first. */
	transfer.subaddressSize = WriteDataNumBytes; /*!< A size of the command buffer. */
	transfer.data = WriteData; /*!< A transfer buffer. */
	transfer.dataSize = WriteDataNumBytes; /*!< A transfer size. */
	printf("\rReading ... \n\r" );

	I2C_MasterTransferBlocking(i2cType, &transfer);
}



//WHO AM I
int I2C_Test(void) {
	int i;

	I2C_Init(I2C0);


	printf("\n\rSending Command to Command Reg...\n\r");
	SendData[0] = 0xE5;
	I2C_Write(I2C0, MAG_I2C_ADDR,MAG_CMDREG,1,SendData);
	//I2C_MasterTransferBlocking(I2C0, &transfer);

	printf("\n\rReading Command Reg back...\n\r");
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_CMDREG,1,ReceiveData);
	printf("\r Data received = %02x\n\r",ReceiveData[0]);

	printf("\n\rReading whoami register\n\r");
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_WHOAMI,1,ReceiveData);
	printf("\r Data received = %02x\n\r",ReceiveData[0]);

	printf("\rRead 1st 8 bytes\n\r");
	I2C_Read(I2C0, MAG_I2C_ADDR,0x07,8,ReceiveData);

	printf("\r Data received = ");

	for (i=0;i<MAX_TRANSFER_SIZE;i++){
			printf("%02x ",ReceiveData[i]);
	}
	printf("\r\n");

	return(0);
}

int I2C_X()
{
	int msb, lsb;
	int reading;
	int i; //Is this unused? TODO: Maybe get rid of unused variables.

	printf("\rRead X bytes\n\r");
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_X,1,ReceiveData);
	msb = ReceiveData[0];
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_X+1,1,ReceiveData);
	lsb = ReceiveData[0];

	printf("\r Data received = %02x %02x\r\n", msb, lsb);

	if (msb>0x7F){
		reading = 0xFFFF0000;
		reading |= (msb<<8);
		reading |= lsb;
		//reading = -reading;
	} else {
		reading = (msb<<8) | lsb;
	}

	printf("\r Data of X = %d \n\r", reading);

	return(0);

}

int I2C_Y()
{
	int msb, lsb;
	int reading;
	int i; //This might be unused as well...

	printf("\rRead Y bytes\n\r");
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_Y,1,ReceiveData);
	msb = ReceiveData[0];
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_Y+1,1,ReceiveData);
	lsb = ReceiveData[0];

	printf("\r Data received = %02x %02x\r\n", msb, lsb);

	if (msb>0x7F){
		reading = 0xFFFF0000;
		reading |= (msb<<8);
		reading |= lsb;
		//reading = -reading; Why is this commented out? What did it do?
	} else {
		reading = (msb<<8) | lsb;
	}

	printf("\r Data of Y = %d \n\r", reading);


	return(0);

}

int I2C_Z()
{

	int msb, lsb;
	int reading;
	int i; //Again, unused, why?

	printf("\rRead Z bytes\n\r");
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_Z,1,ReceiveData);
	msb = ReceiveData[0];
	I2C_Read(I2C0, MAG_I2C_ADDR,MAG_Z+1,1,ReceiveData);
	lsb = ReceiveData[0];

	printf("\r Data received = %02x %02x\r\n", msb, lsb);

	if (msb>0x7F){
		reading = 0xFFFF0000;
		reading |= (msb<<8);
		reading |= lsb;
		//reading = -reading;
	} else {
		reading = (msb<<8) | lsb;
	}

	printf("\r Data of Z = %d \n\r", reading);


	return(0);

}





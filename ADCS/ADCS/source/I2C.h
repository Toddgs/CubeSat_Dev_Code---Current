/*
 * I2C.h
 * TODO: Who was working on this project on this date? Might be able to tell us something about it...
 *  Created on: Jun 15, 2018
 *      Author: Student
 */

#ifndef SOURCE_I2C_H_
#define SOURCE_I2C_H_

void I2C_Init(I2C_Type *i2cType);

void I2C_Write(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, uint8_t *WriteData);

void I2C_Read(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, uint8_t *WriteData);



#endif /* SOURCE_I2C_H_ */

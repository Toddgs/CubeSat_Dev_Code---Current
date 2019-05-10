/*
 * ADC.c
 *
 *  Created on: Apr 6, 2018
 *      Author: edmundspencer
 */

#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"
#include "fsl_adc16.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

adc16_config_t	DefaultConfig;
adc16_channel_config_t TempSensorChannel;
uint32_t TempSensorChannelGroup = 0;
uint32_t ADCFlag;
uint32_t TempSensorVoltage;
int i;

int Temp_Test_ADC(void){

	long temp;
	float calc;
	int left,right;


	printf("\rInitalizing ADC 1...");

	ADC16_GetDefaultConfig(&DefaultConfig);
	ADC16_Init(ADC1, &DefaultConfig);  //Initializes ADC\

	printf("done!\r\n");

	TempSensorChannel.channelNumber = 16;
	TempSensorChannel.enableInterruptOnConversionCompleted = false;
	TempSensorChannel.enableDifferentialConversion = false;

	ADC16_SetChannelConfig(ADC1, TempSensorChannelGroup, &TempSensorChannel);

	ADCFlag = ADC16_GetChannelStatusFlags(ADC1, TempSensorChannelGroup);
	TempSensorVoltage = ADC16_GetChannelConversionValue(ADC1, TempSensorChannelGroup);

	printf("Flags: 0x%08x Voltage: 0x%08x %d \r\n",ADCFlag,TempSensorVoltage, TempSensorVoltage);

	while ( (ADCFlag&0x80)==0 ){
		ADCFlag = ADC16_GetChannelStatusFlags(ADC1, TempSensorChannelGroup);
	}
	TempSensorVoltage = ADC16_GetChannelConversionValue(ADC1, TempSensorChannelGroup);

	printf("Flags: 0x%08x Voltage: 0x%08x %d \r\n",ADCFlag,TempSensorVoltage, TempSensorVoltage);

	temp = TempSensorVoltage * 33 / 10;
	temp *= 1000;
	temp /= 4095;

	left = temp/1000;
	right = temp - left*1000;

	printf("Measured voltage: ");
	printf("%d.%03d",left,right);
	printf(" Volts\r\n");

	printf("\r\nConvert to Celsius: ");
	calc = 1324 - temp;
	calc = -4 * -0.00262*calc;
	calc = (8.194*8.194)+calc;
	calc = sqrt(calc);
	calc = 8.194 - calc;
	calc /= (-2*0.00262);
	calc += 30;

	left = calc;
	right = (calc - left)*1000;
	printf("temperature is %d.%03d\r\n",left,right);




}


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/I2C.c \
../source/SPI.c \
../source/Temperature.c \
../source/flash.c \
../source/main.c 

OBJS += \
./source/I2C.o \
./source/SPI.o \
./source/Temperature.o \
./source/flash.o \
./source/main.o 

C_DEPS += \
./source/I2C.d \
./source/SPI.d \
./source/Temperature.d \
./source/flash.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MK22FX512AVLQ12 -DCPU_MK22FX512AVLQ12_cm4 -I../CMSIS -I../board -I../drivers -I../utilities -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



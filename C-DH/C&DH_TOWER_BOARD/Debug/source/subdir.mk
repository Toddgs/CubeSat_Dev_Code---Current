################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/event.c \
../source/main.c 

OBJS += \
./source/event.o \
./source/main.o 

C_DEPS += \
./source/event.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DFSL_RTOS_BM -DCPU_MK21FN1M0AVLQ12 -DSDK_OS_BAREMETAL -DCPU_MK21FN1M0AVLQ12_cm4 -I../CMSIS -I../board -I../drivers -I../utilities -I../sdmmc -I../sdmmc/inc -I../sdmmc/src -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



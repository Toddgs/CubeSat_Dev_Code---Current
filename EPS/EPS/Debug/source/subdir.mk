################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/IO.c \
../source/main.c 

OBJS += \
./source/IO.o \
./source/main.o 

C_DEPS += \
./source/IO.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MK22FN1M0VLH12 -DCPU_MK22FN1M0VLH12_cm4 -I../CMSIS -I../board -I../drivers -I../utilities -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



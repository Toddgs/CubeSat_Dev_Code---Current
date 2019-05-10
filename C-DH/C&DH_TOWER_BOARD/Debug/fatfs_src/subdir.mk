################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fatfs_src/diskio.c \
../fatfs_src/ff.c \
../fatfs_src/fsl_sd_disk.c 

OBJS += \
./fatfs_src/diskio.o \
./fatfs_src/ff.o \
./fatfs_src/fsl_sd_disk.o 

C_DEPS += \
./fatfs_src/diskio.d \
./fatfs_src/ff.d \
./fatfs_src/fsl_sd_disk.d 


# Each subdirectory must supply rules for building sources it contributes
fatfs_src/%.o: ../fatfs_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DFSL_RTOS_BM -DCPU_MK21FN1M0AVLQ12 -DSDK_OS_BAREMETAL -DCPU_MK21FN1M0AVLQ12_cm4 -I../CMSIS -I../board -I../drivers -I../utilities -I../sdmmc -I../sdmmc/inc -I../sdmmc/src -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



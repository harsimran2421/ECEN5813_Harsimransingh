################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/DMA.c \
../Sources/RTC.c \
../Sources/binary_logger.c \
../Sources/circbuf.c \
../Sources/conversion.c \
../Sources/gpio.c \
../Sources/main.c \
../Sources/memory.c \
../Sources/non_block_logger.c \
../Sources/nrf.c \
../Sources/profiler.c \
../Sources/project2.c \
../Sources/spi.c \
../Sources/systick.c \
../Sources/uart.c 

OBJS += \
./Sources/DMA.o \
./Sources/RTC.o \
./Sources/binary_logger.o \
./Sources/circbuf.o \
./Sources/conversion.o \
./Sources/gpio.o \
./Sources/main.o \
./Sources/memory.o \
./Sources/non_block_logger.o \
./Sources/nrf.o \
./Sources/profiler.o \
./Sources/project2.o \
./Sources/spi.o \
./Sources/systick.o \
./Sources/uart.o 

C_DEPS += \
./Sources/DMA.d \
./Sources/RTC.d \
./Sources/binary_logger.d \
./Sources/circbuf.d \
./Sources/conversion.d \
./Sources/gpio.d \
./Sources/main.d \
./Sources/memory.d \
./Sources/non_block_logger.d \
./Sources/nrf.d \
./Sources/profiler.d \
./Sources/project2.d \
./Sources/spi.d \
./Sources/systick.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIBS/BUTTON.c \
../LIBS/DHT11.c \
../LIBS/DS3231.c \
../LIBS/HCSR04.c \
../LIBS/ROTARY_ENCODER.c \
../LIBS/delay.c \
../LIBS/lcd_i2c.c 

OBJS += \
./LIBS/BUTTON.o \
./LIBS/DHT11.o \
./LIBS/DS3231.o \
./LIBS/HCSR04.o \
./LIBS/ROTARY_ENCODER.o \
./LIBS/delay.o \
./LIBS/lcd_i2c.o 

C_DEPS += \
./LIBS/BUTTON.d \
./LIBS/DHT11.d \
./LIBS/DS3231.d \
./LIBS/HCSR04.d \
./LIBS/ROTARY_ENCODER.d \
./LIBS/delay.d \
./LIBS/lcd_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
LIBS/%.o LIBS/%.su: ../LIBS/%.c LIBS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Tuan/STM32CubeIDE/workspace_1.11.2/DIGITAL_CLOCK/LIBS" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LIBS

clean-LIBS:
	-$(RM) ./LIBS/BUTTON.d ./LIBS/BUTTON.o ./LIBS/BUTTON.su ./LIBS/DHT11.d ./LIBS/DHT11.o ./LIBS/DHT11.su ./LIBS/DS3231.d ./LIBS/DS3231.o ./LIBS/DS3231.su ./LIBS/HCSR04.d ./LIBS/HCSR04.o ./LIBS/HCSR04.su ./LIBS/ROTARY_ENCODER.d ./LIBS/ROTARY_ENCODER.o ./LIBS/ROTARY_ENCODER.su ./LIBS/delay.d ./LIBS/delay.o ./LIBS/delay.su ./LIBS/lcd_i2c.d ./LIBS/lcd_i2c.o ./LIBS/lcd_i2c.su

.PHONY: clean-LIBS


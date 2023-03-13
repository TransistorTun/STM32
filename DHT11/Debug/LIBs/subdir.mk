################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIBs/lcd_i2c.c 

OBJS += \
./LIBs/lcd_i2c.o 

C_DEPS += \
./LIBs/lcd_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
LIBs/%.o LIBs/%.su: ../LIBs/%.c LIBs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Tuan/STM32CubeIDE/workspace_1.11.2/LCD_learn_ver1/Lib" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Tuan/STM32CubeIDE/workspace_1.11.2/LCD_learn_ver1" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LIBs

clean-LIBs:
	-$(RM) ./LIBs/lcd_i2c.d ./LIBs/lcd_i2c.o ./LIBs/lcd_i2c.su

.PHONY: clean-LIBs


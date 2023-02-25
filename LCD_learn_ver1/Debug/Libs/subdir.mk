################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libs/lcd_i2c.c 

OBJS += \
./Libs/lcd_i2c.o 

C_DEPS += \
./Libs/lcd_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Libs/%.o Libs/%.su: ../Libs/%.c Libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Tuan/STM32CubeIDE/workspace_1.11.2/LCD_learn_ver1/Libs" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libs

clean-Libs:
	-$(RM) ./Libs/lcd_i2c.d ./Libs/lcd_i2c.o ./Libs/lcd_i2c.su

.PHONY: clean-Libs


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/ROTARY_ENCODER.c 

OBJS += \
./Lib/ROTARY_ENCODER.o 

C_DEPS += \
./Lib/ROTARY_ENCODER.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Tuan/STM32CubeIDE/workspace_1.11.2/ROTARY_ENCODER/Lib" -I"C:/Users/Tuan/STM32CubeIDE/workspace_1.11.2/ROTARY_ENCODER/Lib" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/ROTARY_ENCODER.d ./Lib/ROTARY_ENCODER.o ./Lib/ROTARY_ENCODER.su

.PHONY: clean-Lib


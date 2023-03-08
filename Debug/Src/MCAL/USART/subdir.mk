################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/USART/USART_program.c 

OBJS += \
./Src/MCAL/USART/USART_program.o 

C_DEPS += \
./Src/MCAL/USART/USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/USART/%.o Src/MCAL/USART/%.su: ../Src/MCAL/USART/%.c Src/MCAL/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-USART

clean-Src-2f-MCAL-2f-USART:
	-$(RM) ./Src/MCAL/USART/USART_program.d ./Src/MCAL/USART/USART_program.o ./Src/MCAL/USART/USART_program.su

.PHONY: clean-Src-2f-MCAL-2f-USART


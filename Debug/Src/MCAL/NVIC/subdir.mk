################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/NVIC/NVIC_program.c 

OBJS += \
./Src/MCAL/NVIC/NVIC_program.o 

C_DEPS += \
./Src/MCAL/NVIC/NVIC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/NVIC/%.o Src/MCAL/NVIC/%.su: ../Src/MCAL/NVIC/%.c Src/MCAL/NVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-NVIC

clean-Src-2f-MCAL-2f-NVIC:
	-$(RM) ./Src/MCAL/NVIC/NVIC_program.d ./Src/MCAL/NVIC/NVIC_program.o ./Src/MCAL/NVIC/NVIC_program.su

.PHONY: clean-Src-2f-MCAL-2f-NVIC


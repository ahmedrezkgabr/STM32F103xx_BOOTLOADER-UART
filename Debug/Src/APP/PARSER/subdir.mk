################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/PARSER/parser.c 

OBJS += \
./Src/APP/PARSER/parser.o 

C_DEPS += \
./Src/APP/PARSER/parser.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/PARSER/%.o Src/APP/PARSER/%.su: ../Src/APP/PARSER/%.c Src/APP/PARSER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-PARSER

clean-Src-2f-APP-2f-PARSER:
	-$(RM) ./Src/APP/PARSER/parser.d ./Src/APP/PARSER/parser.o ./Src/APP/PARSER/parser.su

.PHONY: clean-Src-2f-APP-2f-PARSER


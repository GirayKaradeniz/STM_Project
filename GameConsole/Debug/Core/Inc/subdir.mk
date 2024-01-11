################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Notmain.c \
../Core/Inc/buzzerDriver.c \
../Core/Inc/frameBuffer.c \
../Core/Inc/game.c \
../Core/Inc/oled.c 

OBJS += \
./Core/Inc/Notmain.o \
./Core/Inc/buzzerDriver.o \
./Core/Inc/frameBuffer.o \
./Core/Inc/game.o \
./Core/Inc/oled.o 

C_DEPS += \
./Core/Inc/Notmain.d \
./Core/Inc/buzzerDriver.d \
./Core/Inc/frameBuffer.d \
./Core/Inc/game.d \
./Core/Inc/oled.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su Core/Inc/%.cyclo: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/Notmain.cyclo ./Core/Inc/Notmain.d ./Core/Inc/Notmain.o ./Core/Inc/Notmain.su ./Core/Inc/buzzerDriver.cyclo ./Core/Inc/buzzerDriver.d ./Core/Inc/buzzerDriver.o ./Core/Inc/buzzerDriver.su ./Core/Inc/frameBuffer.cyclo ./Core/Inc/frameBuffer.d ./Core/Inc/frameBuffer.o ./Core/Inc/frameBuffer.su ./Core/Inc/game.cyclo ./Core/Inc/game.d ./Core/Inc/game.o ./Core/Inc/game.su ./Core/Inc/oled.cyclo ./Core/Inc/oled.d ./Core/Inc/oled.o ./Core/Inc/oled.su

.PHONY: clean-Core-2f-Inc


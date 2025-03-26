################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bldc.c \
../Core/Src/bluetooth.c \
../Core/Src/bmi08a.c \
../Core/Src/bmi08g.c \
../Core/Src/bmi08iface.c \
../Core/Src/bmi08xa.c \
../Core/Src/dwt_delay.c \
../Core/Src/leds.c \
../Core/Src/main.c \
../Core/Src/main_user.c \
../Core/Src/read_sensor_data.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/uart.c 

OBJS += \
./Core/Src/bldc.o \
./Core/Src/bluetooth.o \
./Core/Src/bmi08a.o \
./Core/Src/bmi08g.o \
./Core/Src/bmi08iface.o \
./Core/Src/bmi08xa.o \
./Core/Src/dwt_delay.o \
./Core/Src/leds.o \
./Core/Src/main.o \
./Core/Src/main_user.o \
./Core/Src/read_sensor_data.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/uart.o 

C_DEPS += \
./Core/Src/bldc.d \
./Core/Src/bluetooth.d \
./Core/Src/bmi08a.d \
./Core/Src/bmi08g.d \
./Core/Src/bmi08iface.d \
./Core/Src/bmi08xa.d \
./Core/Src/dwt_delay.d \
./Core/Src/leds.d \
./Core/Src/main.d \
./Core/Src/main_user.d \
./Core/Src/read_sensor_data.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bldc.cyclo ./Core/Src/bldc.d ./Core/Src/bldc.o ./Core/Src/bldc.su ./Core/Src/bluetooth.cyclo ./Core/Src/bluetooth.d ./Core/Src/bluetooth.o ./Core/Src/bluetooth.su ./Core/Src/bmi08a.cyclo ./Core/Src/bmi08a.d ./Core/Src/bmi08a.o ./Core/Src/bmi08a.su ./Core/Src/bmi08g.cyclo ./Core/Src/bmi08g.d ./Core/Src/bmi08g.o ./Core/Src/bmi08g.su ./Core/Src/bmi08iface.cyclo ./Core/Src/bmi08iface.d ./Core/Src/bmi08iface.o ./Core/Src/bmi08iface.su ./Core/Src/bmi08xa.cyclo ./Core/Src/bmi08xa.d ./Core/Src/bmi08xa.o ./Core/Src/bmi08xa.su ./Core/Src/dwt_delay.cyclo ./Core/Src/dwt_delay.d ./Core/Src/dwt_delay.o ./Core/Src/dwt_delay.su ./Core/Src/leds.cyclo ./Core/Src/leds.d ./Core/Src/leds.o ./Core/Src/leds.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/main_user.cyclo ./Core/Src/main_user.d ./Core/Src/main_user.o ./Core/Src/main_user.su ./Core/Src/read_sensor_data.cyclo ./Core/Src/read_sensor_data.d ./Core/Src/read_sensor_data.o ./Core/Src/read_sensor_data.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su ./Core/Src/uart.cyclo ./Core/Src/uart.d ./Core/Src/uart.o ./Core/Src/uart.su

.PHONY: clean-Core-2f-Src


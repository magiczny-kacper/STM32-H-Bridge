################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.o: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I"/media/magiczny_kacper/Data/Pulpit 13.07.20/Mikrokontrolery/STM32/Cube IDE/Mostek H/Drivers/CMSIS/DSP/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


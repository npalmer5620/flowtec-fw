################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/%.o Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/%.su Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/%.cyclo: ../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-CMSIS-2f-DSP-2f-Source-2f-ControllerFunctions

clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-CMSIS-2f-DSP-2f-Source-2f-ControllerFunctions:
	-$(RM) ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-CMSIS-2f-DSP-2f-Source-2f-ControllerFunctions


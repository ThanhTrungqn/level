################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TouchGFX/App/app_touchgfx.c 

OBJS += \
./TouchGFX/App/app_touchgfx.o 

C_DEPS += \
./TouchGFX/App/app_touchgfx.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/App/app_touchgfx.o: ../TouchGFX/App/app_touchgfx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../TouchGFX/gui/include -I../TouchGFX/generated/fonts/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"C:/Users/tnguyen/STM32CubeIDE/workspace_1.1.0/Level_Lampe/Drivers/BSP/Components/st7789h2" -I../TouchGFX/generated/texts/include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../TouchGFX/generated/images/include -I../Middlewares/ST/touchgfx/framework/include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../TouchGFX/target/generated -I"C:/Users/tnguyen/STM32CubeIDE/workspace_1.1.0/Level_Lampe/Drivers/BSP/Components/Common" -I../Drivers/CMSIS/Include -I../Core/Inc -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/App -I../TouchGFX/target -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TouchGFX/App/app_touchgfx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


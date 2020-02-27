################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.cpp 

OBJS += \
./TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.o 

CPP_DEPS += \
./TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.o: ../TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../TouchGFX/gui/include -I../TouchGFX/generated/fonts/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../TouchGFX/generated/texts/include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../TouchGFX/generated/images/include -I../Middlewares/ST/touchgfx/framework/include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../TouchGFX/target/generated -I../Drivers/CMSIS/Include -I../Core/Inc -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/App -I../TouchGFX/target -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


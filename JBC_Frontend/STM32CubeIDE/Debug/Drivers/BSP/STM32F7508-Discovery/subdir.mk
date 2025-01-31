################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/TouchGFXProjects/JBC_Frontend/Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.c \
C:/TouchGFXProjects/JBC_Frontend/Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.c \
C:/TouchGFXProjects/JBC_Frontend/Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.c 

C_DEPS += \
./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.d \
./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.d \
./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.d 

OBJS += \
./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.o \
./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.o \
./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.o: C:/TouchGFXProjects/JBC_Frontend/Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.c Drivers/BSP/STM32F7508-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DSTM32F750xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32F7508-Discovery -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.o: C:/TouchGFXProjects/JBC_Frontend/Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.c Drivers/BSP/STM32F7508-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DSTM32F750xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32F7508-Discovery -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.o: C:/TouchGFXProjects/JBC_Frontend/Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.c Drivers/BSP/STM32F7508-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DSTM32F750xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32F7508-Discovery -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32F7508-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32F7508-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.cyclo ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.d ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.o ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery.su ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.cyclo ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.d ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.o ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_sdram.su ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.cyclo ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.d ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.o ./Drivers/BSP/STM32F7508-Discovery/stm32f7508_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32F7508-2d-Discovery


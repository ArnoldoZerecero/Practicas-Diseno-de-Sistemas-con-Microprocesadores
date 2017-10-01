################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ButtonDriver.c" \
"../Sources/DisplayDriver.c" \
"../Sources/LedDriver.c" \
"../Sources/MISCELANEO.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ButtonDriver.c \
../Sources/DisplayDriver.c \
../Sources/LedDriver.c \
../Sources/MISCELANEO.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ButtonDriver.o \
./Sources/DisplayDriver.o \
./Sources/LedDriver.o \
./Sources/MISCELANEO.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ButtonDriver.d \
./Sources/DisplayDriver.d \
./Sources/LedDriver.d \
./Sources/MISCELANEO.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ButtonDriver.o" \
"./Sources/DisplayDriver.o" \
"./Sources/LedDriver.o" \
"./Sources/MISCELANEO.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ButtonDriver.d" \
"./Sources/DisplayDriver.d" \
"./Sources/LedDriver.d" \
"./Sources/MISCELANEO.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ButtonDriver.o \
./Sources/DisplayDriver.o \
./Sources/LedDriver.o \
./Sources/MISCELANEO.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ButtonDriver.o: ../Sources/ButtonDriver.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ButtonDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ButtonDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/DisplayDriver.o: ../Sources/DisplayDriver.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/DisplayDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/DisplayDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LedDriver.o: ../Sources/LedDriver.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LedDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LedDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MISCELANEO.o: ../Sources/MISCELANEO.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/MISCELANEO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/MISCELANEO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '



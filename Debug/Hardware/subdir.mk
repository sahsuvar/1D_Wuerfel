################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Hardware/CADC.cpp \
../Hardware/CBBBHardware.cpp \
../Hardware/CBrake.cpp \
../Hardware/CMPU6050.cpp \
../Hardware/CMotor.cpp 

OBJS += \
./Hardware/CADC.o \
./Hardware/CBBBHardware.o \
./Hardware/CBrake.o \
./Hardware/CMPU6050.o \
./Hardware/CMotor.o 

CPP_DEPS += \
./Hardware/CADC.d \
./Hardware/CBBBHardware.d \
./Hardware/CBrake.d \
./Hardware/CMPU6050.d \
./Hardware/CMotor.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/vmuser/workspace/1D_Wuerfel" -I"/home/vmuser/workspace/1D_Wuerfel/Hardware" -I"/home/vmuser/workspace/1D_Wuerfel/socket" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



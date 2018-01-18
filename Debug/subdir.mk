################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AComponentBase.cpp \
../Assertion.cpp \
../CBinarySemaphore.cpp \
../CCommComp.cpp \
../CContainer.cpp \
../CControlComp.cpp \
../CMutex.cpp \
../CThread.cpp \
../main.cpp 

OBJS += \
./AComponentBase.o \
./Assertion.o \
./CBinarySemaphore.o \
./CCommComp.o \
./CContainer.o \
./CControlComp.o \
./CMutex.o \
./CThread.o \
./main.o 

CPP_DEPS += \
./AComponentBase.d \
./Assertion.d \
./CBinarySemaphore.d \
./CCommComp.d \
./CContainer.d \
./CControlComp.d \
./CMutex.d \
./CThread.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/vmuser/workspace/1D_Wuerfel" -I"/home/vmuser/workspace/1D_Wuerfel/Hardware" -I"/home/vmuser/workspace/1D_Wuerfel/socket" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



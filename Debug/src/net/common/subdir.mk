################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/common/NetworkEvent.cpp \
../src/net/common/NetworkEventManager.cpp \
../src/net/common/NetworkEventReceiver.cpp \
../src/net/common/NetworkManager.cpp \
../src/net/common/NetworkMessage.cpp \
../src/net/common/NetworkMessageOut.cpp 

OBJS += \
./src/net/common/NetworkEvent.o \
./src/net/common/NetworkEventManager.o \
./src/net/common/NetworkEventReceiver.o \
./src/net/common/NetworkManager.o \
./src/net/common/NetworkMessage.o \
./src/net/common/NetworkMessageOut.o 

CPP_DEPS += \
./src/net/common/NetworkEvent.d \
./src/net/common/NetworkEventManager.d \
./src/net/common/NetworkEventReceiver.d \
./src/net/common/NetworkManager.d \
./src/net/common/NetworkMessage.d \
./src/net/common/NetworkMessageOut.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/common/%.o: ../src/net/common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



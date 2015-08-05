################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/TestTCPClient.cpp \
../src/net/TestTCPLoginClient.cpp \
../src/net/TestTCPServer.cpp \
../src/net/TestTcp.cpp 

OBJS += \
./src/net/TestTCPClient.o \
./src/net/TestTCPLoginClient.o \
./src/net/TestTCPServer.o \
./src/net/TestTcp.o 

CPP_DEPS += \
./src/net/TestTCPClient.d \
./src/net/TestTCPLoginClient.d \
./src/net/TestTCPServer.d \
./src/net/TestTcp.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/%.o: ../src/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



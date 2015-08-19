################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/tests/TestTCPClient.cpp \
../src/net/tests/TestTCPLoginClient.cpp \
../src/net/tests/TestTCPServer.cpp \
../src/net/tests/TestTcp.cpp 

OBJS += \
./src/net/tests/TestTCPClient.o \
./src/net/tests/TestTCPLoginClient.o \
./src/net/tests/TestTCPServer.o \
./src/net/tests/TestTcp.o 

CPP_DEPS += \
./src/net/tests/TestTCPClient.d \
./src/net/tests/TestTCPLoginClient.d \
./src/net/tests/TestTCPServer.d \
./src/net/tests/TestTcp.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/tests/%.o: ../src/net/tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/third" -I../src/ -I../src/tools -I../src/third/ -I../src/third/SimpleJSON -I../src/third/SimpleJSON/src -I../src/net/ -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



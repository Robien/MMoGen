################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/tcp/client/ClientConnectAndPrint.cpp 

OBJS += \
./src/net/tcp/client/ClientConnectAndPrint.o 

CPP_DEPS += \
./src/net/tcp/client/ClientConnectAndPrint.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/tcp/client/%.o: ../src/net/tcp/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



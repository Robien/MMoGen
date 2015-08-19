################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/web/WebServer.cpp 

OBJS += \
./src/net/web/WebServer.o 

CPP_DEPS += \
./src/net/web/WebServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/web/%.o: ../src/net/web/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/third" -I../src/ -I../src/tools -I../src/third/ -I../src/third/SimpleJSON -I../src/third/SimpleJSON/src -I../src/net/ -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



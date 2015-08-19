################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../third/SimpleJSON/src/JSON.cpp \
../third/SimpleJSON/src/JSONValue.cpp 

OBJS += \
./third/SimpleJSON/src/JSON.o \
./third/SimpleJSON/src/JSONValue.o 

CPP_DEPS += \
./third/SimpleJSON/src/JSON.d \
./third/SimpleJSON/src/JSONValue.d 


# Each subdirectory must supply rules for building sources it contributes
third/SimpleJSON/src/%.o: ../third/SimpleJSON/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -I../third/ -I../third/SimpleJSON -I../third/SimpleJSON/src -I../src/net/ -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



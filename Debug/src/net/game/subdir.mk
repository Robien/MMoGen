################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/game/Client.cpp \
../src/net/game/LoginServer.cpp 

OBJS += \
./src/net/game/Client.o \
./src/net/game/LoginServer.o 

CPP_DEPS += \
./src/net/game/Client.d \
./src/net/game/LoginServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/game/%.o: ../src/net/game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -I../third/ -I../third/SimpleJSON -I../third/SimpleJSON/src -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



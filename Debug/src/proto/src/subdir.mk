################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/proto/src/Connection.pb.cc \
../src/proto/src/Game.pb.cc 

OBJS += \
./src/proto/src/Connection.pb.o \
./src/proto/src/Game.pb.o 

CC_DEPS += \
./src/proto/src/Connection.pb.d \
./src/proto/src/Game.pb.d 


# Each subdirectory must supply rules for building sources it contributes
src/proto/src/%.o: ../src/proto/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -I../third/ -I../third/SimpleJSON -I../third/SimpleJSON/src -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



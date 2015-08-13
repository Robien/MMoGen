################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/data/BufferToFd.cpp \
../src/tools/data/DataLen.cpp \
../src/tools/data/IBuffer.cpp \
../src/tools/data/SynchonizedBuffer.cpp \
../src/tools/data/Trash.cpp 

OBJS += \
./src/tools/data/BufferToFd.o \
./src/tools/data/DataLen.o \
./src/tools/data/IBuffer.o \
./src/tools/data/SynchonizedBuffer.o \
./src/tools/data/Trash.o 

CPP_DEPS += \
./src/tools/data/BufferToFd.d \
./src/tools/data/DataLen.d \
./src/tools/data/IBuffer.d \
./src/tools/data/SynchonizedBuffer.d \
./src/tools/data/Trash.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/data/%.o: ../src/tools/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -I../third/ -I../third/SimpleJSON -I../third/SimpleJSON/src -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



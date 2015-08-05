################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/thread/MutexAuto.cpp \
../src/tools/thread/StoppableThread.cpp \
../src/tools/thread/Thread.cpp 

OBJS += \
./src/tools/thread/MutexAuto.o \
./src/tools/thread/StoppableThread.o \
./src/tools/thread/Thread.o 

CPP_DEPS += \
./src/tools/thread/MutexAuto.d \
./src/tools/thread/StoppableThread.d \
./src/tools/thread/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/thread/%.o: ../src/tools/thread/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



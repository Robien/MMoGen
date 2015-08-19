################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/time/FormattedDate.cpp \
../src/tools/time/Timer.cpp \
../src/tools/time/TimerCaller.cpp 

OBJS += \
./src/tools/time/FormattedDate.o \
./src/tools/time/Timer.o \
./src/tools/time/TimerCaller.o 

CPP_DEPS += \
./src/tools/time/FormattedDate.d \
./src/tools/time/Timer.d \
./src/tools/time/TimerCaller.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/time/%.o: ../src/tools/time/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/third" -I../src/ -I../src/tools -I../src/third/ -I../src/third/SimpleJSON -I../src/third/SimpleJSON/src -I../src/net/ -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



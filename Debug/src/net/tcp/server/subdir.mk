################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/tcp/server/ServerClientManager.cpp \
../src/net/tcp/server/ServerConnexionHandler.cpp \
../src/net/tcp/server/ServerListener.cpp \
../src/net/tcp/server/TCPServer.cpp 

OBJS += \
./src/net/tcp/server/ServerClientManager.o \
./src/net/tcp/server/ServerConnexionHandler.o \
./src/net/tcp/server/ServerListener.o \
./src/net/tcp/server/TCPServer.o 

CPP_DEPS += \
./src/net/tcp/server/ServerClientManager.d \
./src/net/tcp/server/ServerConnexionHandler.d \
./src/net/tcp/server/ServerListener.d \
./src/net/tcp/server/TCPServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/tcp/server/%.o: ../src/net/tcp/server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -I"/home/rguyard/workspace/MMOGen/src/tools" -I"/home/rguyard/workspace/MMOGen/src" -I../src/ -I../src/tools -O2 -march=native -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/tools/time/subdir.mk
-include src/tools/thread/subdir.mk
-include src/tools/random/subdir.mk
-include src/tools/data/subdir.mk
-include src/tools/subdir.mk
-include src/third/SimpleJSON/src/subdir.mk
-include src/proto/src/subdir.mk
-include src/net/web/subdir.mk
-include src/net/tests/subdir.mk
-include src/net/tcp/server/subdir.mk
-include src/net/tcp/client/subdir.mk
-include src/net/game/subdir.mk
-include src/net/common/subdir.mk
-include src/net/Unity/subdir.mk
-include src/common/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MMOGen

# Tool invocations
MMOGen: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -o "MMOGen" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) MMOGen
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

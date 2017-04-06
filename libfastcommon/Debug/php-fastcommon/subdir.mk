################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../php-fastcommon/fastcommon.c 

OBJS += \
./php-fastcommon/fastcommon.o 

C_DEPS += \
./php-fastcommon/fastcommon.d 


# Each subdirectory must supply rules for building sources it contributes
php-fastcommon/%.o: ../php-fastcommon/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/root/workspace/libfastcommon/src -I/root/workspace/libfastcommon/php-fastcommon -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



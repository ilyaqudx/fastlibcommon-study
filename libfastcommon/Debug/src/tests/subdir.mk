################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tests/test_allocator.c \
../src/tests/test_blocked_queue.c \
../src/tests/test_char_convert.c \
../src/tests/test_char_convert_loader.c \
../src/tests/test_id_generator.c \
../src/tests/test_ini_parser.c \
../src/tests/test_logger.c \
../src/tests/test_mblock.c \
../src/tests/test_multi_skiplist.c \
../src/tests/test_skiplist.c 

OBJS += \
./src/tests/test_allocator.o \
./src/tests/test_blocked_queue.o \
./src/tests/test_char_convert.o \
./src/tests/test_char_convert_loader.o \
./src/tests/test_id_generator.o \
./src/tests/test_ini_parser.o \
./src/tests/test_logger.o \
./src/tests/test_mblock.o \
./src/tests/test_multi_skiplist.o \
./src/tests/test_skiplist.o 

C_DEPS += \
./src/tests/test_allocator.d \
./src/tests/test_blocked_queue.d \
./src/tests/test_char_convert.d \
./src/tests/test_char_convert_loader.d \
./src/tests/test_id_generator.d \
./src/tests/test_ini_parser.d \
./src/tests/test_logger.d \
./src/tests/test_mblock.d \
./src/tests/test_multi_skiplist.d \
./src/tests/test_skiplist.d 


# Each subdirectory must supply rules for building sources it contributes
src/tests/%.o: ../src/tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/root/workspace/libfastcommon/src -I/root/workspace/libfastcommon/php-fastcommon -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/avl_tree.o \
../src/base64.o \
../src/chain.o \
../src/char_convert_loader.o \
../src/char_converter.o \
../src/connection_pool.o \
../src/fast_allocator.o \
../src/fast_blocked_queue.o \
../src/fast_buffer.o \
../src/fast_mblock.o \
../src/fast_mpool.o \
../src/fast_task_queue.o \
../src/fast_timer.o \
../src/flat_skiplist.o \
../src/hash.o \
../src/http_func.o \
../src/id_generator.o \
../src/ini_file_reader.o \
../src/ioevent.o \
../src/ioevent_loop.o \
../src/local_ip_func.o \
../src/logger.o \
../src/md5.o \
../src/multi_skiplist.o \
../src/process_ctrl.o \
../src/pthread_func.o \
../src/sched_thread.o \
../src/shared_func.o \
../src/sockopt.o \
../src/system_info.o 

C_SRCS += \
../src/avl_tree.c \
../src/base64.c \
../src/chain.c \
../src/char_convert_loader.c \
../src/char_converter.c \
../src/connection_pool.c \
../src/fast_allocator.c \
../src/fast_blocked_queue.c \
../src/fast_buffer.c \
../src/fast_mblock.c \
../src/fast_mpool.c \
../src/fast_task_queue.c \
../src/fast_timer.c \
../src/flat_skiplist.c \
../src/hash.c \
../src/http_func.c \
../src/id_generator.c \
../src/ini_file_reader.c \
../src/io_opt.c \
../src/ioevent.c \
../src/ioevent_loop.c \
../src/local_ip_func.c \
../src/logger.c \
../src/md5.c \
../src/multi_skiplist.c \
../src/process_ctrl.c \
../src/pthread_func.c \
../src/pthread_pool.c \
../src/sched_thread.c \
../src/shared_func.c \
../src/sockopt.c \
../src/system_info.c 

OBJS += \
./src/avl_tree.o \
./src/base64.o \
./src/chain.o \
./src/char_convert_loader.o \
./src/char_converter.o \
./src/connection_pool.o \
./src/fast_allocator.o \
./src/fast_blocked_queue.o \
./src/fast_buffer.o \
./src/fast_mblock.o \
./src/fast_mpool.o \
./src/fast_task_queue.o \
./src/fast_timer.o \
./src/flat_skiplist.o \
./src/hash.o \
./src/http_func.o \
./src/id_generator.o \
./src/ini_file_reader.o \
./src/io_opt.o \
./src/ioevent.o \
./src/ioevent_loop.o \
./src/local_ip_func.o \
./src/logger.o \
./src/md5.o \
./src/multi_skiplist.o \
./src/process_ctrl.o \
./src/pthread_func.o \
./src/pthread_pool.o \
./src/sched_thread.o \
./src/shared_func.o \
./src/sockopt.o \
./src/system_info.o 

C_DEPS += \
./src/avl_tree.d \
./src/base64.d \
./src/chain.d \
./src/char_convert_loader.d \
./src/char_converter.d \
./src/connection_pool.d \
./src/fast_allocator.d \
./src/fast_blocked_queue.d \
./src/fast_buffer.d \
./src/fast_mblock.d \
./src/fast_mpool.d \
./src/fast_task_queue.d \
./src/fast_timer.d \
./src/flat_skiplist.d \
./src/hash.d \
./src/http_func.d \
./src/id_generator.d \
./src/ini_file_reader.d \
./src/io_opt.d \
./src/ioevent.d \
./src/ioevent_loop.d \
./src/local_ip_func.d \
./src/logger.d \
./src/md5.d \
./src/multi_skiplist.d \
./src/process_ctrl.d \
./src/pthread_func.d \
./src/pthread_pool.d \
./src/sched_thread.d \
./src/shared_func.d \
./src/sockopt.d \
./src/system_info.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/root/workspace/libfastcommon/src -I/root/workspace/libfastcommon/php-fastcommon -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



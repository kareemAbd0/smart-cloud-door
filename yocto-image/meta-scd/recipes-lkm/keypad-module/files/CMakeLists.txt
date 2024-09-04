cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project("keypad_4x3_Pdriver" VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Set the headers path directly


#execute_process(
#       COMMAND uname -r
#       OUTPUT_VARIABLE KERNEL_VERSION
#       OUTPUT_STRIP_TRAILING_WHITESPACE
#)


set(KERNELHEADERS_DIR "/mnt/yocto/kernel-source/include")


#ddd
message("Kernel headers: ${KERNELHEADERS_DIR}")


message("Kernel headers: ${KERNELHEADERS_DIR}")

# find MODULE_LICENSE("GPL"), MODULE_AUTHOR() etc.
# thanks to "merseyviking" from stack overflow
add_definitions(-D__KERNEL__ -DMODULE)

# this is needed in order for CLion IDE to provide syntax highlighting
# this is independent from the actual kernel object that is built
add_executable(dummy
        keypad_platform_driver.c
        keypad_platform_driver_data.h
        keypad.c
        keypad.h
        # add all *.h and *.c files here that # CLion should cover

)

# CLion IDE will find symbols from <linux/*>
target_include_directories("dummy" PRIVATE ${KERNELHEADERS_DIR})

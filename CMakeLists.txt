# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "<PICO_SDK_HERE>")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(DemoPicoHC06BT C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(DemoPicoHC06BT DemoPicoHC06BT.c )

pico_set_program_name(DemoPicoHC06BT "DemoPicoHC06BT")
pico_set_program_version(DemoPicoHC06BT "0.1")

pico_enable_stdio_uart(DemoPicoHC06BT 1)
pico_enable_stdio_usb(DemoPicoHC06BT 1)

# Add the standard library to the build
target_link_libraries(DemoPicoHC06BT pico_stdlib hardware_uart hardware_irq)

pico_add_extra_outputs(DemoPicoHC06BT)


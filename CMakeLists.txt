cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME tufty-3d) # <-- Name your project/executable here!

include(pimoroni_pico_import.cmake)
include(pico_sdk_import.cmake)

set(PICO_BOARD pimoroni_tufty2040)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add your source files
add_executable(${NAME}
    tufty-3d.cpp # <-- Add source files here!
)

pico_set_program_name(${NAME} "tufty-3d")
pico_set_program_version(${NAME} "0.1")

pico_enable_stdio_uart(${NAME} 0)
pico_enable_stdio_usb(${NAME} 1)

# Include required libraries
# This assumes `pimoroni-pico` is stored alongside your project
include(libraries/tufty2040/tufty2040)
include(drivers/st7789/st7789)
include(libraries/pico_graphics/pico_graphics)
include(drivers/button/button)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(common/pimoroni_bus)

# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
    pico_stdlib
    tufty2040 # <-- List libraries here!
    st7789
    hardware_spi
    pico_graphics
    button
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)

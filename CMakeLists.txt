cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(pico_bug C CXX ASM)

set(PICO_BOARD pico_w)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

#add_subdirectory(pico_w)

add_compile_options(
  -Wall
  -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
  -Wno-unused-function # we have some for the docs that aren't called
  -Wno-maybe-uninitialized
  -O3
  -g
)

add_executable(bug bug.c)

pico_enable_stdio_usb(bug 1) # Enable USB output
pico_enable_stdio_uart(bug 0) # Disable UART output
pico_add_extra_outputs(bug) # Generate map/bin/hex/uf2

target_include_directories(bug
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(bug
  hardware_adc
  pico_cyw43_arch_lwip_threadsafe_background
  pico_multicore
  pico_stdlib
)

target_link_options(bug
    PRIVATE "LINKER:--print-memory-usage"
    #PRIVATE "LINKER:--verbose"
)

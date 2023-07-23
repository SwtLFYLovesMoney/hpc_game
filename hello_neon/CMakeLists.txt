cmake_minimum_required(VERSION 3.1.0)

set(proj_name hello_neon)

project(${proj_name})

set(EXECUTABLE_OUTPUT_PATH ${TOP_DIR}/output)

set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")

# neon extension
add_definitions(-mfpu=neon-vfpv4)

add_executable(${proj_name} main.cpp)

# install(TARGETS hello_neon DESTINATION ${TOP_DIR}/output/)

# arm-linux-gnueabihf-g++ ../main.cpp -mfpu=neon-vfpv4 -O2 -o main
# qemu-arm-static -L /usr/arm-linux-gnueabihf/ ./hello_neon
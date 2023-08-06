cmake_minimum_required(VERSION 3.1.0)

set(proj_name hello_neon)

project(${proj_name})

set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")
# neon extension
add_definitions(-mfpu=neon-vfpv4)

add_executable(${proj_name} main.cpp)
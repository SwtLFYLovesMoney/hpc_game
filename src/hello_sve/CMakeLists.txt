cmake_minimum_required(VERSION 3.1.0)

set(proj_name hello_sve)

project(${proj_name})

set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")
# sve extension
add_definitions(-march=armv8-a+sve)

add_executable(${proj_name} main.cpp)
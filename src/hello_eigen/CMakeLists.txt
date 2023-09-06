cmake_minimum_required(VERSION 3.1.0)

set(proj_name hello_eigen)
project(${proj_name})

# compiler option
set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")

include_directories(PUBLIC ${TOP_DIR}/include/eigen/)

file(GLOB_RECURSE SRC_CODE ./*.cpp)

add_executable(${proj_name} ${SRC_CODE})
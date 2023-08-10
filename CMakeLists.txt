cmake_minimum_required(VERSION 3.1.0)

include(config.cmake)
project(hpc_game)

include_directories(SYSTEM ${TOP_DIR}/include/eigen/)

# add_subdirectory(${TOP_DIR}/src/hello_sve)
add_subdirectory(${TOP_DIR}/src/hello_neon)
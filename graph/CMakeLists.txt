cmake_minimum_required(VERSION 3.10)
project(graph LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(
    data_structure/include
    algorithms/include
    
)

# Gather all source files
file(GLOB DS_SRC data_structure/src/*.cpp)
file(GLOB ALGO_SRC algorithms/src/*.cpp)

add_executable(graph main.cpp ${DS_SRC} ${ALGO_SRC})
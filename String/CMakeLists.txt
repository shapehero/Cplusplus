cmake_minimum_required(VERSION 3.5)
project(String)

set(CMAKE_CXX_STANDARD 11)
add_definitions("-Wall -g")

set(SOURCE_FILES String.cpp)
add_executable(run ${SOURCE_FILES})

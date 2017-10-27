cmake_minimum_required(VERSION 3.8)
project(sortingNetwork)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/bsort.cpp)

add_executable(sortingNetwork ${SOURCE_FILES})
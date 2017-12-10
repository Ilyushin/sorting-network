cmake_minimum_required(VERSION 3.8)
project(testHeapSort)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(lib/googletest)

include_directories(
        include
        lib/googletest/googletest/include
)

set(SOURCE_FILES
        ../../include/heapSort.h
        ../../src/heapSort.cpp
        testHeapSort.cpp
        )

add_executable(. ${SOURCE_FILES})
target_link_libraries(. gtest)
add_test(testHeapSort testHeapSort.cpp)
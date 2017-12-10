cmake_minimum_required(VERSION 3.8)
project(.)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(lib/googletest)

include_directories(
        include
        lib/googletest/googletest/include
)

set(SOURCE_FILES
        src/bsort.cpp
        include/permutation.h
        include/sortingNetwork.h
        src/sortingNetwork.cpp
        tests/TestSortingNetwork.cpp
        )

add_executable(. ${SOURCE_FILES})
target_link_libraries(. gtest)
add_test( TestSortingNetwork testSortingNetwork.cpp)
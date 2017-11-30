cmake_minimum_required(VERSION 3.8)
project(sortingNetwork)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(
        lib/googletest
        tests
)

include_directories(
        include
        lib/googletest/googletest/include
)

set(SOURCE_FILES
        include/bsort.h
        src/bsort.cpp
        include/permutation.h
        src/permutation.cpp
        include/sortingNetwork.h
        src/sortingNetwork.cpp
        src/main.cpp src/Point.cpp include/Point.h)

add_executable(sortingNetwork ${SOURCE_FILES})
target_link_libraries(sortingNetwork gtest)
add_test(sortingNetwork sortingNetwork)
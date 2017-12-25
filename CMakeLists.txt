cmake_minimum_required(VERSION 3.8)
project(sortingNetwork)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(
        lib/googletest
        tests
)

set(CMAKE_C_COMPILER /usr/local/bin/mpicc)
set(CMAKE_CXX_COMPILER /usr/local/bin/mpic++)

include_directories(
        include
        lib/googletest/googletest/include
)

set(SOURCE_FILES
        src/bsort.h
        src/bsort.cpp
        src/permutation.h
        src/permutation.cpp
        src/sortingNetwork.h
        src/sortingNetwork.cpp
        src/main.cpp
        src/point.h
        src/point.cpp
        src/heapSort.cpp
        src/heapSort.h
        src/quickSort.cpp
        src/quickSort.h
        src/mergeSort.cpp
        src/mergeSort.h
        src/point.cpp)

add_executable(sortingNetwork ${SOURCE_FILES})
target_link_libraries(sortingNetwork gtest)
add_test(sortingNetwork sortingNetwork)
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
        include/bsort.h
        src/bsort.cpp
        include/permutation.h
        src/permutation.cpp
        include/sortingNetwork.h
        src/sortingNetwork.cpp
        src/main.cpp
        include/point.h src/point.cpp src/heapSort.cpp include/heapSort.h src/quickSort.cpp include/quickSort.h src/mergeSort.cpp include/mergeSort.h)

add_executable(sortingNetwork ${SOURCE_FILES})
target_link_libraries(sortingNetwork gtest)
add_test(sortingNetwork sortingNetwork)
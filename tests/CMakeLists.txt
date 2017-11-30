cmake_minimum_required(VERSION 3.8)
project(sortingNetwork)

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
        src/main.cpp
        )

add_executable(sortingNetwork ${SOURCE_FILES})
target_link_libraries(sortingNetwork gtest)
add_test( SortingNetwork ./TestSortingNetwork.cpp )
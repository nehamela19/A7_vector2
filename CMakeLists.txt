cmake_minimum_required(VERSION 3.16)

project(A7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(tests)

add_executable(my_test
    tests/test_vector_1.cpp
    tests/test_vector_2.cpp
    tests/test_matrix.cpp
)
cmake_minimum_required(VERSION 2.8)
project(Fraction CXX C)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 ${LLVM_CXX_FLAGS} ")

include_directories(${CMAKE_SOURCE_DIR}/test/)
link_directories(${CMAKE_SOURCE_DIR}/test/)

add_executable(Fraction Fraction.cpp main.cpp )
target_link_libraries(Fraction gtest gtest_main pthread)
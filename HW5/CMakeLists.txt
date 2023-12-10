cmake_minimum_required(VERSION 3.21)
project(abby_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)

find_package(Boost REQUIRED COMPONENTS graph)
include_directories(CLI11/include)

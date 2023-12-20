cmake_minimum_required(VERSION 3.27)
project(abby_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)
target_compile_options(task2 PUBLIC "-fcoroutines")
add_executable(task3 task3.cpp)
add_executable(task4 task4.cpp)
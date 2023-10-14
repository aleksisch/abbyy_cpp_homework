cmake_minimum_required(VERSION 3.27)
project(abby_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)
add_executable(task3 task3.cpp)
add_executable(task4 task4.cpp)
add_executable(task5 task5/task5.cpp)
add_executable(task6 task6.cpp)
add_executable(leetcode2 leetcode2.cpp)
#target_sources(task5
#        PUBLIC
#        FILE_SET bModule TYPE CXX_MODULES FILES
#        B.cppm
#        )
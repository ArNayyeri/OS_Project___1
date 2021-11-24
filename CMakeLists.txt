cmake_minimum_required(VERSION 3.20)
project(OS_Project___1 C)

set(CMAKE_C_STANDARD 99)

add_executable(MainProcess MainProcess.c)
add_executable(finder finder.c)
add_executable(placer placer.c)
add_executable(decoder decoder.c)
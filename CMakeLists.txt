cmake_minimum_required(VERSION 3.21)
project(C1 C)

set(CMAKE_C_STANDARD 99)

add_executable(C1 main.c input.c input.h form.c form.h)

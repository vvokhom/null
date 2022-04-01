cmake_minimum_required(VERSION 3.21)
project(report_libs)

set(CMAKE_C_STANDARD 99)

add_library(st_report report.h common_report.c st_report.c)

add_library(mt_report report.h common_report.c mt_report.c)
cmake_minimum_required(VERSION 3.21)
project(C2)

set(CMAKE_C_STANDARD 99)


include(FetchContent)
FetchContent_Declare(
                googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(data input.c input.h data.c data.h)

add_subdirectory(report)
add_executable(C2 main.c)

target_link_libraries(C2 st_report data)

add_executable(
        basic_test
        basic_test.cpp)

target_link_libraries(
        basic_test
        gtest_main
        form
)
#include(CodeCoverage)
enable_testing()
include(GoogleTest)
gtest_discover_tests(basic_test)
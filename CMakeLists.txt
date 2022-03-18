cmake_minimum_required(VERSION 3.21)
project(C1)

set(CMAKE_C_STANDARD 99)


include(FetchContent)
FetchContent_Declare(
                googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(form input.c input.h form.c form.h)
add_executable(C1 main.c)

target_link_libraries(C1 form)

add_executable(
        basic_test
        basic_test.cpp)

add_compile_options(-fprofile-arcs -ftest-coverage)
target_link_libraries(
        basic_test
        gtest_main
        form
)
enable_testing()
include(GoogleTest)
gtest_discover_tests(basic_test)

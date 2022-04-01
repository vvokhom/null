cmake_minimum_required(VERSION 3.22.1)

project(cmake_hw1)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

add_executable(main main.c)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

target_link_libraries(main pthread)

enable_testing()

add_executable(
    tests
    tests.cpp
    func.c
)
target_link_libraries(
    tests
    gtest 
    pthread
)

include(GoogleTest)
gtest_discover_tests(tests)
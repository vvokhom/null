# Задать минимальную версию CMake:
cmake_minimum_required(VERSION 3.0)

# Указать характеристики проекта:
project(null VERSION 1.0.0 LANGUAGES C CXX)

include_directories(server client boost_1_79_0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# client
add_library(client STATIC client/client.cpp)
add_executable(client.out client/main.cpp)
target_link_libraries(client.out client)

# server
add_library(server STATIC server/server.cpp)
add_executable(server.out server/main.cpp)
target_link_libraries(server.out server)
# Задать минимальную версию CMake:
cmake_minimum_required(VERSION 3.0)

# Указать характеристики проекта:
project(null VERSION 1.0.0 LANGUAGES C CXX)

include_directories(ServerClient/server ServerClient/client ServerClient/boost_1_79_0 ServerClient/)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# client
add_library(client STATIC ServerClient/client/client.cpp)
add_executable(client.out ServerClient/client/main.cpp)
target_link_libraries(client.out client)

# server
add_library(server STATIC ServerClient/server/server.cpp)
add_executable(server.out ServerClient/server/main.cpp)
target_link_libraries(server.out server)

# logic
add_subdirectory(logic)
# ui
add_subdirectory(ui)
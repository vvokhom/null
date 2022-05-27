cmake_minimum_required(VERSION 3.22)
project(logic)

set(CMAKE_CXX_STANDARD 14)

add_library(logic player.cpp player.h game.cpp game.h tile.cpp tile.h street.cpp street.h)
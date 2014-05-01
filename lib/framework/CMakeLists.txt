cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(FlakeDisplay SHARED display.cpp)
target_link_libraries(FlakeDisplay sfml-system sfml-window)

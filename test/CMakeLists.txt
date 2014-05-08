cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(test EXCLUDE_FROM_ALL tri.cpp)

target_link_libraries(test flake)
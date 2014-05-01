cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add_library(TestLibrary SHARED TestLibrary.cpp)
# target_link_libraries(TestLibrary sfml-system)

add_subdirectory(framework)

add_library(flake SHARED empty.cpp)
target_link_libraries(flake
    FlakeDisplay
    )
cmake_minimum_required(VERSION 2.8.8)

project(flake )

include_directories(include)
link_directories(lib)


add_subdirectory(lib)

add_subdirectory(test)
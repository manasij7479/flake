cmake_minimum_required(VERSION 2.8.8)


add_executable(test EXCLUDE_FROM_ALL test.cpp)

target_link_libraries(test TestLibrary)
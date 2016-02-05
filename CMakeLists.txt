project(stl_examples)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wpedantic")

add_executable(all_of src/all_of.cxx)

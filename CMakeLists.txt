cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(resources)
add_executable(projeto lib/main.cpp lib/graphviewer.cpp lib/connection.cpp)
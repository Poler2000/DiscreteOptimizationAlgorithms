cmake_minimum_required(VERSION 3.20)
project(AOD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "--pedantic -Wall -Wextra")

add_executable(L1 main.cpp src/graph/Graph.cpp include/graph/Graph.h)
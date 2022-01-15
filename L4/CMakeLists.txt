cmake_minimum_required(VERSION 3.20)
project(L4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)

include_directories(include)

add_executable(L4 src/main.cpp include/Graph.h src/Graph.cpp include/HeapPair.h src/GraphAlgorithms.cpp include/GraphAlgorithms.h include/Timer.h include/PriorityQueue.h src/PriorityQueue.cpp src/JuMPGenerator.cpp include/JuMPGenerator.h)
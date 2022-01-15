cmake_minimum_required(VERSION 3.20)
project(L3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)
#include_directories(include)


add_executable(L3 main.cpp include/Graph.h src/Graph.cpp include/GraphAlgorithms.h src/GraphAlgorithms.cpp include/HeapPair.h include/PriorityQueue.h src/PriorityQueue.cpp include/Timer.h src/GraphFileReader.cpp include/GraphFileReader.h include/Stats.h include/ShortestPath.h include/Bucket.h)
add_executable(dijkstra dijkstra_main/main.cpp include/Graph.h src/Graph.cpp include/GraphAlgorithms.h src/GraphAlgorithms.cpp include/HeapPair.h include/PriorityQueue.h src/PriorityQueue.cpp include/Timer.h src/GraphFileReader.cpp include/GraphFileReader.h include/Stats.h include/ShortestPath.h include/Bucket.h)
add_executable(dial dial_main/main.cpp include/Graph.h src/Graph.cpp include/GraphAlgorithms.h src/GraphAlgorithms.cpp include/HeapPair.h include/PriorityQueue.h src/PriorityQueue.cpp include/Timer.h src/GraphFileReader.cpp include/GraphFileReader.h include/Stats.h include/ShortestPath.h include/Bucket.h)
add_executable(radixheap radix_main/main.cpp include/Graph.h src/Graph.cpp include/GraphAlgorithms.h src/GraphAlgorithms.cpp include/HeapPair.h include/PriorityQueue.h src/PriorityQueue.cpp include/Timer.h src/GraphFileReader.cpp include/GraphFileReader.h include/Stats.h include/ShortestPath.h include/Bucket.h)

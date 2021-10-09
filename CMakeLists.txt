cmake_minimum_required(VERSION 3.20)
project(AOD)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("${PROJECT_SOURCE_DIR}/L1" "${PROJECT_SOURCE_DIR}/L1/L1_output")
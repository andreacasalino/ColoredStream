cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ColoredStream)

option(BUILD_SAMPLES "Build the samples" ON)

add_subdirectory(src)

add_subdirectory(samples)

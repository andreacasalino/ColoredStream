cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ColoredStream)


add_subdirectory(src)

option(BUILD_COLORED_STREAM_SAMPLES "Build the samples" ON)
if(BUILD_COLORED_STREAM_SAMPLES)
    add_subdirectory(samples)
endif()

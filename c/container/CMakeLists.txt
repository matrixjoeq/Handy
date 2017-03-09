cmake_minimum_required(VERSION 2.8.4)
project(c_container)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB CONTAINER_SOURCES "*.c")
add_library(c_container_static STATIC ${CONTAINER_SOURCES})
add_library(c_container_shared SHARED ${CONTAINER_SOURCES})

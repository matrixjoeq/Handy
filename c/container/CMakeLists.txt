cmake_minimum_required(VERSION 2.8.4)
project(c_container)

include("../../cmake/common.cmake")

include_parent_directories()

file(GLOB CONTAINER_SOURCES "*.c")
c_static_library(c_container_static "" ${CONTAINER_SOURCES})
c_shared_library(c_container_shared "" ${CONTAINER_SOURCES})

file(GLOB CONTAINER_TEST_SOURCES "test/*.cpp")
cxx_gtest_executable(c_container_test "c_container_static" ${CONTAINER_TEST_SOURCES})
add_test(c_container c_container_test)


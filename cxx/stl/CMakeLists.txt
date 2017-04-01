cmake_minimum_required(VERSION 2.8.4)
project(cxx_stl)

include("../../cmake/common.cmake")

include_parent_directories()

#file(GLOB STL_SOURCES "*.cpp")
#cxx_static_library(cxx_stl_static "" ${STL_SOURCES})
#cxx_shared_library(cxx_stl_shared "" ${STL_SOURCES})

file(GLOB STL_TEST_SOURCES "test/*.cpp")
#cxx_gtest_executable(cxx_stl_test "cxx_stl_static" ${STL_TEST_SOURCES})
cxx_gtest_executable(cxx_stl_test "" ${STL_TEST_SOURCES})
add_test(cxx_stl cxx_stl_test)


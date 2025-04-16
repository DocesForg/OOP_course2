cmake_minimum_required(VERSION 3.12)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Libraries build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(bst)
add_subdirectory(tree)

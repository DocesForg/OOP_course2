cmake_minimum_required(VERSION 3.22)
project(sandpile-model)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp Sand.cpp Sand.h BMP.h)

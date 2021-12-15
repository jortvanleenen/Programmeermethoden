cmake_minimum_required(VERSION 3.20)
project(PM4)

set(CMAKE_CXX_STANDARD 20)

add_executable(PM4 main.cpp koffiebord.cpp koffiebord.h stapel.cpp stapel.h)

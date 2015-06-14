cmake_minimum_required(VERSION 3.2)
project(ParseFixMsg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32 -msse4.2")

set(SOURCE_FILES main.cpp FixMsg.cpp)
add_executable(ParseFixMsg ${SOURCE_FILES})
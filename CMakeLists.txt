cmake_minimum_required(VERSION 3.2)
project(ParseFixMsg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FixItem.cpp FixMsg.cpp)
add_executable(ParseFixMsg ${SOURCE_FILES})
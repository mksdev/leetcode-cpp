cmake_minimum_required(VERSION 3.17)
project(leetcode)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(cmake/subdirlist.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(problems)
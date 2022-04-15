cmake_minimum_required(VERSION 3.16)

project(Mutex C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic ")

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Mutex)

add_subdirectory(Examples)

cmake_minimum_required(VERSION 3.16)

project(shared_mutex C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic ")

include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(smutex SHARED shared_mutex_posix.c)
target_link_libraries(smutex pthread rt)
install(
    TARGETS smutex
    DESTINATION lib
)

add_executable(test_smutex test_smutex.c)
target_link_libraries(test_smutex smutex)
install(
    TARGETS test_smutex
    DESTINATION bin
)

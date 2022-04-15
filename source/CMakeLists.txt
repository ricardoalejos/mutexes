cmake_minimum_required(VERSION 3.16)

project(Mutex C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic ")

include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(mutex SHARED PosixSharedMutex.c Mutex.c)
target_link_libraries(mutex pthread rt)
target_include_directories(
    mutex PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> 
)
install(
    TARGETS mutex
    DESTINATION lib
)
install(
    FILES Mutex.h PosixSharedMutex.h
    DESTINATION include
)

add_executable(test_smutex test_smutex.c)
target_link_libraries(test_smutex mutex)
install(
    TARGETS test_smutex
    DESTINATION bin
)

cmake_minimum_required(VERSION 3.16)

project(
    Mutexes
    LANGUAGES C
    VERSION 0.0.1
)

execute_process(
    COMMAND git log --pretty=%H -1
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE commit_hash
)
string(STRIP "${commit_hash}" commit_hash)
execute_process(
    COMMAND git status --porcelain
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE commit_status
)
if("${commit_status}" STREQUAL "")
    set(dirty_suffix "")
else()
    set(dirty_suffix "-dirty")
endif()
set(Mutexes_COMMIT_ID "${commit_hash}${dirty_suffix}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic ")

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Mutexes)

add_subdirectory(Examples)

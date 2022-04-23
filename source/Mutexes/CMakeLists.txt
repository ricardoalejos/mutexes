configure_file(
    Version.h.in
    ${CMAKE_INSTALL_PREFIX}/include/Mutex/Version.h
    @ONLY
)
file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_LIST_DIR}/*.c
)
add_library(mutexes SHARED ${sources})
target_link_libraries(mutexes pthread rt)
target_include_directories(
    mutexes PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include> 
)
install(
    TARGETS mutexes
    DESTINATION lib
)
install(
    FILES Mutex.h PosixSharedMutex.h
    DESTINATION include/Mutex
)

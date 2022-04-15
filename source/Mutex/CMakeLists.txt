add_library(mutex SHARED PosixSharedMutex.c Mutex.c)
target_link_libraries(mutex pthread rt)
target_include_directories(
    mutex PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include> 
)
install(
    TARGETS mutex
    DESTINATION lib
)
install(
    FILES Mutex.h PosixSharedMutex.h
    DESTINATION include/Mutex
)

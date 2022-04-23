add_executable(sharedMutexDemo sharedMutexDemo.c)
target_link_libraries(sharedMutexDemo mutexes)
install(
    TARGETS sharedMutexDemo
    DESTINATION bin
)

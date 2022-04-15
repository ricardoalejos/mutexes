add_executable(test_smutex test_smutex.c)
target_link_libraries(test_smutex mutex)
install(
    TARGETS test_smutex
    DESTINATION bin
)

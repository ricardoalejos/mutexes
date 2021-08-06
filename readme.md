# Shared Mutexes

Shared Mutexes protect critical sections that only one process can access at a time. They are particularly useful for protecting accesses to physical devices (UARTs, CAN, SPI, etc).

## Test application

If a user spawns two processes that take the same shared mutex, one of the two will wait until such mutex times out, or the alternate process releases it.

## Build instructions

Run the "setenv.sh" and "build.sh" scripts (in that order). If the build is successful, the test application (test_smutex) should become available in the "out/bin" directory. The library and its public headers will become available in the "out/lib" and "out/include" directories.

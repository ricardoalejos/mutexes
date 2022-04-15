# Mutex library

This library provides a Mutex interface and multiple implementations. One of these implementations is the Shared Mutex explained below.

## Shared Mutexes

Shared Mutexes protect critical sections that only one process can access at a time. They are particularly useful for protecting accesses to physical devices (UARTs, CAN, SPI, etc).

## Test application

If a user spawns two processes that take the same shared mutex, one of the two will wait until such mutex times out, or the alternate process releases it.

## Build instructions

Run the "build.sh" script. If the build is successful, the test application (test_smutex) should become available in the "out/bin" directory. The library and its public headers will become available in the "out/lib" and "out/include" directories.

If you wished to remove the output artifacts and the build temporary files, you can run the "clean.sh" script. This script removes the output directory.

## Running the test

```bash
# 1. Fill LD_LIBRARY_PATH with the directory containing the library.
$ export LD_LIBRARY_PATH=$(pwd)/out/lib:${LD_LIBRARY_PATH}
# 2. Run the test executable (multiple instances will try taking the same mutex)
$ ./out/bin/test_smutex 
Create /mutex0.
Try taking /mutex0.
Let's wait 5 seconds for other processes to attempt taking /mutex0.
Now let's release /mutex0.
Finally, let us destroy the /mutex0 reference.
```

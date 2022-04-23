# Mutex library

This library provides a Mutex interface and multiple implementations. One of these implementations is the Shared Mutex explained below.

## Shared Mutexes

Shared Mutexes protect critical sections that only one process can access at a time. They are particularly useful for protecting accesses to physical devices (UARTs, CAN, SPI, etc).

## Test application

If a user spawns two processes that take the same shared mutex, one of the two will wait until such mutex times out, or the alternate process releases it.

## Build instructions

Run the "build.sh" script. If the build is successful, the demo application (sharedMutexDemo) should become available in the "out/bin" directory. The library and its public headers will become available in the "out/lib" and "out/include" directories.

If you wished to remove the output artifacts and the build temporary files, you can run the "clean.sh" script. This script removes the output directory.

## Running the demo

The repository contains a demo application to show how the Shared Mutex implementation of the Mutex interface works. The application creates a Shared Mutex, takes it, waits for 5 seconds, releases the mutex, and terminates itself.

If the user spawns a second instance of the sharedMutexDemo application before the first one exits, the second one will wait for the first one to finish (because they try to take the same Shared Mutex). Alternatively, it will fail to take the mutex if the first instance holds it for more than 3 seconds (the lock timeout configured in the demo application).

```bash
./scripts/sharedMutexDemo.sh
```

#ifndef _SHARED_MUTEX_POSIX_H_
#define _SHARED_MUTEX_POSIX_H_

#include "shared_mutex.h"

enum SharedMutexPosixErrorCode {
    SharedMutexPosixErrorCode_CANNOT_OPEN_SHARED_MUTEX,
    SharedMutexPosixErrorCode_CANNOT_CLOSE_SHARED_MUTEX,
    SharedMutexPosixErrorCode_FTRUNCATE_FAILED,
    SharedMutexPosixErrorCode_TIMEOUT,
    SharedMutexPosixErrorCode_PTHREAD_MUTEX_DESTROY_FAILED,
    SharedMutexPosixErrorCode_MMAP_FAILED,
    SharedMutexPosixErrorCode_MUNMAP_FAILED,
    SharedMutexPosixErrorCode_SHMUNLINK_FAILED,
    SharedMutexPosixErrorCode_PTHREAD_MUTEX_TIMEDLOCK_FAILED,
    SharedMutexPosixErrorCode_PTHREAD_MUTEX_UNLOCK_FAILED
};

// Creates a shared mutex for which the "take" function times out after
// "timeout" seconds.
int SharedMutex_createPosixSharedMutex(
    struct SharedMutex ** mutex,
    char * name,
    unsigned long timeout
);

// Destroys the reference to a shared mutex (makes the pointer NULL), and
// also deletes the underlying shared mutex file under /dev/shm if this
// was the process that created it. If other process created the mutex, then
// this function will leave it in /dev/shm
int SharedMutex_destroyPosixSharedMutex(
    struct SharedMutex ** mutex
);

#endif
#ifndef _POSIX_SHARED_MUTEX_H_
#define _POSIX_SHARED_MUTEX_H_

#include "MutexImplementation.h"

// Creates a shared mutex for which the "take" function times out after
// "timeout" seconds.
int Mutex_createPosixSharedMutex(
    Mutex ** mutex,
    char * name,
    unsigned long timeout
);

// Destroys the reference to a shared mutex (makes the pointer NULL), and
// also deletes the underlying shared mutex file under /dev/shm if this
// was the process that created it. If other process created the mutex, then
// this function will leave it in /dev/shm
int Mutex_destroyPosixSharedMutex(Mutex ** mutex);

#endif
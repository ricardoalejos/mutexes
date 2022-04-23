#ifndef _MUTEXES_VERBOSE_SHARED_MUTEX_H_
#define _MUTEXES_VERBOSE_SHARED_MUTEX_H_

#include "Mutexes/Mutex.h"

// Creates a shared mutex for which the "take" function times out after
// "timeout" seconds.
int VerboseSharedMutex_create(
    Mutex ** mutex,
    char * name,
    unsigned long timeout
);

// Destroys the reference to a shared mutex (makes the pointer NULL), and
// also deletes the underlying shared mutex file under /dev/shm if this
// was the process that created it. If other process created the mutex, then
// this function will leave it in /dev/shm
int VerboseSharedMutex_destroy(Mutex ** mutex);

#endif

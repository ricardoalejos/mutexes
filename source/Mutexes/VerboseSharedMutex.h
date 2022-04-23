#ifndef _MUTEXES_VERBOSE_SHARED_MUTEX_H_
#define _MUTEXES_VERBOSE_SHARED_MUTEX_H_

#include "Mutexes/Mutex.h"

/**
 * @brief Creates a shared mutex for which the "take" function times out after
 * "timeout" seconds. This Mutex implementation logs its actions to STDOUT.
 * 
 * @param[in] mutex The address of the pointer which will point towards the
 * Mutex instance that this function creates.
 * @param[in] name The name of the shared mutex. It should start with "/" by
 * the Posix interface.
 * @param[in] timeout The amount of seconds that calls to take() will wait
 * before they time out.
 * @return MutexReturnCode 
 */
MutexReturnCode VerboseSharedMutex_create(
    Mutex ** mutex,
    char * name,
    unsigned long timeout
);


/**
 * @brief Destroys the reference to a shared mutex (makes the pointer NULL), 
 * and also deletes the underlying shared mutex file under /dev/shm if this
 * was the process that created it. If other process created the mutex, then
 * this function will leave it in /dev/shm.
 * 
 * @param mutex The address of a pointer hosting a VerboseSharedMutex instance.
 * @return MutexReturnCode 
 */
MutexReturnCode VerboseSharedMutex_destroy(Mutex ** mutex);

#endif

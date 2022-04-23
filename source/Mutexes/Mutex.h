#ifndef _MUTEXES_MUTEX_H_
#define _MUTEXES_MUTEX_H_

typedef enum {
    MutexErrorCode_SUCCESS,
    MutexErrorCode_ERROR,
    MutexErrorCode_CANNOT_OPEN_SHARED_MUTEX,
    MutexErrorCode_CANNOT_CLOSE_SHARED_MUTEX,
    MutexErrorCode_FTRUNCATE_FAILED,
    MutexErrorCode_TIMEOUT,
    MutexErrorCode_PTHREAD_MUTEX_DESTROY_FAILED,
    MutexErrorCode_MMAP_FAILED,
    MutexErrorCode_MUNMAP_FAILED,
    MutexErrorCode_SHMUNLINK_FAILED,
    MutexErrorCode_PTHREAD_MUTEX_TIMEDLOCK_FAILED,
    MutexErrorCode_PTHREAD_MUTEX_UNLOCK_FAILED
} MutexErrorCode;

typedef struct MutexStructure Mutex;

/**
 * @brief Takes a mutex in preparation to enter a critical region. If the mutex
 * has already been taken, this function will block until it takes the mutex or
 * fails to do it. The user should check the return value to verify if the
 * mutex was taken successfully.
 * 
 * @param[in] mutex A concrete Mutex implementation.
 * @return MutexErrorCode 
 */
MutexErrorCode Mutex_take(Mutex * mutex);

/**
 * @brief Releases a previously-taken mutex after exiting a critical region.
 * 
 * @param[in] mutex A concrete Mutex implementation.
 * @return MutexErrorCode 
 */
MutexErrorCode Mutex_release(Mutex * mutex);

#endif

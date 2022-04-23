#ifndef _MUTEXES_MUTEX_H_
#define _MUTEXES_MUTEX_H_

typedef enum {
    MutexReturnCode_SUCCESS,
    MutexReturnCode_ERROR
} MutexReturnCode;

typedef struct MutexStructure Mutex;

/**
 * @brief Takes a mutex in preparation to enter a critical region. If the mutex
 * has already been taken, this function will block until it takes the mutex or
 * fails to do it. The user should check the return value to verify if the
 * mutex was taken successfully.
 * 
 * @param[in] mutex A concrete Mutex implementation.
 * @return MutexReturnCode 
 */
MutexReturnCode Mutex_take(Mutex * mutex);

/**
 * @brief Releases a previously-taken mutex after exiting a critical region.
 * 
 * @param[in] mutex A concrete Mutex implementation.
 * @return MutexReturnCode 
 */
MutexReturnCode Mutex_release(Mutex * mutex);

#endif

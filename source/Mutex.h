#ifndef _MUTEX_H_
#define _MUTEX_H_

enum MutexErrorCode {
    MutexErrorCode_SUCCESS,
    MutexErrorCode_ERROR_BASE,
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
};

typedef struct MutexStructure Mutex;

int Mutex_take(Mutex * mutex);
int Mutex_release(Mutex * mutex);

#endif

#ifndef _SHARED_MUTEX_H_
#define _SHARED_MUTEX_H_

enum SharedMutexErrorCode {
    SharedMutexErrorCode_SUCCESS,
    SharedMutexErrorCode_ERROR_BASE
};

struct SharedMutex {
    int (*take)(struct SharedMutex * mutex);
    int (*release)(struct SharedMutex * mutex);
};

#endif

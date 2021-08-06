#include "shared_mutex_posix.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>           // clock_gettime, timespec, CLOCK_REALTIME
#include <errno.h>          // errno, ENOENT
#include <fcntl.h>          // O_RDWR, O_CREATE
#include <sys/mman.h>       // shm_open, shm_unlink, mmap, munmap,
                            // PROT_READ, PROT_WRITE, MAP_SHARED, MAP_FAILED
#include <unistd.h>         // ftruncate, close
#include <string.h>         // strcpy

struct PosixSharedMutex {
    struct SharedMutex base;
    int fileDescriptor;
    char name[128];
    pthread_mutex_t * pMutex;
    bool createdFlag;
    unsigned long timeout;
};

static int take(struct SharedMutex * mutex);
static int release(struct SharedMutex * mutex);

int SharedMutex_createPosixSharedMutex(
    struct SharedMutex ** mutex,
    char * name,
    unsigned long timeout
) {
    struct PosixSharedMutex * posixSharedMutex = (
        (struct PosixSharedMutex *) malloc(
            sizeof(struct PosixSharedMutex)
        )
    );

    posixSharedMutex->base.take = take;
    posixSharedMutex->base.release = release;
    strncpy(posixSharedMutex->name, name, 128);

    posixSharedMutex->createdFlag = false;

    posixSharedMutex->fileDescriptor = shm_open(
        posixSharedMutex->name,
        O_RDWR,
        0660
    );

    if (errno == ENOENT) {
        posixSharedMutex->fileDescriptor = shm_open(
            posixSharedMutex->name,
            O_RDWR|O_CREAT,
            0660
        );
        posixSharedMutex->createdFlag=true;
    }

    int feedback = ftruncate(
        posixSharedMutex->fileDescriptor,
        sizeof(pthread_mutex_t)
    );
    if (feedback != 0) {
        return SharedMutexPosixErrorCode_FTRUNCATE_FAILED;
    }

    posixSharedMutex->pMutex = (pthread_mutex_t *) mmap(
        NULL,
        sizeof(pthread_mutex_t),
        PROT_READ|PROT_WRITE,
        MAP_SHARED,
        posixSharedMutex->fileDescriptor,
        0
    );

    posixSharedMutex->timeout = timeout;

    if (posixSharedMutex->createdFlag) {
        pthread_mutexattr_t attributes;
        pthread_mutexattr_init(&attributes);
        pthread_mutexattr_setpshared(&attributes, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(posixSharedMutex->pMutex, &attributes);
    }
    *mutex = &(posixSharedMutex->base);

    return SharedMutexErrorCode_SUCCESS;
}

int SharedMutex_destroyPosixSharedMutex(struct SharedMutex ** mutex) {
    struct PosixSharedMutex * posixSharedMutex = *(
        (struct PosixSharedMutex **) mutex
    );
    if (posixSharedMutex->createdFlag) {
        if ((errno = pthread_mutex_destroy(posixSharedMutex->pMutex))) {
            return SharedMutexPosixErrorCode_PTHREAD_MUTEX_DESTROY_FAILED;
        }
    }
    if (munmap((void *)posixSharedMutex->pMutex, sizeof(pthread_mutex_t))) {
        return SharedMutexPosixErrorCode_MUNMAP_FAILED;
    }
    *mutex = NULL;
    if (close(posixSharedMutex->fileDescriptor)) {
        return SharedMutexPosixErrorCode_CANNOT_CLOSE_SHARED_MUTEX;
    }
    posixSharedMutex->fileDescriptor = 0;
    if (posixSharedMutex->createdFlag) {
        if (shm_unlink(posixSharedMutex->name)) {
            return SharedMutexPosixErrorCode_SHMUNLINK_FAILED;
        }
    }
    free(posixSharedMutex);
    return SharedMutexErrorCode_SUCCESS;
}

static int take(struct SharedMutex * mutex) {
    struct PosixSharedMutex * posixSharedMutex = (
        (struct PosixSharedMutex *) mutex
    );
    struct timespec timeoutSpec = {0};
    clock_gettime(CLOCK_REALTIME, &timeoutSpec);
    timeoutSpec.tv_sec += posixSharedMutex->timeout;
    int feedback = pthread_mutex_timedlock(
        posixSharedMutex->pMutex,
        &timeoutSpec
    );
    if (feedback == 0) {
        return SharedMutexErrorCode_SUCCESS;
    } else if (feedback == ETIMEDOUT) {
        return SharedMutexPosixErrorCode_TIMEOUT;
    } else {
        return SharedMutexPosixErrorCode_PTHREAD_MUTEX_TIMEDLOCK_FAILED;
    }
}

static int release(struct SharedMutex * mutex) {
    struct PosixSharedMutex * posixSharedMutex = (
        (struct PosixSharedMutex *) mutex
    );
    int feedback = pthread_mutex_unlock(posixSharedMutex->pMutex);
    if (feedback != 0) {
        return SharedMutexPosixErrorCode_PTHREAD_MUTEX_UNLOCK_FAILED;
    }
    return SharedMutexErrorCode_SUCCESS;
}

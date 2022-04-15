#include "PosixSharedMutex.h"
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
    Mutex base;
    int fileDescriptor;
    char name[128];
    pthread_mutex_t * pMutex;
    bool createdFlag;
    unsigned long timeout;
};

static int take(Mutex * mutex);
static int release(Mutex * mutex);

const struct MutexInterface posixSharedMutexInterface = {
    .release=release,
    .take=take
};

int Mutex_createPosixSharedMutex(
    Mutex ** mutex,
    char * name,
    unsigned long timeout
) {
    struct PosixSharedMutex * posixSharedMutex = (
        (struct PosixSharedMutex *) malloc(
            sizeof(struct PosixSharedMutex)
        )
    );

    posixSharedMutex->base.implementationInterface=&posixSharedMutexInterface;
    posixSharedMutex->base.instanceData = (void *)posixSharedMutex;
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
        return MutexErrorCode_FTRUNCATE_FAILED;
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

    return MutexErrorCode_SUCCESS;
}

int Mutex_destroyPosixSharedMutex(Mutex ** mutex) {
    struct PosixSharedMutex * posixSharedMutex = *(
        (struct PosixSharedMutex **) mutex
    );
    if (posixSharedMutex->createdFlag) {
        if ((errno = pthread_mutex_destroy(posixSharedMutex->pMutex))) {
            return MutexErrorCode_PTHREAD_MUTEX_DESTROY_FAILED;
        }
    }
    if (munmap((void *)posixSharedMutex->pMutex, sizeof(pthread_mutex_t))) {
        return MutexErrorCode_MUNMAP_FAILED;
    }
    *mutex = NULL;
    if (close(posixSharedMutex->fileDescriptor)) {
        return MutexErrorCode_CANNOT_CLOSE_SHARED_MUTEX;
    }
    posixSharedMutex->fileDescriptor = 0;
    if (posixSharedMutex->createdFlag) {
        if (shm_unlink(posixSharedMutex->name)) {
            return MutexErrorCode_SHMUNLINK_FAILED;
        }
    }
    free(posixSharedMutex);
    return MutexErrorCode_SUCCESS;
}

static int take(Mutex * mutex) {
    struct PosixSharedMutex * posixSharedMutex = (struct PosixSharedMutex *) mutex->instanceData;
    struct timespec timeoutSpec = {0};
    clock_gettime(CLOCK_REALTIME, &timeoutSpec);
    timeoutSpec.tv_sec += posixSharedMutex->timeout;
    int feedback = pthread_mutex_timedlock(
        posixSharedMutex->pMutex,
        &timeoutSpec
    );
    if (feedback == 0) {
        return MutexErrorCode_SUCCESS;
    } else if (feedback == ETIMEDOUT) {
        return MutexErrorCode_TIMEOUT;
    } else {
        return MutexErrorCode_PTHREAD_MUTEX_TIMEDLOCK_FAILED;
    }
}

static int release(Mutex * mutex) {
    struct PosixSharedMutex * posixSharedMutex = (struct PosixSharedMutex *) mutex->instanceData;
    int feedback = pthread_mutex_unlock(posixSharedMutex->pMutex);
    if (feedback != 0) {
        return MutexErrorCode_PTHREAD_MUTEX_UNLOCK_FAILED;
    }
    return MutexErrorCode_SUCCESS;
}

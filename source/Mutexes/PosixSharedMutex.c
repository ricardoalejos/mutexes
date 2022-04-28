#include "Mutexes/PosixSharedMutex.h"
#include "Mutexes/MutexImplementation.h"
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

static MutexReturnCode take(Mutex * mutex);
static MutexReturnCode release(Mutex * mutex);

const struct MutexInterface posixSharedMutexInterface = {
    .release=release,
    .take=take
};

MutexReturnCode PosixSharedMutex_create(
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
    posixSharedMutex->base.instanceData = (Mutex *)posixSharedMutex;
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
        return MutexReturnCode_ERROR;
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
        pthread_mutexattr_setrobust (&attributes, PTHREAD_MUTEX_ROBUST);
        pthread_mutex_init(posixSharedMutex->pMutex, &attributes);
    }
    *mutex = &(posixSharedMutex->base);

    return MutexReturnCode_SUCCESS;
}

MutexReturnCode PosixSharedMutex_destroy(Mutex ** mutex) {
    struct PosixSharedMutex * posixSharedMutex = *(
        (struct PosixSharedMutex **) mutex
    );
    if (posixSharedMutex->createdFlag) {
        if ((errno = pthread_mutex_destroy(posixSharedMutex->pMutex))) {
            return MutexReturnCode_ERROR;
        }
    }
    if (munmap((void *)posixSharedMutex->pMutex, sizeof(pthread_mutex_t))) {
        return MutexReturnCode_ERROR;
    }
    *mutex = NULL;
    if (close(posixSharedMutex->fileDescriptor)) {
        return MutexReturnCode_ERROR;
    }
    posixSharedMutex->fileDescriptor = 0;
    if (posixSharedMutex->createdFlag) {
        if (shm_unlink(posixSharedMutex->name)) {
            return MutexReturnCode_ERROR;
        }
    }
    free(posixSharedMutex);
    return MutexReturnCode_SUCCESS;
}

static MutexReturnCode take(Mutex * mutex) {
    struct PosixSharedMutex * posixSharedMutex = (struct PosixSharedMutex *) mutex->instanceData;
    struct timespec timeoutSpec = {0};
    clock_gettime(CLOCK_REALTIME, &timeoutSpec);
    timeoutSpec.tv_sec += posixSharedMutex->timeout;
    int feedback = pthread_mutex_timedlock(
        posixSharedMutex->pMutex,
        &timeoutSpec
    );
    if (feedback == 0) {
        return MutexReturnCode_SUCCESS;
    } else if (feedback == ETIMEDOUT) {
        return MutexReturnCode_ERROR;
    } else if (feedback == EOWNERDEAD) {
        feedback = pthread_mutex_consistent(posixSharedMutex->pMutex);
        if (feedback) {
            return MutexReturnCode_ERROR;
        }
    }
    return MutexReturnCode_ERROR;
}

static MutexReturnCode release(Mutex * mutex) {
    struct PosixSharedMutex * posixSharedMutex = (struct PosixSharedMutex *) mutex->instanceData;
    int feedback = pthread_mutex_unlock(posixSharedMutex->pMutex);
    if (feedback != 0) {
        return MutexReturnCode_ERROR;
    }
    return MutexReturnCode_SUCCESS;
}

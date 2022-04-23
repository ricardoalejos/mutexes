#include "Mutexes/PosixSharedMutex.h"
#include "Mutexes/MutexImplementation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Mutex base;
    Mutex * posixSharedMutex;
    char * name;
} VerboseSharedMutex;

static MutexReturnCode take(Mutex * mutex);
static MutexReturnCode release(Mutex * mutex);

const struct MutexInterface verboseSharedMutexInterface = {
    .release=release,
    .take=take
};

MutexReturnCode VerboseSharedMutex_create(
    Mutex ** mutex,
    char * name,
    unsigned long timeout
) {
    printf("Creating shared mutex '%s' with timeout of %ld seconds.\n", name, timeout);
    VerboseSharedMutex * this = (VerboseSharedMutex *)malloc(sizeof(VerboseSharedMutex));
    if (!this) {
        printf("Cannot allocate memory for mutex '%s'.\n", name);
        return MutexReturnCode_ERROR;
    }
    this->base.implementationInterface=&verboseSharedMutexInterface;
    this->base.instanceData=(Mutex*)this;
    this->name = strdup(name);
    int feedback = PosixSharedMutex_create(&(this->posixSharedMutex), name, timeout);
    if (feedback) {
        printf("Failed to create a PosixSharedMutex (error %d).\n", feedback);
        free(this->name);
        free(this);
        return MutexReturnCode_ERROR;
    }
    *mutex = &(this->base);
    return MutexReturnCode_SUCCESS;
}

MutexReturnCode VerboseSharedMutex_destroy(Mutex ** mutex) {
    VerboseSharedMutex * this = (VerboseSharedMutex *) *mutex;
    printf("Destroying shared mutex '%s'.\n", this->name);
    PosixSharedMutex_destroy(&(this->posixSharedMutex));
    free(this->name);
    free(*mutex);
    *mutex=NULL;
    return MutexReturnCode_SUCCESS;
}

static MutexReturnCode take(Mutex * mutex) {
    VerboseSharedMutex * this = (VerboseSharedMutex *) mutex;
    printf("Taking shared mutex '%s' ... ", this->name);
    MutexReturnCode feedback = Mutex_take(this->posixSharedMutex);
    if (feedback == MutexReturnCode_SUCCESS) {
        printf("SUCCESS!\n");
    } else {
        printf("ERROR\n");
    }
    return feedback;
}

static MutexReturnCode release(Mutex * mutex) {
    VerboseSharedMutex * this = (VerboseSharedMutex *) mutex;
    printf("Releasing shared mutex '%s' ... ", this->name);
    MutexReturnCode feedback = Mutex_release(this->posixSharedMutex);
    if (feedback == MutexReturnCode_SUCCESS) {
        printf("SUCCESS!\n");
    } else {
        printf("ERROR\n");
    }
    return feedback;
}

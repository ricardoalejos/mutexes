#ifndef _MUTEX_IMPLEMENTATION_H_
#define _MUTEX_IMPLEMENTATION_H_

#include "Mutex.h"

struct MutexInterface {
    int (*take)(Mutex * mutex);
    int (*release)(Mutex * mutex);
};

struct MutexStructure {
    struct MutexInterface const * implementationInterface;
    void * instanceData;
};

#endif

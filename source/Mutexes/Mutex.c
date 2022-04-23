#include "Mutexes/MutexImplementation.h"

MutexErrorCode Mutex_take(Mutex * mutex) {
    return mutex->implementationInterface->take(mutex->instanceData);
}

MutexErrorCode Mutex_release(Mutex * mutex) {
    return mutex->implementationInterface->release(mutex->instanceData);
}

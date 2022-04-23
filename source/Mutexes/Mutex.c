#include "Mutexes/MutexImplementation.h"

MutexReturnCode Mutex_take(Mutex * mutex) {
    return mutex->implementationInterface->take(mutex->instanceData);
}

MutexReturnCode Mutex_release(Mutex * mutex) {
    return mutex->implementationInterface->release(mutex->instanceData);
}

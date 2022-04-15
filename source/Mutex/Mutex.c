#include "MutexImplementation.h"

int Mutex_take(Mutex * mutex) {
    return mutex->implementationInterface->take(mutex);
}

int Mutex_release(Mutex * mutex) {
    return mutex->implementationInterface->release(mutex);
}

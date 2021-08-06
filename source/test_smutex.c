#include "shared_mutex_posix.h"
#include "stdio.h"
#include <pthread.h>
#include <unistd.h>

int main() {
    static struct SharedMutex * mutex0 = NULL;
    puts("Creation");
    SharedMutex_createPosixSharedMutex(&mutex0, "/test0", 3);
    puts("Take");
    if (mutex0->take(mutex0) != SharedMutexErrorCode_SUCCESS) {
        puts("Failed to take mutex");
        puts("Destroy");
        SharedMutex_destroyPosixSharedMutex(&mutex0);
        return 1;
    }
    puts("Wait 5 seconds");
    sleep(5);
    puts("Release");
    mutex0->release(mutex0);
    puts("Destroy");
    SharedMutex_destroyPosixSharedMutex(&mutex0);
    return 0;
}

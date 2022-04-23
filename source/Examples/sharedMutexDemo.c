#include "Mutexes/VerboseSharedMutex.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main() {
    Mutex * mutex0 = NULL;
    VerboseSharedMutex_create(&mutex0, "/mutex0", 3);
    if (Mutex_take(mutex0) != MutexReturnCode_SUCCESS) {
        VerboseSharedMutex_destroy(&mutex0);
        return 1;
    }
    puts("Let's wait 5 seconds for other processes to attempt taking /mutex0.");
    sleep(5);
    Mutex_release(mutex0);
    VerboseSharedMutex_destroy(&mutex0);
    return 0;
}

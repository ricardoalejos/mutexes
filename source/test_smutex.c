#include "PosixSharedMutex.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main() {

    Mutex * mutex0 = NULL;

    puts("Create /mutex0.");
    Mutex_createPosixSharedMutex(&mutex0, "/mutex0", 3);

    puts("Try taking /mutex0.");
    if (Mutex_take(mutex0) != MutexErrorCode_SUCCESS) {
        puts("Whoops! This process failed to take /mutex0.");
        Mutex_destroyPosixSharedMutex(&mutex0);
        return 1;
    }

    puts("Let's wait 5 seconds for other processes to attempt taking /mutex0.");
    sleep(5);

    puts("Now let's release /mutex0.");
    Mutex_release(mutex0);

    puts("Finally, let us destroy the /mutex0 reference.");
    Mutex_destroyPosixSharedMutex(&mutex0);

    return 0;
}

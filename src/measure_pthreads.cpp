#include "measure_pthreads.h"
#include "wall_clock.h"

void measurePThreadsOneMutex()
{
    // Measure time for incrementing doubles as ground truth.
    {
        volatile int x = 0;
        double start = sysTime();
        for (int i = 0; i < REPETITIONS; ++i) {
            x += i;
        }
        double end = sysTime();

        printf("%d int sum: %f s\n", REPETITIONS, end - start);
    }

    // Measure time for using atomic operation for the addition.
    {
        volatile int x = 0;
        double start = sysTime();
        for (int i = 0; i < REPETITIONS; ++i) {
            __sync_fetch_and_add(&x, i);
        }
        double end = sysTime();

        printf("%d double atomic sum: %f s\n", REPETITIONS, end - start);
    }
    
    // Measure time for lock/unlock pairs.
    {
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

        volatile int x = 0;
        double start = sysTime();
        for (int i = 0; i < REPETITIONS; ++i) {
            pthread_mutex_lock(&mutex);
            x += i;
            pthread_mutex_unlock(&mutex);
        }
        double end = sysTime();

        printf("%d pthread_mutex_lock/pthread_mutex_unlock pairs: %f s\n", REPETITIONS, end - start);

        pthread_mutex_destroy(&mutex);
    }
}

void measurePThreads()
{
    std::cout << "Measuring for pthreads\n\n";

    measurePThreadsOneMutex();

    std::cout << "\n\n";
}


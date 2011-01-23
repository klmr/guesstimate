#include <omp.h>

#include "measure_omp.h"
#include "wall_clock.h"

void measureOmpOneMutex()
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

    // Measure time for using OpenMP atomic operation for the addition.
    {
        volatile int x = 0;
        double start = sysTime();
        omp_set_num_threads(1);
        #pragma omp parallel for
        for (int i = 0; i < REPETITIONS; ++i) {
            #pragma omp atomic
            x += i;
        }
        double end = sysTime();

        printf("%d double atomic sum: %f s\n", REPETITIONS, end - start);
    }
    
    // Measure time for using atomic operation for the addition.
    {
        volatile int x = 0;
        double start = sysTime();
        omp_set_num_threads(1);
        #pragma omp parallel for
        for (int i = 0; i < REPETITIONS; ++i) {
            __sync_fetch_and_add(&x, i);
        }
        double end = sysTime();

        printf("%d double atomic sum: %f s\n", REPETITIONS, end - start);
    }

    // Measure time for lock/unlock pairs.
    {
        volatile int x = 0;
        double start = sysTime();
        omp_set_num_threads(1);
        #pragma omp parallel for
        for (int i = 0; i < REPETITIONS; ++i) {
            #pragma omp critical
            {
                x += i;
            }
        }
        double end = sysTime();

        printf("%d critical sum pairs: %f s\n", REPETITIONS, end - start);
    }
}

void measureOmp()
{
    std::cout << "Measuring for OpenMP\n\n";

    measureOmpOneMutex();

    std::cout << "\n\n";
}


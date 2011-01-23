// ==========================================================================
//                Guesstimate - Technology Constant Estimator
// ==========================================================================
// Copyright (c) 2011, Manuel Holtgrewe
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Manuel Holtgrewe nor the names of its
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================

#include "measure_pthreads.h"
#include "wall_clock.h"

void measureOneMutex()
{
    // Measure time for incrementing doubles as ground truth.
    {
        volatile int x = 0;
        double start = sysTime();
        for (int i = 0; i < REPETITIONS; ++i) {
            x += i;
        }
        double end = sysTime();

        printf("%d int sum pairs: %f s\n", REPETITIONS, end - start);
    }

    // Measure time for using atomic operation for the addition.
    {
        volatile int x = 0;
        double start = sysTime();
        for (int i = 0; i < REPETITIONS; ++i) {
            __sync_fetch_and_add(&x, i);
        }
        double end = sysTime();

        printf("%d double sum pairs: %f s\n", REPETITIONS, end - start);
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

    measureOneMutex();
}


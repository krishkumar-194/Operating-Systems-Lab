#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

long long counter = 0;

pthread_mutex_t mutex;

void *increment_counter(void *arg)
{
    int thread_id = *(int *)arg;

    for (int i = 0; i < ITERATIONS; i++) {

        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    printf("Thread %d completed.\n", thread_id);

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("=====================================\n");
    printf("      THREAD MUTEX DEMONSTRATION\n");
    printf("=====================================\n");

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUM_THREADS; i++) {

        thread_ids[i] = i + 1;

        if (pthread_create(
                &threads[i],
                NULL,
                increment_counter,
                &thread_ids[i]) != 0) {

            perror("pthread_create failed");
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n=====================================\n");
    printf("Expected Counter : %d\n",
           NUM_THREADS * ITERATIONS);

    printf("Actual Counter   : %lld\n",
           counter);

    printf("=====================================\n");

    pthread_mutex_destroy(&mutex);

    printf("Program completed successfully.\n");

    return EXIT_SUCCESS;
}
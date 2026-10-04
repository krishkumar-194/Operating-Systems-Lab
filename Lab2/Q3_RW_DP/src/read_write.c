#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define READERS 3
#define WRITERS 2
#define OPERATIONS 3

int shared_data = 0;

pthread_mutex_t rw_mutex;
pthread_mutex_t read_mutex;

int reader_count = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < OPERATIONS; i++) {

        pthread_mutex_lock(&read_mutex);
        reader_count++;

        if (reader_count == 1)
            pthread_mutex_lock(&rw_mutex);

        pthread_mutex_unlock(&read_mutex);

        printf("Reader %d reads data = %d\n",
               id, shared_data);

        pthread_mutex_lock(&read_mutex);
        reader_count--;

        if (reader_count == 0)
            pthread_mutex_unlock(&rw_mutex);

        pthread_mutex_unlock(&read_mutex);

        usleep(100000);
    }

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < OPERATIONS; i++) {

        pthread_mutex_lock(&rw_mutex);

        shared_data++;

        printf("Writer %d writes data = %d\n",
               id, shared_data);

        pthread_mutex_unlock(&rw_mutex);

        usleep(150000);
    }

    return NULL;
}

int main(void)
{
    pthread_t readers[READERS];
    pthread_t writers[WRITERS];

    int reader_ids[READERS];
    int writer_ids[WRITERS];

    printf("========================================\n");
    printf("       READERS-WRITERS PROBLEM\n");
    printf("========================================\n");

    pthread_mutex_init(&rw_mutex, NULL);
    pthread_mutex_init(&read_mutex, NULL);

    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1;

        pthread_create(
            &readers[i],
            NULL,
            reader,
            &reader_ids[i]
        );
    }

    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1;

        pthread_create(
            &writers[i],
            NULL,
            writer,
            &writer_ids[i]
        );
    }

    for (int i = 0; i < READERS; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < WRITERS; i++)
        pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&rw_mutex);
    pthread_mutex_destroy(&read_mutex);

    printf("\n========================================\n");
    printf("Final shared data = %d\n", shared_data);
    printf("Readers-Writers completed successfully.\n");
    printf("========================================\n");

    return 0;
}
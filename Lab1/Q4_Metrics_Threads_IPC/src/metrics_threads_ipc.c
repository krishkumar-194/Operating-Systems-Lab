#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#define SIZE 1000000

long long sum = 0;

void *calculate_sum(void *arg)
{
    int *data = (int *)arg;

    for (int i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    pthread_exit(NULL);
}

double get_time(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void show_metrics(void)
{
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == -1) {
        perror("getrusage");
        return;
    }

    printf("\n========== PROCESS METRICS ==========\n");

    printf("User CPU Time   : %ld.%06ld seconds\n",
           usage.ru_utime.tv_sec,
           usage.ru_utime.tv_usec);

    printf("System CPU Time : %ld.%06ld seconds\n",
           usage.ru_stime.tv_sec,
           usage.ru_stime.tv_usec);

    printf("Maximum Memory  : %ld KB\n",
           usage.ru_maxrss);

    printf("=====================================\n");
}

int main(void)
{
    printf("============================================\n");
    printf("   OS METRICS, THREADS AND IPC DEMO\n");
    printf("============================================\n");

    int *data = malloc(SIZE * sizeof(int));

    if (data == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < SIZE; i++) {
        data[i] = 1;
    }

    /* ---------- THREAD ---------- */

    pthread_t thread;

    double start = get_time();

    if (pthread_create(&thread, NULL, calculate_sum, data) != 0) {
        perror("pthread_create");
        free(data);
        return EXIT_FAILURE;
    }

    pthread_join(thread, NULL);

    double end = get_time();

    printf("\n========== THREAD EXECUTION ==========\n");
    printf("Thread completed successfully.\n");
    printf("Sum = %lld\n", sum);
    printf("Execution Time = %.6f seconds\n",
           end - start);
    printf("======================================\n");

    /* ---------- IPC USING PIPE ---------- */

    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        free(data);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        free(data);
        return EXIT_FAILURE;
    }

    if (pid == 0) {

        /* Child Process */

        close(pipefd[0]);

        const char message[] =
            "Hello from Child Process using Pipe IPC";

        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]);

        printf("\nChild PID = %ld\n",
               (long)getpid());

        exit(EXIT_SUCCESS);
    }

    else {

        /* Parent Process */

        close(pipefd[1]);

        char buffer[100];

        ssize_t bytes_read;

        bytes_read = read(pipefd[0],
                          buffer,
                          sizeof(buffer));

        if (bytes_read > 0) {
            printf("\n============= IPC =============\n");
            printf("Parent PID = %ld\n",
                   (long)getpid());

            printf("Message received: %s\n",
                   buffer);

            printf("IPC Method: Pipe\n");
            printf("===============================\n");
        }

        close(pipefd[0]);

        waitpid(pid, NULL, 0);
    }

    /* ---------- METRICS ---------- */

    show_metrics();

    free(data);

    printf("\nProgram completed successfully.\n");

    return EXIT_SUCCESS;
}
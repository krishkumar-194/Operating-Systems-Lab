#include <stdio.h>

#define PROCESSES 5
#define RESOURCES 3

void calculate_need(int max[PROCESSES][RESOURCES],
                    int allocation[PROCESSES][RESOURCES],
                    int need[PROCESSES][RESOURCES]) {
    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int is_safe(int available[RESOURCES],
            int max[PROCESSES][RESOURCES],
            int allocation[PROCESSES][RESOURCES]) {

    int need[PROCESSES][RESOURCES];
    int work[RESOURCES];
    int finish[PROCESSES] = {0};
    int safe_sequence[PROCESSES];
    int count = 0;

    calculate_need(max, allocation, need);

    for (int i = 0; i < RESOURCES; i++)
        work[i] = available[i];

    while (count < PROCESSES) {
        int found = 0;

        for (int i = 0; i < PROCESSES; i++) {
            if (finish[i] == 0) {
                int possible = 1;

                for (int j = 0; j < RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < RESOURCES; j++)
                        work[j] += allocation[i][j];

                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    if (count == PROCESSES) {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < PROCESSES; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < PROCESSES - 1)
                printf(" -> ");
        }

        printf("\n");
        return 1;
    }

    printf("\nSystem is in UNSAFE state. Deadlock may occur.\n");
    return 0;
}

int main(void) {

    int available[RESOURCES] = {3, 3, 2};

    int max[PROCESSES][RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allocation[PROCESSES][RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    printf("========================================\n");
    printf("          DEADLOCK AVOIDANCE\n");
    printf("          BANKER'S ALGORITHM\n");
    printf("========================================\n");

    printf("\nAvailable Resources:\n");
    printf("R1 = %d, R2 = %d, R3 = %d\n",
           available[0], available[1], available[2]);

    printf("\nChecking system safety...\n");

    is_safe(available, max, allocation);

    printf("\n========================================\n");
    printf("Deadlock analysis completed successfully.\n");
    printf("========================================\n");

    return 0;
}
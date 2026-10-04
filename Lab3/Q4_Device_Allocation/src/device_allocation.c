#include <stdio.h>

#define PROCESSES 4
#define DEVICES 3

int main(void) {
    int allocation[PROCESSES][DEVICES] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}
    };

    int available[DEVICES] = {0, 0, 0};

    printf("========================================\n");
    printf("          DEVICE ALLOCATION\n");
    printf("========================================\n");

    printf("\nDevice Allocation Table:\n");
    printf("Process   D1  D2  D3\n");

    for (int i = 0; i < PROCESSES; i++) {
        printf("P%d        ", i + 1);
        for (int j = 0; j < DEVICES; j++)
            printf("%d   ", allocation[i][j]);
        printf("\n");
    }

    printf("\nAvailable Devices:\n");
    printf("D1 = %d, D2 = %d, D3 = %d\n",
           available[0], available[1], available[2]);

    printf("\nDevice allocation completed successfully.\n");

    printf("========================================\n");

    return 0;
}

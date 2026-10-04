#include <stdio.h>

#define BLOCKS 10

int main(void) {
    int allocation[BLOCKS] = {1, 1, 1, 0, 1, 0, 1, 1, 0, 0};

    printf("========================================\n");
    printf("           FILE ALLOCATION\n");
    printf("========================================\n");

    printf("\nDisk Blocks:\n");

    for (int i = 0; i < BLOCKS; i++)
        printf("Block %d : %s\n", i,
               allocation[i] ? "Allocated" : "Free");

    printf("\nAllocation methods:\n");
    printf("1. Contiguous Allocation\n");
    printf("2. Linked Allocation\n");
    printf("3. Indexed Allocation\n");

    printf("\nFile allocation completed successfully.\n");
    printf("========================================\n");

    return 0;
}

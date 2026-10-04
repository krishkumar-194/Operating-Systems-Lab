#include <stdio.h>

#define PAGES 4
#define PAGE_SIZE 100

int main(void) {
    int page_table[PAGES] = {2, 0, 3, 1};

    int logical_address;
    int page_number;
    int offset;
    int frame_number;
    int physical_address;

    printf("========================================\n");
    printf("     SWAPPING & ADDRESS TRANSLATION\n");
    printf("========================================\n");

    printf("\nPage Size = %d\n", PAGE_SIZE);

    printf("\nPage Table:\n");
    for (int i = 0; i < PAGES; i++) {
        printf("Page %d -> Frame %d\n", i, page_table[i]);
    }

    printf("\nEnter Logical Address (0-399): ");
    scanf("%d", &logical_address);

    if (logical_address < 0 || logical_address >= PAGES * PAGE_SIZE) {
        printf("Invalid logical address!\n");
        return 1;
    }

    page_number = logical_address / PAGE_SIZE;
    offset = logical_address % PAGE_SIZE;

    frame_number = page_table[page_number];
    physical_address = frame_number * PAGE_SIZE + offset;

    printf("\nLogical Address  = %d\n", logical_address);
    printf("Page Number      = %d\n", page_number);
    printf("Offset           = %d\n", offset);
    printf("Frame Number     = %d\n", frame_number);
    printf("Physical Address = %d\n", physical_address);

    printf("\n========================================\n");
    printf("Address translation completed successfully.\n");
    printf("========================================\n");

    return 0;
}
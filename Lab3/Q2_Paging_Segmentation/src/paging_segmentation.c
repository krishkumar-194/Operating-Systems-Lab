#include <stdio.h>

#define PAGE_SIZE 100

int main(void) {
    int page_table[] = {3, 1, 4, 0, 2};
    int logical_address, page, offset, frame, physical;

    printf("========================================\n");
    printf("       PAGING & SEGMENTATION\n");
    printf("========================================\n");

    printf("\nPaging\n");
    printf("Page Size = %d\n", PAGE_SIZE);

    printf("\nPage Table:\n");
    for (int i = 0; i < 5; i++)
        printf("Page %d -> Frame %d\n", i, page_table[i]);

    printf("\nEnter Logical Address (0-499): ");
    scanf("%d", &logical_address);

    if (logical_address < 0 || logical_address >= 500) {
        printf("Invalid address!\n");
        return 1;
    }

    page = logical_address / PAGE_SIZE;
    offset = logical_address % PAGE_SIZE;
    frame = page_table[page];
    physical = frame * PAGE_SIZE + offset;

    printf("\nPage Number      = %d\n", page);
    printf("Offset           = %d\n", offset);
    printf("Frame Number     = %d\n", frame);
    printf("Physical Address = %d\n", physical);

    printf("\nSegmentation Example:\n");

    int base = 1000;
    int limit = 500;
    int segment_offset = 250;

    printf("Segment Base  = %d\n", base);
    printf("Segment Limit = %d\n", limit);
    printf("Offset        = %d\n", segment_offset);

    if (segment_offset < limit)
        printf("Physical Address = %d\n", base + segment_offset);
    else
        printf("Segmentation Fault!\n");

    printf("\n========================================\n");
    printf("Paging and Segmentation completed successfully.\n");
    printf("========================================\n");

    return 0;
}

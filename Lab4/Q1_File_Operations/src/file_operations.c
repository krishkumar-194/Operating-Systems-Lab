#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char text[100];

    printf("========================================\n");
    printf("           FILE OPERATIONS\n");
    printf("========================================\n");

    fp = fopen("testfile.txt", "w");
    if (fp == NULL) {
        perror("File creation failed");
        return 1;
    }

    fprintf(fp, "Operating Systems Lab - File Operations\n");
    fprintf(fp, "File created and written successfully.\n");
    fclose(fp);

    fp = fopen("testfile.txt", "r");
    if (fp == NULL) {
        perror("File opening failed");
        return 1;
    }

    printf("\nFile Content:\n");
    while (fgets(text, sizeof(text), fp) != NULL)
        printf("%s", text);

    fclose(fp);

    printf("\nFile read operation completed successfully.\n");
    printf("========================================\n");

    return 0;
}

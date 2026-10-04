#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    struct stat st;

    printf("========================================\n");
    printf("          FILE TYPES & ACCESS\n");
    printf("========================================\n");

    FILE *fp = fopen("access_test.txt", "w");
    if (fp == NULL) {
        perror("File creation failed");
        return 1;
    }

    fprintf(fp, "Testing file types and access permissions.\n");
    fclose(fp);

    if (stat("access_test.txt", &st) == -1) {
        perror("stat failed");
        return 1;
    }

    printf("\nFile Information:\n");
    printf("File Size = %ld bytes\n", (long)st.st_size);

    printf("\nAccess Permissions:\n");
    printf("Read    : %s\n",
           access("access_test.txt", R_OK) == 0 ? "Yes" : "No");
    printf("Write   : %s\n",
           access("access_test.txt", W_OK) == 0 ? "Yes" : "No");
    printf("Execute : %s\n",
           access("access_test.txt", X_OK) == 0 ? "Yes" : "No");

    printf("\nFile types and access check completed successfully.\n");
    printf("========================================\n");

    return 0;
}

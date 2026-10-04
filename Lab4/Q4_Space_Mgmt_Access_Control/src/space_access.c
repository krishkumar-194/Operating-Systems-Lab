#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    FILE *fp;
    struct stat st;

    printf("========================================\n");
    printf("      SPACE MANAGEMENT & ACCESS CONTROL\n");
    printf("========================================\n");

    fp = fopen("space_test.txt", "w");
    if (fp == NULL) {
        perror("File creation failed");
        return 1;
    }

    fprintf(fp, "Operating Systems Lab\n");
    fprintf(fp, "Testing space management and access control.\n");
    fclose(fp);

    if (stat("space_test.txt", &st) == -1) {
        perror("stat failed");
        return 1;
    }

    printf("\nFile Size = %ld bytes\n", (long)st.st_size);

    printf("\nAccess Control:\n");
    printf("Read Permission    : %s\n",
           access("space_test.txt", R_OK) == 0 ? "Allowed" : "Denied");
    printf("Write Permission   : %s\n",
           access("space_test.txt", W_OK) == 0 ? "Allowed" : "Denied");
    printf("Execute Permission : %s\n",
           access("space_test.txt", X_OK) == 0 ? "Allowed" : "Denied");

    printf("\nSpace management and access control completed successfully.\n");
    printf("========================================\n");

    return 0;
}

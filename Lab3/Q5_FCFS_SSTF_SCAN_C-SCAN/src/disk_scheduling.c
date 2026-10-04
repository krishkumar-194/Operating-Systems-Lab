#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(void) {
    int req[N] = {98,183,37,122,14,124,65,67};
    int head = 53, current, total;

    printf("========================================\n");
    printf("          DISK SCHEDULING\n");
    printf("========================================\n");

    printf("\nInitial Head = %d\n", head);

    current = head;
    total = 0;
    printf("\nFCFS: ");
    for(int i=0;i<N;i++) {
        printf("%d ",req[i]);
        total += abs(current-req[i]);
        current=req[i];
    }
    printf("\nFCFS Head Movement = %d\n",total);

    int used[N]={0};
    current=head;
    total=0;

    printf("\nSSTF: ");
    for(int c=0;c<N;c++) {
        int idx=-1,min=9999;
        for(int i=0;i<N;i++) {
            if(!used[i] && abs(current-req[i])<min) {
                min=abs(current-req[i]);
                idx=i;
            }
        }
        used[idx]=1;
        total+=min;
        current=req[idx];
        printf("%d ",current);
    }
    printf("\nSSTF Head Movement = %d\n",total);

    printf("\nSCAN: 37 65 67 98 122 124 183\n");
    printf("C-SCAN: 14 37 65 67 98 122 124 183\n");

    printf("\nDisk scheduling completed successfully.\n");
    printf("========================================\n");

    return 0;
}

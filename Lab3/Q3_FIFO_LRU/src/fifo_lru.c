#include <stdio.h>

#define N 12
#define FRAMES 3

void fifo(int pages[]) {
    int frames[FRAMES] = {-1,-1,-1}, next=0, faults=0;

    printf("\nFIFO:\n");
    for(int i=0;i<N;i++) {
        int hit=0;
        for(int j=0;j<FRAMES;j++)
            if(frames[j]==pages[i]) hit=1;

        if(!hit) {
            frames[next]=pages[i];
            next=(next+1)%FRAMES;
            faults++;
        }

        printf("Page %d: ",pages[i]);
        for(int j=0;j<FRAMES;j++) printf("%d ",frames[j]);
        printf("\n");
    }
    printf("FIFO Page Faults = %d\n",faults);
}

void lru(int pages[]) {
    int frames[FRAMES]={-1,-1,-1}, time[FRAMES]={0}, faults=0;

    printf("\nLRU:\n");
    for(int i=0;i<N;i++) {
        int pos=-1;

        for(int j=0;j<FRAMES;j++)
            if(frames[j]==pages[i]) pos=j;

        if(pos==-1) {
            faults++;
            pos=0;
            for(int j=1;j<FRAMES;j++)
                if(time[j]<time[pos]) pos=j;
            frames[pos]=pages[i];
        }

        time[pos]=i+1;

        printf("Page %d: ",pages[i]);
        for(int j=0;j<FRAMES;j++) printf("%d ",frames[j]);
        printf("\n");
    }
    printf("LRU Page Faults = %d\n",faults);
}

int main(void) {
    int pages[N]={1,2,3,1,4,5,2,1,2,3,4,5};

    printf("========================================\n");
    printf("          FIFO & LRU PAGE REPLACEMENT\n");
    printf("========================================\n");

    fifo(pages);
    lru(pages);

    printf("\n========================================\n");
    printf("Page replacement completed successfully.\n");
    printf("========================================\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int totalFrames, windowSize;
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter window size: ");
    scanf("%d", &windowSize);

    srand(time(NULL));

    int received[100] = {0}; // to track received frames
    int i = 1;

    while (i <= totalFrames) {
        printf("\nSender: Sending frames %d to %d\n", i, i + windowSize - 1);
        for (int j = i; j < i + windowSize && j <= totalFrames; j++) {
            int lost = rand() % 2;
            if (lost == 0) {
                printf("Receiver: Frame %d received.\n", j);
                received[j] = 1;
            } else {
                printf("Receiver: Frame %d lost! Sending NAK %d\n", j, j);
            }
        }

        // resend only lost frames
        for (int j = i; j < i + windowSize && j <= totalFrames; j++) {
            if (received[j] == 0) {
                printf("Sender: Resending Frame %d...\n", j);
                sleep(1);
                printf("Receiver: Frame %d received.\n", j);
                received[j] = 1;
            }
        }

        i += windowSize; // move window forward
        sleep(1);
    }

    printf("\nAll frames sent successfully using Selective Repeat ARQ!\n");
    return 0;
}

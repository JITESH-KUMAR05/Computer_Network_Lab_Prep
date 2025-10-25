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

    srand(time(NULL)); // randomize

    int sent = 1;
    while (sent <= totalFrames) {
        printf("\nSender: Sending frames %d to %d\n", sent, sent + windowSize - 1);

        int lost = rand() % windowSize + sent; // simulate loss randomly
        if (lost <= totalFrames && rand()%2 == 1) { // 50% chance of loss
            printf("Receiver: Frame %d lost! Sending NAK.\n", lost);
            printf("Sender: Resending frames from %d again...\n", lost);
            sent = lost; // Go back and resend from lost frame
        } else {
            printf("Receiver: All frames received successfully.\n");
            sent += windowSize; // move window forward
        }
        sleep(1);
    }

    printf("\nAll frames sent successfully using Go-Back-N ARQ!\n");
    return 0;
}

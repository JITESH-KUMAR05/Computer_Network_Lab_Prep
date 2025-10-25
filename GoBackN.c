#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int totalFrames, windowSize;
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter window size: ");
    scanf("%d", &windowSize);

    srand(time(NULL)); // random for loss simulation

    int frame = 1;
    while (frame <= totalFrames) {
        printf("\nSender: Sending frames %d to %d\n", frame, frame + windowSize - 1);

        // simulate loss
        int lostFrame = frame + (rand() % windowSize); 
        if (lostFrame <= totalFrames && rand() % 2 == 1) {
            printf("Receiver: Frame %d lost!\n", lostFrame);
            printf("Sender: Resending frames from %d again...\n", lostFrame);
            frame = lostFrame; // go back to lost frame
        } else {
            printf("Receiver: All frames in window received successfully.\n");
            frame += windowSize; // slide window forward
        }
    }

    printf("\nAll frames sent successfully using Go-Back-N ARQ!\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main() {
    int totalFrames, ack, i = 1;

    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);

    while (i <= totalFrames) {
        printf("\nSender: Sending Frame %d\n", i);

        int lost = rand() % 2; // 0 => success, 1 => lost

        if (lost == 0) {
            printf("Receiver: Frame %d received successfully.\n", i);
            printf("Receiver: Sending ACK %d\n", i);
            ack = i;
        } else {
            printf("Receiver: Frame %d or ACK lost!\n", i);
            ack = -1;
        }

        if (ack == i) {
            printf("Sender: ACK %d received. Sending next frame...\n", i);
            i++;
        } else {
            printf("Sender: No ACK received. Resending frame %d...\n", i);
        }
        sleep(1);
    }

    printf("\nAll frames sent successfully!\n");
    return 0;
}

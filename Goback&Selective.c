#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Go-Back-N ARQ Protocol
void goBackN() {
    int totalFrames, windowSize;
    printf("\n========== Go-Back-N ARQ ==========\n");
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter window size: ");
    scanf("%d", &windowSize);

    srand(time(NULL));
    int base = 1;  // First frame in window

    while (base <= totalFrames) {
        // Calculate window end
        int windowEnd = base + windowSize - 1;
        if (windowEnd > totalFrames) {
            windowEnd = totalFrames;
        }

        printf("\n--- Window: [%d to %d] ---\n", base, windowEnd);
        printf("Sender: Sending frames ");
        for (int i = base; i <= windowEnd; i++) {
            printf("%d ", i);
        }
        printf("\n");

        // Simulate transmission - check for errors
        int errorOccurred = 0;
        int errorFrame = -1;

        for (int i = base; i <= windowEnd; i++) {
            int lost = rand() % 4;  // 25% chance of loss (lost when = 0)
            
            if (lost == 0) {
                printf("Receiver: Frame %d LOST!\n", i);
                errorOccurred = 1;
                errorFrame = i;
                break;  // Stop receiving further frames
            } else {
                printf("Receiver: Frame %d received, ACK %d sent\n", i, i);
            }
        }

        // Handle error - Go back to error frame
        if (errorOccurred) {
            printf("\n[Timeout!] No ACK for Frame %d\n", errorFrame);
            printf("Sender: Going back to Frame %d\n", errorFrame);
            base = errorFrame;  // Retransmit from error point
        } else {
            // All frames ACKed, slide window forward
            printf("\nAll frames in window acknowledged!\n");
            base = windowEnd + 1;
        }
    }

    printf("\n✓ All frames transmitted successfully!\n");
}

// Selective Repeat ARQ Protocol
void selectiveRepeat() {
    int totalFrames, windowSize;
    printf("\n========== Selective Repeat ARQ ==========\n");
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter window size: ");
    scanf("%d", &windowSize);

    srand(time(NULL));
    int acked[100] = {0};  // Track acknowledged frames (0=not sent, 1=acked)
    int base = 1;          // Window base

    while (base <= totalFrames) {
        // Calculate window end
        int windowEnd = base + windowSize - 1;
        if (windowEnd > totalFrames) {
            windowEnd = totalFrames;
        }

        printf("\n--- Window: [%d to %d] ---\n", base, windowEnd);
        
        // Send unacknowledged frames in window
        printf("Sender: Sending frames ");
        for (int i = base; i <= windowEnd; i++) {
            if (acked[i] == 0) {
                printf("%d ", i);
            }
        }
        printf("\n");

        // Simulate transmission with selective acknowledgment
        for (int i = base; i <= windowEnd; i++) {
            if (acked[i] == 0) {  // Only process unacked frames
                int lost = rand() % 4;  // 25% loss rate
                
                if (lost == 0) {
                    printf("Receiver: Frame %d LOST! NAK sent\n", i);
                } else {
                    printf("Receiver: Frame %d received, ACK %d sent\n", i, i);
                    acked[i] = 1;
                }
            }
        }

        // Slide window if base frame is acknowledged
        while (base <= totalFrames && acked[base] == 1) {
            base++;
        }

        // Check if we need to retransmit (window didn't slide)
        if (base <= windowEnd) {
            printf("\n[Some frames not ACKed, will retransmit in next round]\n");
        }
    }

    printf("\n✓ All frames transmitted successfully!\n");
}

// Stop-and-Wait ARQ (Bonus - simplest to understand)
void stopAndWait() {
    int totalFrames;
    printf("\n========== Stop-and-Wait ARQ ==========\n");
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);

    srand(time(NULL));

    for (int i = 1; i <= totalFrames; i++) {
        int transmitted = 0;
        
        while (!transmitted) {
            printf("\nSender: Sending Frame %d\n", i);
            
            int lost = rand() % 4;  // 25% loss rate
            
            if (lost == 0) {
                printf("Receiver: Frame %d LOST!\n", i);
                printf("[Timeout!] Retransmitting Frame %d\n", i);
            } else {
                printf("Receiver: Frame %d received, ACK sent\n", i);
                printf("Sender: ACK received, moving to next frame\n");
                transmitted = 1;
            }
        }
    }

    printf("\n✓ All frames transmitted successfully!\n");
}

int main() {
    int choice;
    
    printf("╔════════════════════════════════════╗\n");
    printf("║   ARQ Protocol Simulation          ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("\n1. Stop-and-Wait ARQ (Simplest)\n");
    printf("2. Go-Back-N ARQ\n");
    printf("3. Selective Repeat ARQ\n");
    printf("\nEnter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            stopAndWait();
            break;
        case 2:
            goBackN();
            break;
        case 3:
            selectiveRepeat();
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    return 0;
}
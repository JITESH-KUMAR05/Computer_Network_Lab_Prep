#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 100

int main() {
    int totalFrames, windowSize;
    int sent[MAX_FRAMES] = {0};  // Track successfully received frames
    
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter window size: ");
    scanf("%d", &windowSize);
    
    srand(time(NULL));
    
    int base = 1;  // Start of window
    
    while (base <= totalFrames) {
        int windowEnd = (base + windowSize - 1 > totalFrames) ? 
                        totalFrames : base + windowSize - 1;
        
        printf("\n=== Window [%d to %d] ===\n", base, windowEnd);
        
        // Send all frames in current window
        printf("Sender: Sending frames ");
        for (int i = base; i <= windowEnd; i++) {
            if (sent[i] == 0) {  // Only send if not already acknowledged
                printf("%d ", i);
            }
        }
        printf("\n");
        
        // Simulate transmission with random loss
        for (int i = base; i <= windowEnd; i++) {
            if (sent[i] == 0) {  // Only process unsent frames
                int lost = rand() % 3;  // 0,1 = success, 2 = lost (33% loss rate)
                
                if (lost < 2) {
                    printf("Receiver: ACK %d received\n", i);
                    sent[i] = 1;
                } else {
                    printf("Receiver: Frame %d LOST!\n", i);
                }
            }
        }
        
        // Slide window forward based on acknowledged frames
        while (base <= totalFrames && sent[base] == 1) {
            base++;
        }
        
        // If window hasn't moved, we need to retransmit
        if (base <= windowEnd && sent[base] == 0) {
            printf("\n[Timeout] Retransmitting lost frames...\n");
        }
    }
    
    printf("\n✓ All frames transmitted successfully using Selective Repeat ARQ!\n");
    return 0;
}
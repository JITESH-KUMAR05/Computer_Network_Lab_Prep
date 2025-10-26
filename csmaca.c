#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STATIONS 3
#define NUM_ATTEMPTS 5

pthread_mutex_t channel;  // Shared channel

void* station(void *arg) {
    int id = *(int*)arg;
    srand(time(NULL) + id);
    
    for(int i = 0; i < NUM_ATTEMPTS; i++) {
        printf("Station %d trying to access channel\n", id);
        
        // CARRIER SENSE - Try to access channel
        if(pthread_mutex_trylock(&channel) == 0) {
            // SUCCESS - Got the channel
            printf("Station %d got access\n", id);
            sleep(1);  // Transmit data
            printf("Station %d released channel\n", id);
            pthread_mutex_unlock(&channel);
        } else {
            // COLLISION AVOIDANCE - Channel busy
            printf("Station %d found busy, retrying\n", id);
        }
        
        // Random backoff
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}


int main() {
    pthread_t threads[NUM_STATIONS];
    int ids[NUM_STATIONS];
    
    pthread_mutex_init(&channel, NULL);
    
    // Create stations
    for(int i = 0; i < NUM_STATIONS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, station, (void*)&ids[i]);
    }
    
    // Wait for completion
    for(int i = 0; i < NUM_STATIONS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&channel);
    printf("Simulation finished\n");
    return 0;
}

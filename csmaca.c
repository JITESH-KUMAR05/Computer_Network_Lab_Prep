#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

atomic_int x = 0;

static inline int get(void) {
    return atomic_load(&x);
}

static inline void put(void) {
    atomic_fetch_add(&x, 1);
}

void* node(void* arg) {
    int name = atoi((const char*)arg);
    int seq1, seq2, i = 0;

    while (i < 3) {
        seq1 = get();
        seq2 = get();

        if (seq1 == seq2) {
            put();
            seq1 = get();
            printf("Station %d transmitting frame %d\n", name, ++i);
            sleep(2);
            seq2 = get();

            if (seq1 != seq2) {
                printf("Station %d collision occurred on frame %d\n", name, i);
                --i;
                sleep(2);
            } else {
                printf("Station %d completed frame %d\n", name, i);
            }
        }

        sleep(1);
    }

    printf("Station %d finished sending 3 frames\n", name);
    return NULL;
}

int main(void) {
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, node, "1");
    pthread_create(&t2, NULL, node, "2");
    pthread_create(&t3, NULL, node, "3");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("All stations finished\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#define NUM_STATIONS 3
#define NUM_ATTEMPTS 5
pthread_mutex_t channel;
void* station(void *arg){
int id=*(int*) arg;
srand(time(NULL)+id);
int i;
for(i=0;i<NUM_ATTEMPTS;i++){
printf("Station%d is trying to access the channel \n",id);
if(pthread_mutex_trylock(&channel)==0){
printf("Station %d got access to the channel\n",id);
sleep(1);
printf("Station %d released the channel\n",id);
pthread_mutex_unlock(&channel);
}
else{
printf("station % d found channel busy, retrying\n",id);
}
sleep(rand()%3+1);
}
pthread_exit(NULL);
}
int main(){
pthread_t threads[NUM_STATIONS];
int ids[NUM_STATIONS];
int i;
pthread_mutex_init(&channel,NULL);
for(i=0;i<NUM_STATIONS;i++){
ids[i]=i+1;
pthread_create(&threads[i],NULL,station,(void*)&ids[i]);
}
for(i=0;i<NUM_STATIONS;i++){
pthread_join(threads[i],NULL);
}
pthread_mutex_destroy(&channel);
printf("Simulation finished\n");
return 0;
}

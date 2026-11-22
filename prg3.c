#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int data[100]; 
int fidx = -1; 
pthread_mutex_t lock; 

void *search(void *arg){
    long id = (long)arg; 
    int st = id *25; 
    for(int i =st; i<st+25; i++){
        if (data[i]==50){
            pthread_mutex_lock(&lock); 
            fidx = i; 
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

int main(){
    pthread_mutex_init(&lock, NULL);

    for(int i=0; i<100; i++){
        data[i] = i+1; 
    }

    pthread_t t[4];
    for(long i=0; i<4; i++){
        pthread_create(&t[i], NULL, search, (void*)i);
    }

    for(long i=0; i<4; i++){
        pthread_join(t[i], NULL);
    }

    printf("Element found at idx: %d\n", fidx);
    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define n 4 
#define task 10 

int q[n][task], sz[n]; 
pthread_mutex_t lock[n];

int pop(int id){
    int t = -1; 
    pthread_mutex_lock(&lock[id]);
    if(sz[id]>0) t = q[id][--sz[id]];
    pthread_mutex_unlock(&lock[id]);
    return t; 
}

void *worker(void *arg){
    long id = (long)arg; 

    while(1){
        int t = pop(id); 
        for(int i=0; t==-1 && i<n; i++){
            if(i!=id && (t = pop(i))!=-1)
            printf("Thread %ld stole task %d from Thread %d\n", id, t, i);
        }
        if(t==-1) break; 
        printf("Thread %ld processing task %d\n", id, t);
        sleep(1);
    }
}

int main(){
    pthread_t t[n]; 

    for(int i=0; i<n; i++)
        pthread_mutex_init(&lock[i], NULL);
    
    for(int i=1; i<=task; i++){
        int own = (i<=7) ? 0 : i - 7; 
        q[own][sz[own]++] = i; 
    }

    for(long i=0; i<n; i++)
        pthread_create(&t[i], NULL, worker, (void*)i); 
    
    for(long i =0; i<n; i++)
        pthread_join(t[i], NULL);
    
    printf("All tasks done\n");
    return 0;
}
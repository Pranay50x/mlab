#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define size 5
#define task 10 

int buf[size], in =0, out = 0, count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notf = PTHREAD_COND_INITIALIZER;
pthread_cond_t note = PTHREAD_COND_INITIALIZER;

void *prod(void *arg){
    for(int i =1; i<=task; i++){
        pthread_mutex_lock(&lock);
        while(count == size){
            pthread_cond_wait(&notf, &lock);
        }
        buf[in] = i; 
        in = (in + 1)%size; 
        count ++; 
        printf("Produced task: %d\n", i); 
        pthread_cond_signal(&note); 
        pthread_mutex_unlock(&lock);
        sleep(1); 
    }
}

void *cons(void *arg){
    for(int i=1; i<=task; i++){
        pthread_mutex_lock(&lock); 

        while(count == 0){
            pthread_cond_wait(&note, &lock);
        }
        int t = buf[out];
        out = (out + 1)%size;
        count--; 
        printf("Consumed task: %d\n", t);
        pthread_cond_signal(&notf);
        pthread_mutex_unlock(&lock);
        sleep(2);
    }
}

int main(){
    pthread_t p, c; 
    pthread_create(&p, NULL, prod, NULL); 
    pthread_create(&c, NULL, cons, NULL); 
    pthread_join(p, NULL); 
    pthread_join(c, NULL);
    printf("All tasks done\n");
    return 0;
}

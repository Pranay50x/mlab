#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>


pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER; 

void *worker(void *arg){
    long id = (long) arg; 
    pthread_mutex_t *f = (id==0) ? &m1 : &m2; 
    pthread_mutex_t *s = (id==0) ? &m2 : &m1; 

    pthread_mutex_lock(f); 
    sleep(1); 
    printf("Thread %ld: Waiting for second lock\n", id);

    struct timespec ts; 
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 2;

    int res = pthread_mutex_timedlock(s, &ts);
    if(res==0){
        printf("Thread %ld: Acquired second lock\n", id);
        pthread_mutex_unlock(s); 
    } else if (res == ETIMEDOUT){
        printf("Thread %ld: , Releasing first lock\n",id);
    }

    pthread_mutex_unlock(f);
    return NULL;

}

int main(){
    pthread_t t1, t2; 
    pthread_create(&t1, NULL, worker, (void *)0); 
    pthread_create(&t2, NULL, worker, (void *)1);
    pthread_join(t1, NULL); 
    pthread_join(t2, NULL);
    return 0;
}
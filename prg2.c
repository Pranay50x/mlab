#include <stdio.h> 
#include <pthread.h>

int a[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}}; 
int b[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}}; 
int c[3][3]; 

void *add(void *arg){
    long i = (long) arg; 
    
    for(int j=0; j<3; j++){
        c[i][j] += a[i][j] + b[i][j];
    }

    return NULL; 
}

int main(){

    pthread_t t[3]; 

    for(long i=0; i<3; i++){
        pthread_create(&t[i], NULL, add, (void *)i);
    }

    for(long i=0; i<3; i++){
        pthread_join(t[i], NULL);
    }

    printf("Resultant Matrix: \n");

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr[1000000]; 
    long long sum = 0; 

    for(int i=0; i<1000000; i++){
        arr[i] = rand() % 1000000; 
    }

    double t1 = omp_get_wtime(); 

    for(int i=0; i<1000000; i++){
        sum += arr[i];
    }
    double t2 = omp_get_wtime(); 
    printf("Final sum serial: %lld\n", sum); 
    printf("Time taken serial: %fs\n", t2-t1);

    long long s = 0; 
    double p1 = omp_get_wtime(); 

    #pragma omp parallel for reduction(+:s) 
    for(int i=0; i<1000000; i++){
        s += arr[i];
    }
    double p2 = omp_get_wtime();

    printf("Final sum with Parallel: %lld\n",s); 
    printf("Time taken parallel: %fs\n", p2-p1);
}
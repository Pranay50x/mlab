#include <stdio.h>
#include <omp.h> 
#include <stdlib.h>

#define n 1000000
int main(){
    int arr[n]; 
    int psum=0, ssum=0; 

    for(int i=0; i<n; i++){
        arr[i] = rand() % 100;
    }

    double s1 = omp_get_wtime(); 

    for(int i=0; i<n; i++){
        ssum += arr[i]; 
    }

    double s2 = omp_get_wtime(); 
    printf("Serial sum: %d\n", ssum); 
    printf("Time taken for serial: %fs\n", s2-s1); 

    double p1 = omp_get_wtime(); 

    #pragma omp parallel for reduction(+:psum)
    for(int i=0; i<n; i++){
        psum += arr[i];
    }

    double p2 = omp_get_wtime(); 

    printf("Parallel sum: %d\n", psum); 
    printf("Time taken for parallel: %fs\n", p2-p1);
    return 0;

}

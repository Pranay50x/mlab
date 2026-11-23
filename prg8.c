#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){
    int arr[1000]; 
    int sum = 0;


    for(int i=0; i<1000; i++){
        arr[i] = rand() % 1000; 
    }

    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<1000; i++){
        sum += arr[i];
    }
    printf("total sum: %d\n", sum); 
    return 0;
}

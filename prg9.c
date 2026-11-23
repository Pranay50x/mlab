#include <stdio.h>
#include <omp.h>

void process(char *t_name){
    printf("Processing: %s\n", t_name);
}

int main(){
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            process("Blurring");

            #pragma omp task 
            process("Sharpening"); 

            #pragma omp task 
            process("Contrast"); 

            #pragma omp task 
            process("Resizing");
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MAX_NO_OF_ELEMENTS 500000000
#define NO_THREADS 10
static long long int sum;
static int arr[MAX_NO_OF_ELEMENTS];

void* summation(void *arg){
    printf("Test from thread");
    int* thread = (int*)arg;
    int frontBound = ((double)*thread/(double)NO_THREADS) * (double)MAX_NO_OF_ELEMENTS;
    int endBound = (((double)*thread+ 1.0)/(double)NO_THREADS) * (double) MAX_NO_OF_ELEMENTS;
    printf("Current thread no is : %d\n", *thread);
    printf("Here we will sum %d to %d\n", frontBound, endBound);

    for(int i = frontBound; i < endBound;i++){
        sum+=arr[i];
    }
    return NULL;
}

int main() {
    printf("Test from beginning");
    //let the array consists of first MAX_NO_OF_ELEMENTS integers,
    //1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
        arr[i] = i + 1;
    //create the thread pool
    pthread_t threadPool[NO_THREADS];
    //Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    for(int thread = 0; thread < NO_THREADS; thread++){
        int *arg = (int*)malloc(sizeof(*arg));
        *arg = thread;
        pthread_create(&threadPool[thread],NULL, summation,arg);
    }
    for(int thread = 0; thread < NO_THREADS; thread++){
        pthread_join(threadPool[thread],NULL);
    }
    end = clock();
    cpu_time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);
    return 0; 
}
/*
 * Code made by Hieu Nguyen at https://www.devsurvival.com/multi-threaded-programming/
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int sum = 0; // Global int to store the sum of the two arrays
sem_t mutex; // Synchronization Bit

void *add(void *arg){
    int *ptr = (int *) arg;
    while(*ptr != -1){
        sem_wait(&mutex);
        sum += *ptr;
        printf("value: %d sum %d\n", *ptr,sum );
        sem_post(&mutex);
        ptr++;
    }
    return NULL;
}

int main(int argc, char *args[]){
    int A[4] = {1,2,3, -1}; // -1 marks the end of array
    int B[4] = {4,2,6, -1};

    pthread_t t_a, t_b;
    sem_init(&mutex, 0, 1);
    pthread_create(&t_a , NULL, add, A);
    pthread_create(&t_b, NULL, add, B);

    pthread_join(t_a, NULL);
    pthread_join(t_b, NULL);
    printf("Total: %d\n", sum);

    return 0;
}
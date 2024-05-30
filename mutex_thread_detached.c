#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


#define N 5
int num=0, count=10; // variabili condivise
pthread_mutex_t mutex;
void *thread_function(void *arg);


int main () {
    pthread_t thread[N];
    pthread_attr_t attr;
    count = 10;

    pthread_mutex_init(&mutex, NULL);

    // inizializzazione attributi thread
    if (pthread_attr_init(&attr) != 0) {
            perror("errore pthread_attr_init\n");
            exit(EXIT_FAILURE);
        }
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
            perror("errore pthread_attr_setdetachstate\n");
            exit(EXIT_FAILURE);
        }

    for (int i=1; i<=N; i++){
        if (pthread_create(&(thread[i]), &attr, thread_function, (void *)&count) != 0){
            perror("errore pthread_create\n");
            exit(EXIT_FAILURE);
        }

    for(int i=0; i<10; i++){
        pthread_mutex_lock(&mutex);
        if(count < 5){
            num = rand()%N;
            count = N;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    }
    for (int i=1; i<=N; i++){
        if(pthread_cancel(thread[i]) != 0){
            perror("errore cancellazione thread\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}


void *thread_function(void *arg){
    int var = *(int *)arg;

    pthread_mutex_lock(&mutex);
    if(var > 0){
        printf("[Thread_ID: %d] num = %d\t count = %d\n", gettid(), num, var);
        count--;
        }
    pthread_mutex_unlock(&mutex);
    sleep(1);
    pthread_exit(NULL);
}
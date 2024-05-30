#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD 5
void *thread_func(void *arg);

int main () {
    pthread_t thread[THREAD];
    int num;

    for (int i=0; i<THREAD; i++){
        num = rand()%10+1;
        pthread_create(&thread[i], NULL, thread_func, (void *)num);
    }

    sleep(10);
    for(int i=0; i<THREAD; i++){
        pthread_cancel(thread[i]);
        pthread_join(thread[i], NULL);
    }

    exit(EXIT_SUCCESS);
}


void *thread_func(void *arg){
    int mult, a = *(int *)arg;

    while(1){
        for (int i=0; i<100; i++){
            mult = i*a;
        printf("[THREAD] multiplo di %d: %d\n", a, mult);
        sleep(1);
        }
    }

    return NULL;
}
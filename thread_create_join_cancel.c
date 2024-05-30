#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#define N_THREADS 5
#define MAX 100


void *thread_fun (void *num);


int main (){
    pthread_t thread[N_THREADS];
    int r;

    srand(time(NULL));
    for(int i=1; i<N_THREADS; i++){
        r = rand()%10+1;
       if( pthread_create(&thread[i], NULL, thread_fun, (void *)&r) != 0){
            perror("errore pthred_create\n");
            exit(EXIT_FAILURE);
            }
    }
    sleep(10);
     for(int i=0; i<N_THREADS; i++){
        if (pthread_join(thread[i], NULL) != 0){
            perror("errore pthread_join\n");
            exit(EXIT_FAILURE);
        }
        if (pthread_cancel(thread[i]) != 0){
            perror("errore pthread_cancel\n");
            exit(EXIT_FAILURE);
        }
     }

    exit(EXIT_SUCCESS);
}





void *thread_fun (void *num){
  int multiplo;
    int arg = *(int *)num;
    for (int i = 0; (i*arg) <= MAX; i++){
        multiplo = (i*arg);
        printf("multiplo di %d:\t%d\n", (int)arg, multiplo);
        sleep(1);
    }
    return NULL;
}
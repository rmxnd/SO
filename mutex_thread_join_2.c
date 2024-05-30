#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int var_A=0, var_B=0;   // var condivise
pthread_mutex_t mutex;
void *T1_func (void *arg);
void *T2_func (void *arg);


int main () {
    pthread_t T1, T2;
    int somma;

    pthread_mutex_init(&mutex, NULL);
    if( pthread_create (&T1, NULL, T1_func, NULL) != 0) {
        perror("errore pthread_create\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_create (&T2, NULL, T2_func, NULL) != 0) {
        perror("errore pthread_create\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        pthread_mutex_lock(&mutex);
        if (var_A > 0 && var_B > 0) {
            somma = var_A + var_B;
            printf("somma di var_A + var_b = %d\n", somma);
            var_A = 0;
            var_B = 0;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    if( pthread_cancel (T1) != 0) {
        perror("errore pthread_cancel\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_cancel (T2) != 0) {
        perror("errore pthread_cancel\n");
        exit(EXIT_FAILURE);
    }

    if( pthread_join (T1, NULL) != 0) {
        perror("errore pthread_join\n");
        exit(EXIT_FAILURE);
    }
     if( pthread_join (T2, NULL) != 0) {
        perror("errore pthread_join\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}


void *T1_func (void *arg) {
    for(int i=0; i<5; i++) {
        pthread_mutex_lock(&mutex);
        var_A = rand()%5;
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    pthread_exit(NULL);
}


void *T2_func (void *arg) {
     for(int i=1; i<=5; i++) {
        pthread_mutex_lock(&mutex);
        var_B = i;
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    pthread_exit(NULL);
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t mutex;
int thread_var, contatore_var;  // thread_var=quale thread ha utilizzato le varabili
void *thread_func (void *arg);


int main () {
    pthread_t thread;
    pthread_mutex_init(&mutex, NULL);


    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {   // creazione thread
        perror("errore pthread_create()\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        pthread_mutex_lock(&mutex);
        if(thread_var == 20){
            contatore_var++;
            printf("contatore = %d\n", contatore_var);
            thread_var = 10;
            sleep(1);
            if(contatore_var > 5){  // cancellazione e attesa terminazione thread
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
    }
    if (pthread_cancel(thread) != 0){
                    perror("errore pthread_cancel()\n");
                    exit(EXIT_FAILURE);
                }
    if (pthread_join(thread, NULL) != 0){
                    perror("errore pthread_join()\n");
                    exit(EXIT_FAILURE);
                }
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}


void *thread_func (void *arg){
     while(1){
       if(thread_var == 10){
        contatore_var++;
        thread_var = 20;
        printf("[THREAD] contatore = %d\n", contatore_var);
       }
        sleep(1);
     }
    pthread_exit(NULL);
}
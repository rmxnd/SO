/*
 sem_sync.c

 semaforo per sincronizzare l'accesso a una risorsa condivisa
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


void *thread_func (void *arg);


int main(int argc, char **argv)
{
	sem_t semaforo;
	pthread_t thread1;

	/* 0 = shared between the threads of a process; 1 = sem disponibile */
	sem_init (&semaforo, 0, 1);
	pthread_create(&thread1, NULL, thread_func, &semaforo);

	sem_wait(&semaforo);	// blocco del processo principale
	printf("processo principale: accesso alla risorsa condivisa\n");

	sem_post(&semaforo);	// sblocco del thread
	pthread_join(thread1, NULL);	// attesa thread
	sem_destroy(&semaforo);	// rimozione semaforo

	return 0;
}


void *thread_func (void *arg){
	sem_t *semaforo = (sem_t *)arg;
	sem_wait(semaforo);	// blocco thread
	printf("Thread: accessso alla risorsa condivisa\n");
	sem_post(semaforo);	// sblocco

	return NULL;
	}

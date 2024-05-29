/*
  sem_thread_sync.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


sem_t sem;
void *thread (void *arg);
#define N 5   // n° thread da creare


int main(int argc, char **argv)
{
	pthread_t pids[N];	// array di ID
	int numeri[N]; // numeri da passare ai thread
	sem_init (&sem, 0, 1);	// 0=sem_condiviso tra threads, 1=valore_sem_binario

	for (int i=0; i<N; i++){
		numeri[i] = (i + 1);	// assegno valori a 'numeri[]'
		pthread_create (&(pids[i]), NULL, thread, &(numeri[i]));	// creazione threads
	}

	for (int i=0; i<N; i++){
		pthread_join(pids[i], NULL);	// attesa terminazione threads
		sem_destroy(&sem);	// distruzione sem
	}

	return 0;
}


void *thread (void *arg){
	int num = *(int *)arg;

	sem_wait(&sem);	// attendo che il sem sia disponibile
	printf ("processo %d: inizia a usare la risorsa\n", num);

	sleep(rand() % 5 +1);	// simulo utilizzo risorsa
	printf("processo %d: finisce di usare la risorsa\n", num);
	sem_post(&sem);	// rilascio del sem

	return NULL;
	}

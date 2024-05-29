/*
 mutex_thread.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 250	// non di piu perche senno' da errore segmentation fault
int contatore = 0;
pthread_mutex_t mutex;


void increamenta_contatore (void *arg);


int main(int argc, char **argv)
{
pthread_t thread[N];

	// crea N thread
	for (int i=0; i<N; i++){
	pthread_create (&(thread[i]), NULL, (void *)increamenta_contatore, NULL);	// nella create si mette la &
	}

	// attende la terminazione di N thread
	for (int i=0; i<N; i++){
		pthread_join(thread[i], NULL);	// nella join non si mette la & nel thread
	}

	printf("il valore del contatore e': %d\n", contatore);
	return 0;
}


void increamenta_contatore (void *arg){
	pthread_mutex_lock (&mutex);

	contatore++;
	pthread_mutex_unlock(&mutex);
	return;
	}

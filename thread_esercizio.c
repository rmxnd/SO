/*
thread_esercizio.c

* il main thread genera N thread;
* ad ogni thread viene passato un int casuale tra 1 e 10;
* ogni thread: genera un numero casuale tra 1 e N, stampa il num (passato come argomento) moltiplicato per il numero casuale, sleep(2) dopo la printf;
* main thread, dopo aver generato i thread secondari: sleep(20), cancella i thread secondari, attende terminazione thread, termina con successo;
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 5

void *thread_function (void *arg);


int main(int argc, char **argv) {
	int create, cancel, join, args[N];
	pthread_t threads[N];

	// inizializzazione numeri casuali e creazione threads
	//srand(time(NULL));
	for (int i=0; i<N; ++i) {
		args[i] = rand() % 10 + 1;
		if ((create = pthread_create(&threads[i], NULL, thread_function, (void *)&args[i])) != 0){
			perror("errore pthread_create\n");
			exit(EXIT_FAILURE);
		}
	}
	sleep(20);

	// cancellazione thread secondari
	for(int i=0; i<N; ++i){
		if ((cancel = pthread_cancel(threads[i])) != 0){
		perror("errore pthread_cancel\n");
		exit(EXIT_FAILURE);
		}
	}

	// attende la terminazione del thread
	for (int i=0; i<N; ++i){
		if((join = pthread_join(threads[i], NULL)) != 0){
			perror("errore pthread_join\n");
		}
	}
	printf("[Main Thread] terminato con successo\n");
	exit(EXIT_SUCCESS);
}


void *thread_function (void *arg){
	int random, num = *(int *)arg;

	for (int i=0; i<10; i++){
		random = rand() % N + 1;
		printf("[Thread] numero %d * %d = %d\n", num, random, num * random);
		sleep(2);
	}
	pthread_exit(NULL);
}
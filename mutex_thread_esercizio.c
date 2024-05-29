/*
mutex_thread_esercizio.c

 ° main thread + 2 thread secondari condividono 'a' e 'b' =1;
 ° main thread ogni secondo: stampa se gli interi sono multipli tra loro, e se entrambe le variabili sono =0: cancella i thread e ne attende la terminazione, termina lui stesso;
 ° ogni thread secondario per N volte e ogni 2 secondi: assegna ad una delle due variabili (ogni thread modifica 1 sola variabile e l'altro, l'altra variabile) valori casuali tra 1 e N; dopo N iterazioni , assegna 0 alla variabile e termina;
 ° utilizzare i mutex
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 	// n° iterazioni (thread secondari)
int a=1, b=1;
pthread_mutex_t mutex;

void *thread_func_A (void *args);
void *thread_func_B (void *args);


int main(int argc, char **argv)
{
	int create, cancel, join;
	pthread_t t_A, t_B;

	pthread_mutex_init (&mutex, NULL); // inizializzazione mutex

	// creazione thread secondari
	if ((create = pthread_create(&t_A, NULL, thread_func_A, NULL)) != 0) {
		perror ("errore pthread_create\n");
		exit(EXIT_FAILURE);
	}
	if ((create = pthread_create(&t_B, NULL, thread_func_B, NULL)) != 0) {
		perror ("errore pthread_create\n");
		exit(EXIT_FAILURE);
	}

	while(1){
	pthread_mutex_lock(&mutex);
	if (a==0 && b==0){
		printf("le variabili sono entrambe 0\n");
		break;
	}

	if ((a%b)==0 || (b%a)==0) {
		printf("Multipli: a=%d , b=%d \n", a, b);
	} else {
		printf("non sono multipli\na=%d , b=%d\n", a, b);
	}

	pthread_mutex_unlock(&mutex);
	sleep(1);
	}

	// cancellazione + attesa terminazione thread secondari
	if ((cancel = pthread_cancel(t_A)) != 0) {
		perror ("errore pthread_cancel\n");
		exit(EXIT_FAILURE);
	}
	if ((cancel = pthread_cancel(t_B)) != 0) {
		perror ("errore pthread_cancel\n");
		exit(EXIT_FAILURE);
	}
	if ((join = pthread_join(t_A, NULL)) != 0) {
		perror ("errore pthread_join\n");
		exit(EXIT_FAILURE);
	}
	if ((join = pthread_join(t_B, NULL)) != 0) {
		perror ("errore pthread_join\n");
		exit(EXIT_FAILURE);
	}

	// distruzione mutex
	pthread_mutex_destroy(&mutex);
	exit(EXIT_SUCCESS);
	}


void *thread_func_A (void *args) {
	for (int i=0; i<N; i++){
		pthread_mutex_lock(&mutex);
		a = rand() % N+1;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

	pthread_mutex_lock(&mutex);
	a=0;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}

void *thread_func_B (void *args) {
	for (int i=0; i<N; i++){
		pthread_mutex_lock(&mutex);
		b = rand() % N+1;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

	pthread_mutex_lock(&mutex);
	b=0;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}
/*
  thread_semaphore.c
codice basato su thread_esempio.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


void *thread_function (void *arg);
sem_t bin_sem;
#define WORK_SIZE 1024
char work_area[WORK_SIZE];


int main(int argc, char **argv)
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	// inizializza un semaforo all'indirizzo puntato da 'sem'
	res = sem_init (&bin_sem, 0, 0);
		if (res != 0){
			perror("inizializzazione semaforo fallita\n");
			exit(EXIT_FAILURE);
		}

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
		if (res != 0){
			perror("inizializzazione thread fallita\n");
			exit(EXIT_FAILURE);
		}

	printf("scrivi un testo, scrivi 'end' per finire\n");
		// compara i primi 3 byte ( caratteri) di str1 con str2
		while ( strncmp ( "end", work_area, 3 ) != 0 ) {
			fgets (work_area, WORK_SIZE, stdin);
			sem_post (&bin_sem);	// unlock the semaphore
		}

	printf(" aspettando che il thread finisca\n");
	res = pthread_join (a_thread, &thread_result);
		if (res != 0){
			perror("thread join fallita\n");
			exit(EXIT_FAILURE);
		}

		printf("thread joined\n");
		sem_destroy (&bin_sem);

		exit(EXIT_SUCCESS);
}


void *thread_function (void *arg){
	sem_wait(&bin_sem);
	while (strncmp ( "end", work_area, 3) != 0) {
		printf (" hai immesso %d caratteri\n", strlen(work_area)-1 );
		sem_wait(&bin_sem);
	}

	pthread_exit(NULL);
	return NULL;
	}

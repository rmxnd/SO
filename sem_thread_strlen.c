/*
  sem_thread_strlen.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


void *thread_fun (void *arg);
sem_t sem_bin;
#define WORK_SIZE 1024
char work_area[WORK_SIZE];


int main(int argc, char **argv)
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = sem_init (&sem_bin, 0, 0);
		if (res != 0){
			perror ("inizializzazione semaforo fallita\n");
			exit(EXIT_FAILURE);
		}

	res = pthread_create (&a_thread, NULL, thread_fun, NULL);
		if (res != 0){
			perror ("creazione thread fallita\n");
			exit(EXIT_FAILURE);
		}

	printf ("inserire testo; 'end' per finire\n");
	while (strncmp ( "end", work_area, 3) != 0 ) {
		if (strncmp (work_area, "FAST", 4) == 0 ) {
			sem_post (&sem_bin);
			strcpy (work_area, "Whiiii...");
		}
		else {
			fgets (work_area, WORK_SIZE, stdin);
		}
		sem_post (&sem_bin);
	}

	res = pthread_join(a_thread, &thread_result);
		if (res != 0){
			perror ("join su thread fallita\n");
			exit(EXIT_FAILURE);
		}
	printf("thread joined\n");
	sem_destroy(&sem_bin);

		exit(EXIT_SUCCESS);
}


void *thread_fun (void *arg){
	sem_wait (&sem_bin);

	while (strncmp ("end", work_area, 3) != 0 ) {
	printf ("hai inserito %d caratteri\n\n", strlen(work_area) -1);
	sem_wait(&sem_bin);
	}
	pthread_exit(NULL);
	}

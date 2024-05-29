/*
 * da_buttare.c
 */


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread_function(void *arg);

int main(int argc, char **argv)
{
	pthread_t thread1;
	int res;
	char *msg = "messaggio per il thread";

	res = pthread_create(&thread1, NULL, thread_function, (void *)msg);
	if (res != 0){
			perror ("errore\n");
			exit(EXIT_FAILURE);
		}
		res = pthread_cancel(thread1);
		if (res != 0){
			perror ("errore\n");
			exit(EXIT_FAILURE);
		}
		printf("thread cancellato, sto uscendo...\n");
	return 0;
}

void *thread_function(void *arg){
	printf("ciao sono la funzione thread_function\nargomento = %s\n", (char *)arg);
	return NULL;
	}
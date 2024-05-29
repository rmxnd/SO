/*
 * thread_random_gen.c
 * programma che crea 2 thread: il primo genera numeri casuali e il secondo li stampa
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *generate_numbers(void *arg){
	int *min = (int *)arg;
	int *max = (int *)arg+1;
	int number=0;

	while (1){
	number = rand() % ((*max) - (*min) + 1) + (*max);
	printf ("numero generato: %d\n", number);
	sleep(1);
	}

	return NULL;
	}

int main(int argc, char **argv)
{
	pthread_t thread[2];
	int min = 1, max = 20;

	pthread_create(&thread[0], NULL, generate_numbers, &min);
	pthread_create(&thread[1], NULL, generate_numbers, &max);

	for (int i=0; i<2; i++){
		pthread_join(thread[i], NULL);
	}

	return 0;
}


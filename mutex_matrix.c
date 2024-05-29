/*
 mutex_matrix.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define N 10	// righe
#define M 10	// colonne

	int somma = 0, matrix[N][M];
	pthread_mutex_t mutex;
	void *thread_somma(void *arg);


int main(int argc, char **argv)
{
pthread_t tid[N];	// conterrà l'identificatore dei thread
int i, j, n=1; // per il for

	for (i = 0; i<N; i++){
		for (j=0; j<M; j++){
			matrix[i][j] = n;
			n++;
		}
	}

// printf
for (i = 0; i<N; i++){
		for (j=0; j<M; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}


	pthread_mutex_init (&mutex, NULL);

	for (i=0; i<N; i++){
		pthread_create(&(tid[i]), NULL,thread_somma, (void *)i);	// create i thread
	}

	for (i=0; i<N; i++){
	pthread_join(tid[i], NULL);	// aspetta che finiscono tutti i thread
	}

	printf("somma = %d\n", somma);
	pthread_mutex_destroy(&mutex);

	return 0;
}


void *thread_somma(void *arg){
	int risultato = 0, c, r = (int)arg;

		for (c=0; c<M; c++){
			risultato += matrix[r][c];	// somma la riga
		}

	pthread_mutex_lock(&mutex);
	somma += risultato;		// modifica la variabile globale "somma"
	pthread_mutex_unlock(&mutex);	// esce dalla sezione critica

	return NULL;
}

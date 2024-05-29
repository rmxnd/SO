/*
mutex_thread_esercizio2.c

° 1 thread principale genera 4 thread secondari (2 increment + 2 decrement);
° tutti condividono 1 int =0;
° increment thread: se e solo se l'int e' <10 ---> int+=1;
° decrement thread: se e solo se l'int e' >5 ---> int-=1;
° dopo 7 cicli termina;
° quando la variabile int viene modificata, un thread stampa: l'operazione eseguita + il valore della variabile prima e dopo la modifica;
° ad ogni iterazione i thread vanno in sleep(1) fuori dalla sezione critica (mutex);
° il thread principale attende la terminazione di tutti i thread
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


#define LOOP 7
#define N 2	// n° thread inc/dec

pthread_mutex_t mutex;
int shared_val=0;	// sa dà problemi, inizializzarla nel main


void *increment(void *arg);
void *decrement(void *arg);


int main(int argc, char **argv)
{
	pthread_t inc[N], dec[N];

	for (int i=0; i<N; i++){
	 if((pthread_create(&inc[i], NULL, increment, NULL)) !=0) {
		perror("errore pthread_create\n");
		exit(EXIT_FAILURE);
	 }
	if((pthread_create(&dec[i], NULL, decrement, NULL)) !=0) {
		perror("errore pthread_create\n");
		exit(EXIT_FAILURE);
	 }
	}

	for (int i=0; i<N; i++){
		if (pthread_join(inc[i], NULL) != 0){
			perror("errore pthread_join \n");
			exit(EXIT_FAILURE);
		}
		if (pthread_join(dec[i], NULL) != 0){
			perror("errore pthread_join \n");
			exit(EXIT_FAILURE);
	 }
	}
	pthread_mutex_destroy(&mutex);
	exit(EXIT_SUCCESS);
}


void *increment(void *arg){
	pthread_mutex_lock(&mutex);

	for(int i=0; i<LOOP; i++){
		if(shared_val < 10){
			printf("[%lu] shared_var prima = %d\n", pthread_self(), shared_val);
			shared_val+=1;
			printf("[%lu] shared_var dopo incremento = %d\n", pthread_self(), shared_val);
		}
	}
	pthread_mutex_unlock(&mutex);
	sleep(1);
	return NULL;
	}


void *decrement(void *arg){
	pthread_mutex_lock(&mutex);

	for(int i=0; i<LOOP; i++){
		if(shared_val > 5){
			printf("[%lu] shared_var prima = %d\n", pthread_self(), shared_val);
			shared_val-=1;
			printf("[%lu] shared_var dopo decremento = %d\n", pthread_self(), shared_val);
		}
	}
	pthread_mutex_unlock(&mutex);
	sleep(1);
	return NULL;
	}
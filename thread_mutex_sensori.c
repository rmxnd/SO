/*
thread_mutex_sensori.c

 °programma che permette la raccolta dati da 3 sensori.
 ° ogni sensore e' rappresentato da un thread:
 sensore1: ogni secondo monitora la temperatura di una stanza.
 sensore2: ogni secondo monitora l'umidita' di una stanza.
 sexxxnsore3: ogni secondo monitora il consumo energetic.
 ° tutti i sensori inviano i dati al main thread che stamnpera' i valori ogni 2 secondi.
 ° il padre termina se legge che il valore di tutti e 3 i sensori e' = -1
 ° usare la lib <time.h> per verificare se sono passati 20 secondi
 °i valori dei sensri vanno generati con rand con valore max 30 per temperatura, 100 per umidita', 3000 per consumo energetico.
 */
// errore

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
void *stemp (void *args);
void *sumid (void *args);
void *senergy (void *args);

int main(int argc, char **argv)
{
	pthread_t tt, te, tu;
	int thread_res = 0, temperatura = 0, umidita = 0, energia = 0;

	pthread_mutex_init (&mutex, NULL);	// creazione thread mutex
	if ( (thread_res = pthread_create(&tt, NULL, stemp, NULL) ) != 0 ) {
		perror ("errore pthread_create\n");
		exit (EXIT_FAILURE);
	}
	if ( (thread_res = pthread_create (&tu, NULL, sumid, NULL)) != 0 ) {
		perror ("errore pthread_create\n");
		exit (EXIT_FAILURE);
	}

	if ( (thread_res = pthread_create (&te, NULL, senergy, NULL)) != 0 ) {
		perror ("errore pthread_create\n");
		exit (EXIT_FAILURE);
	}

	while (1){
		pthread_mutex_lock(&mutex);
		if (temperatura == -1 && umidita == -1 && energia == -1) {
			break;
		}
		printf("T: %d\nU: %d\nE: %d\n", temperatura, umidita, energia);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	pthread_mutex_destroy (&mutex);
	return 0;
}


void *stemp (void *args){
	time_t start_time;

	srand (pthread_self());
	start_time = time(NULL);

	while ((time(NULL) - start_time) < 20 ){
		pthread_mutex_lock(&mutex);
		temperatura = rand()%31;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	printf("[stemp]: ho finito\n");

	pthread_mutex_lock(&mutex);
	temperatura = -1;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}

void *sumid (void *args){
	time_t start_time;

	srand (pthread_self());
	start_time = time(NULL);

	while ((time(NULL) - start_time) < 20 ){
		pthread_mutex_lock(&mutex);
		umidita = rand()%101;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	printf("[sumid]: ho finito\n");

	pthread_mutex_lock(&mutex);
	umidita = -1;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}

void *senergy (void *args){
	time_t start_time;

	srand (pthread_self());
	start_time = time(NULL);

	while ((time(NULL) - start_time) < 20 ){
		pthread_mutex_lock(&mutex);
		energia = rand()%3001;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	printf("[senergy]: ho finito\n");

	pthread_mutex_lock(&mutex);
	energia = -1;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}
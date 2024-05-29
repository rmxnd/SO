/*
 * thread_esempio.c
il main thread crea un thrad secondario che esegue la funzione thread_function
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *thread_function (void *args);
char messagio[5] = "ciao";	// variabile globale condivisa tra i 2 thread

int main(int argc, char **argv)
{
	int res;
	pthread_t ptid;
	void *thread_res;
	
	res = pthread_create (&ptid, NULL, thread_function, (void *)messagio);
	
		if (res != 0){
			perror ("errore\n");
			exit(EXIT_FAILURE);
		}
/* se la create() ha successo, il main thread continua 
 e il secondario eseguira' la thread_function */
	printf("main thread: attendo la terminazione del thread...\n");
	res = pthread_join(ptid, &thread_res);
		if (res != 0){
			perror ("errore\n");
			exit(EXIT_FAILURE);
		}
	
	printf("main thread: il thread ha terminato, restituendo %s\n", (char *)messagio);
	printf("Main thread: il messaggio e': %s\n", messagio);
	
	return 0;
}


void *thread_function (void *args){
	printf("Thread 1: sto eseguendo thread_function..,\n"
		   "Thread 1: Argomento: %s\n", (char *)args);
	sleep(3);
	
// snprintf e' una printf ma l'output e' su una stringa anziche' su stdout
	snprintf(messagio, 5, "Bye!");
	pthread_exit ("Grazie per il cpu time\n");
	};

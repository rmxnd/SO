/*
 * thread_detached.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


// variabili globali
void *thread_function(void *arg);
char message[] = "ciao";
int thread_finished = 0;	// usato dal secondo thread per dire al primo che ha finito


int main(int argc, char **argv)
{
int res;
pthread_t a_thread;
pthread_attr_t thread_attr;

res = pthread_attr_init(&thread_attr);
	if (res != 0){
		perror("creazione attributo fallita\n");
		exit(EXIT_FAILURE);
	}

	// creazione thread detached
res=pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	if (res != 0){
		perror("impostazione attributo detached fallita\n");
		exit(EXIT_FAILURE);
	}
	
	// creazione thread
res = pthread_create(&a_thread, &thread_attr, thread_function, (void*)message);
	if (res != 0){
		perror("creazione thread fallita\n");
		exit(EXIT_FAILURE);
	}
	
	// e' buona norma cancellare gli attributi dopo averli usati se non serviranno più
pthread_attr_destroy(&thread_attr);

	// non va in wait, è un'attesa attiva (busy waiting)
	while (!thread_finished){	// while thread_finished e' != 0
	printf("aspettando che finisca il thread...\n");
	sleep(1);
	}
	
	printf("gli altri thread hanno finitto, bye!\n\n");
	exit(EXIT_SUCCESS);
	
	return 0;	// non verrà eseguito perche esce prima con la exit se va bene
}


void *thread_function(void *arg){
	printf("Thread_function is running: Argument = %s\n", (char*)arg);
	sleep(4);
	thread_finished = 1; // imposta la variabile globale = 1
	pthread_exit(NULL);
	}

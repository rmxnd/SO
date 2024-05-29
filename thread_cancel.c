/*
 * thread_cancel.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *thread_function (void *args);


//	thread di inizio
int main(int argc, char **argv)
{
	int res;
	pthread_t ptid;
	void *thread_res;
	
	res = pthread_create (&ptid, NULL, thread_function, NULL);
	if (res != 0){
	perror("errore\n");
	exit(EXIT_FAILURE);	
	}
	
	// per lasciare sdpazio all'esecuzione del nuovo thread...
	sleep(3);
	printf("Main thread: sto cancellando il thread...\n");
	
	// richiesta di cancellazione Thread ptid
	res = pthread_cancel(ptid);
	if (res != 0){
	perror("thread_cancel fallita\n");
	exit(EXIT_FAILURE);	
	}
	printf("Main thread: aspettando che il thread finisca...\n");
	
	// Main thread si sincronizza sulla fine di ptid
	res = pthread_join(ptid, &thread_res);
	if (res != 0){
	perror("thread_join fallita\n");
	exit(EXIT_FAILURE);	
	}
	
	printf("Main thread: fatto\n\n");
	exit(EXIT_SUCCESS);
	
	// se tutto ok, non viene eseguito il return
	return 0;
}


void *thread_function (void *args){
	int res;
	
	// setto lo stato di cancellazione, cosi' viene cancellato all'arrivo del segnale
	res=pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
	if (res != 0){
	perror("setcancelstate fallita\n");
	exit(EXIT_FAILURE);	
	}
	
//setto il tipo di cancellazione deferred (prima del primo cancellation point utile)
	res = pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED, NULL);
	if (res != 0){
	perror("setcanceltype fallita\n");
	exit(EXIT_FAILURE);	
	}
	
	printf ("Thread 1: thread_function is running...\n");
	for (int i=0; i<10; i++){
		printf("Thread still running... (%d)\n", i);
		sleep(1);	// cancellation point
		}
	pthread_exit(NULL);
}

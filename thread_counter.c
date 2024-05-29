/*
 * thread_counter.c
 * stampa numeri da 1 a N su 2 thread separati
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define N 10

void *thread_fun1 (void *arg);
void *thread_fun2 (void *arg);

int main(int argc, char **argv)
{
	pthread_t thread1;
	pthread_t thread2;
	
	// creazione threads
	pthread_create(&thread1, NULL, thread_fun1, NULL);
	pthread_create(&thread2, NULL, thread_fun2, NULL);
	
	// attende terminazione dei thread
	pthread_join (thread1, NULL);
	pthread_join (thread1, NULL);
	
	return 0;
}

void *thread_fun1 (void *arg){
	for (int i=1; i<=N; i++){
	printf("Thread 1: %d\n", i);	
	}	
	return NULL;
	}
	
	
void *thread_fun2 (void *arg){
	for (int a=1; a<=N; a++){
		printf("Thread 2: %d\n", a);
	}
	return NULL;
	}

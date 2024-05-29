#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int a=1, b=1;
pthread_mutex_t mutex;
#define N 5
void *thread_function_a (void *arg);
void *thread_function_b (void *arg);


int main(int argc, char **argv)
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, thread_function_a, NULL);
	pthread_create(&thread2, NULL, thread_function_b, NULL);

	while(1){
		pthread_mutex_lock(&mutex);
		if (a == 0 && b == 0) break;
		else if ((a%b) == 0 || (b%a) == 0) {
			printf("a e b sono multipli\n");
			}
		else printf ("NON sono multipli\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}

	pthread_cancel(thread1);
	pthread_cancel(thread2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);
	exit(EXIT_SUCCESS);
}


void *thread_function_a (void *arg){
	for (int i=0; i<N; i++) {
		pthread_mutex_lock(&mutex);
		a = rand()%N+1;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

	pthread_mutex_lock(&mutex);
	a=0;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}

void *thread_function_b (void *arg){
	for (int i=0; i<N; i++) {
		pthread_mutex_lock(&mutex);
		b = rand()%N+1;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

	pthread_mutex_lock(&mutex);
	b=0;
	pthread_mutex_unlock(&mutex);
	return NULL;
	}
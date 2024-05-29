#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int var=1;
pthread_mutex_t mutex;
void *thread_func (void *arg);


int main(int argc, char **argv)
{
	pthread_t thread;
	pthread_attr_t attr;


	pthread_mutex_init(&mutex, NULL);
	pthread_attr_init(&attr);
	pthread_create(&thread, &attr, thread_func, (void *)&var);

	for(int i=0; i<10; i++){
		pthread_mutex_lock(&mutex);
		var += rand()%10+1;
		pthread_mutex_unlock(&mutex);
		printf("var = %d\n", var);
		sleep(1);
		}
	var = -1;

	pthread_mutex_destroy(&mutex);
	pthread_attr_destroy(&attr);
	pthread_join(thread, NULL);
	exit(EXIT_SUCCESS);
}


void *thread_func (void *arg) {
	while(1){
		pthread_mutex_lock(&mutex);
		if(var == -1){
			pthread_mutex_unlock(&mutex);
			break;
			}
		var --;
		pthread_mutex_unlock(&mutex);
		printf("[Thread secondario] var = %d\n", var);
	}

	return NULL;
	}
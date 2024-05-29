 /* thread_id.c
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>


void *thread_handler(void *args){
	pid_t tid;
	
	tid = gettid();
	printf("Thread secondario: PID = %d - TID = %d\n", getpid(), tid);
	printf("Thread secondario: Pthread ID = %ld\n", pthread_self());
	
	while(1) {
	sleep(1);
	}
	};
	
	
int main(int argc, char **argv)
{
	pid_t tid;
	pthread_t ptid;
	
	// creazione thread
	pthread_create(&ptid, NULL, thread_handler, NULL);
	
	tid = gettid();
	printf("Main Thread: PID = %d - TID = %d\n", getpid(), tid);
	printf("Main Thread: Pthread ID = %ld\n", pthread_self());	// TID libreria POSIX
	getchar();
	
	// cancellazione thread
	pthread_cancel(ptid);
	pthread_join(ptid, NULL);
	
	return 0;
}

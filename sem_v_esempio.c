/*
 sem_V_esempio.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>


int main(int argc, char **argv)
{
	static int sem_id;
	sem_t sem;
	pid_t pid1, pid2;	// 2 processi figli
	sem_init(&sem, 1, 1);	// creo un sem con valore = 1

	if ((pid1 = fork()) == 0) {	// figlio1
		for (int i = 0; i< 10; i++) {
			sem_wait(&sem);	// acquisisco il sem
			sem_id = semget((key_t)3456, 1, 0666 | IPC_CREAT);
			printf("semaforo (PID = %d) acqiusito dal figlio 1: i = %d\n", sem_id, i);
			sem_post(&sem);	// rilascio il sem
		}
		return 0;
	}

	if ((pid2 = fork()) == 0) {	// figlio2
		for (int i = 0; i< 10; i++) {
			sem_wait(&sem);	// acquisisco il sem
			sem_id = semget((key_t)3456, 1, 0666 | IPC_CREAT);
			printf("semaforo (PID = %d) acqiusito dal figlio 2: i 0 %d\n", sem_id, i);
			sem_post(&sem);	// rilascio il sem
		}
		return 0;
	}

	// padre
		for (int i = 0; i< 10; i++) {
			sem_wait(&sem);	// acquisisco il sem
			sem_id = semget((key_t)3456, 1, 0666 | IPC_CREAT);
			printf("semaforo (PID = %d) acqiusito dal padre: i = %d\n", sem_id, i);
			sem_post(&sem);	// rilascio il sem
		}

		// attesa terminazione figli
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		sem_destroy(&sem); // distruzione sem
		return 0;


	return 0;
}


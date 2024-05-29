/*
 sem_V_stampa.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>


#define NUM_SEMS 2
#define SEM1 0
#define SEM2 1


union semun {
	int val;
	struct semid_ds *buf;
	unsigned int *array;
};

void sem_wait (int semid, int sem_num);
void sem_signal (int semid, int sem_num);


int main(int argc, char **argv)
{
	int semid, i;
	union semun arg;
	struct sembuf sops[NUM_SEMS];

	// crea 2 sem
	semid = semget (IPC_PRIVATE, NUM_SEMS, 0666 | IPC_CREAT);
		if (semid == -1) {
			perror("errore semget\n");
			exit(EXIT_FAILURE);
		}

	// inizializza a 1  il primo sem
	arg.val = 1;
		if (semctl(semid, SEM1, SETVAL, arg) == -1) {
			perror ("errore semctl\n");
			exit (EXIT_FAILURE);
		}

	// inizializza a 0 il secondo sem
	arg.val = 0;
		if (semctl(semid, SEM2, SETVAL, arg) == -1) {
			perror ("errore semctl\n");
			exit (EXIT_FAILURE);
		}

	// crea un figlio
	if (fork () == 0 ) {
		for (i = 0; i < 10; i++) {
			sem_wait (semid, SEM1);
			printf ("child: %d\n", i);

			sem_signal (semid, SEM2);
		}
		exit(EXIT_SUCCESS);
	} else {
		// processo padre
		for (i = 0; i< 10; i++) {
			sem_wait (semid, SEM2);
			printf ("Parent: %d\n", i);

			sem_signal (semid, SEM1);
		}
	}

	// rimozione semafori
	if (semctl(semid, 0, IPC_RMID, arg) == -1) {
		perror ("errore semctl\n");
		exit(1);
	}
	return 0;
}


void sem_wait (int semid, int sem_num) {
	struct sembuf sops;
	sops.sem_num = sem_num;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	semop (semid, &sops, 1);

	return;
}


void sem_signal (int semid, int sem_num){
	struct sembuf sops;
	sops.sem_num = sem_num;
	sops.sem_op = 1;
	sops.sem_flg = 0;
	semop (semid, &sops, 1);

	return;
}

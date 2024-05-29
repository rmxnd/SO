/*
shm_esempio.c

Accesso concorrente alla SHM con sync tramite semafori
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


#define SIZE 1024


int main(int argc, char **argv)
{
	// creazione ID per il segmento di SHM
	// la key IPC_PRIVATE crea la SHM condivisibile solo tra parent processes
	int segment_id = shmget (IPC_PRIVATE, SIZE, IPC_CREAT | 0600);
		if (segment_id == -1) {
			perror("errore shmget\n");
			exit(EXIT_FAILURE);
		}
	// creazione ID semaforo
	int sem_id = semget (IPC_PRIVATE, 1, IPC_CREAT | 0600);
		if (sem_id == -1 ) {
			perror ("error semget\n");
			exit(EXIT_FAILURE);
		}

	int init = semctl (sem_id, 0, SETVAL, 1);
		if (init == -1) {
			perror ("error initializing sem\n");
			exit(EXIT_FAILURE);
		}

	// collegamento SHM al proprio spazio degli indirizzi
	int *attaching = shmat (segment_id, NULL, 0);
		if (attaching == (int *)-1) {
			perror ("errore shmat\n");
			exit(EXIT_FAILURE);
		}

		// accesso alla SHM
		struct sembuf sem_buf;

		sem_buf.sem_num = 0;
		sem_buf.sem_op = -1;
		sem_buf.sem_flg = SEM_UNDO;

			// acquisisco il sem
	int op = semop (sem_id, &sem_buf, 1);
		if (op == -1) {
			perror ("errore semop\n");
			exit(EXIT_FAILURE);
		}
	printf("semop creata correttamente \n\n");
	exit(EXIT_SUCCESS);
	return 0;
}


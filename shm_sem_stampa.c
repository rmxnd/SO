/*
shm_sem_stampa.c

IPC con sem e shm
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SIZE 1024

struct sembuf sem_buf;
void wait_sem (int semid);		// attende che il sem sia disponibile
void signal_sem (int semid);	// segnala che il sem e' disponibile


int main(int argc, char **argv)
{
	char string[100];
	key_t key = ftok("shm_sem_stampa.c", 65);	// key per la shm

	int shmid = shmget (key, SIZE, 0666 | IPC_CREAT);	// id shm
		if (shmid == -1) {
			perror("errore shmget\n");
			exit(EXIT_FAILURE);
		}
	char *str = (char *)shmat (shmid, NULL, 0);	// attacco la shm al processo
		if (shmat == (void *)-1) {
			perror("errore shmat\n");
			exit(EXIT_FAILURE);
		}

	int semid = semget (key, 1, 0666 | IPC_CREAT);	// crea il sem
		if (semid == -1) {
			perror("errore semget\n");
			exit(EXIT_FAILURE);
		}

	int sem_ctl = semctl (semid, 0, SETVAL, 1);	// inizializza il sem a 1
		if (sem_ctl == -1) {	// in caso fai la union
			perror("errore semctl\n");
			exit(EXIT_FAILURE);
		}

	printf ("processo A: inserire stringa:\t");
	scanf ("%s", string);

	wait_sem(semid);
	printf("processo B: stringa letta da A: %s\n", string);
	signal_sem(semid);

	int detach = shmdt(str);	// str = puntatore di shmat
	if (detach == -1) {
			perror("errore shmdt\n");
			exit(EXIT_FAILURE);
		}
	sem_ctl = semctl (semid, 0, IPC_RMID);
		if (sem_ctl == -1) {
			perror("errore semctl\n");
			exit(EXIT_FAILURE);
		}
	return 0;
}


void wait_sem (int semid){
	int sem_oper = 0;

	sem_buf.sem_num = 0;	/* semaphore number (in array) */
	sem_buf.sem_op = -1;	/* semaphore operation - attende disponibilita' sem */
	sem_buf.sem_flg = 0;	/* operation flags */

	sem_oper = semop (semid, &sem_buf, 1);
	if (sem_oper == -1){
		perror ("errore semop\n");
		exit(EXIT_FAILURE);
	}
	return;
	}


void signal_sem (int semid) {
	int sem_oper = 0;

	sem_buf.sem_num = 0;	/* semaphore number */
	sem_buf.sem_op = 1;		/* semaphore operation - sem disponibile */
	sem_buf.sem_flg = 0;	/* operation flags */

	sem_oper = semop (semid, &sem_buf, 1);
	if (sem_oper == -1){
		perror ("errore semop\n");
		exit(EXIT_FAILURE);
	}
	return;
	}

/*
shm_sem_produttore_consumatore.c

problema del produttore-consumatore con buffer circolare
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>


#define BUF_SIZE 5
struct sembuf sem_buf;	// struct per le operazioni sul sem
void wait_sem (int semid);
void post_sem (int semid);


int main(int argc, char **argv)
{
	// int buf_fer[BUF_SIZE];
	key_t key = ftok(*argv, BUF_SIZE);
	int shmid = shmget (key, sizeof(int) * BUF_SIZE, 0666 | IPC_CREAT);	// creazione shm
		if (shmid == -1) {
			printf("errore semget\n");
			exit(EXIT_FAILURE);
		}

	int *buffer = (int *)shmat (shmid, NULL, 0);	// attach shm al processo
		if (shmat == (void *)-1) {
			printf("errore shmat\n");
			exit(EXIT_FAILURE);
		}

	int semid = semget(key, 1, 0666 | IPC_CREAT);
	if (semid == -1) {
			printf("errore semget\n");
			exit(EXIT_FAILURE);
		}

	union semun {	// copiato da manuale
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO */
	} sem_un;

	sem_un.val = 1; // inizializzazione sem
	int sem_ctl = semctl (semid, 0, SETVAL, sem_un);
		if (sem_ctl == -1) {
			printf("errore semctl\n");
			exit(EXIT_FAILURE);
		}

	int in = 0, out = 0; 	// inizializzazione inserimento ed estrazione

	// produttore
	if (fork() == 0){
		for (int i=0; i<=10; i++){
			wait_sem(semid);	// attendi che il buffer sia pieno
			buffer[in] = i; // inserimento del dato nel buf
			printf("Produttore: inserito %d nel buffer\n", i);
			in = (in + 1) % BUF_SIZE;

			post_sem(semid);
			sleep(1); // simula la produzione
		}
		// exit(EXIT_SUCCESS);
	}

	// consumatore
	if (fork() == 0){
		for (int i=0; i<10; i++){
			wait_sem(semid);	// attendi che il buffer sia pieno
			int data = buffer[out];	// estrazione del dato dal buffer
			printf("Consumatore: estratto %d nel buffer\n", data);
			out = (out + 1) % BUF_SIZE;

			post_sem(semid);	// segnala che buf non e' pieno
			sleep(1); // simula il consumo
		}
		// exit(EXIT_SUCCESS);
	}
	wait (NULL);	// attesa terminazione figli
	wait (NULL);
	shmdt(buffer);
	shmctl(shmid, IPC_RMID, NULL);	// rimozione shm e sem
	semctl(semid, 0, IPC_RMID);
	return 0;
}


void wait_sem (int semid){
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;	// wait sem to become available
	sem_buf.sem_flg = 0;
	int sem___wait = semop(semid, &sem_buf, 1);
		if (sem___wait == -1) {
			printf("errore semop in wait_sem\n");	// errore nel programma
			exit(EXIT_FAILURE);
		}
	return;
	}


void post_sem (int semid){
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 1;		// sem is available
	sem_buf.sem_flg = SEM_UNDO;
	int sem___op = semop (semid, &sem_buf, 1);
		if (sem___op == -1) {
			printf("errore semop in post_sem\n");
			exit(EXIT_FAILURE);
		}
	return;
	}

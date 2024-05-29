/*
shm_sem_motore.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <wait.h>


union semun {
	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};


int sem_up (int semid);
int sem_down (int semid);
int sem_set (int semid, int val);


#define KEY_SEM (key_t)9876
#define KEY_SHM (key_t)9875
#define N_VOLTE 20


int main(int argc, char **argv)
{
	int semid, shmid, semset, i, r;
	char *comando;	// punt indirizzo di memoria
	pid_t m1, m2;	// figli
	char *cmds[] = {"Avanti", "Indietro", "Sinistra", "Destra", "Stop"};	// commands
	char oldcmd [100] = "";

	semid = semget (KEY_SEM, 1, IPC_CREAT | 0666);
		if (semid == -1) {
			perror("errore semget\n");
			exit(EXIT_FAILURE);
		}

	semset = sem_set(semid, 1);
		if (semset == -1) {
			perror("sem_set error\n");
			exit(EXIT_FAILURE);
		}

	shmid = shmget (KEY_SHM, sizeof(char)*100, 0666 | IPC_CREAT);
		if (shmid == -1) {
			perror("shmid error\n");
			exit(EXIT_FAILURE);
		}

	comando = (char *)shmat (shmid, NULL, 0);	// zero: decide il kernel
		if (comando == (void *)-1) {
			perror ("errore attach shmat\n");
			exit(EXIT_FAILURE);
		}

	m1 = fork();
	switch (m1) {
			case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);
			break;

			case 0:	// figlio
			while (1) {
			// ogni volta che la variabile condivisa cambia, la stampa
			sem_down(semid);	// accede alla sezione critica

			if (strcmp(comando, "Termina") == 0) {
				shmdt(comando);
				sem_up(semid);
				exit(EXIT_SUCCESS);
			}

			if (strcmp (comando, oldcmd) != 0) {
				// copio 'comando' in 'oldcmd'
				strcpy(oldcmd, comando);
				printf("Figlio 1: ricevuto %s\n", comando);
			}
			sem_up(semid);
			}

			break;

			default:	// padre

			break;
	}


	// figlio2, copiato da figlio1
	m2 = fork();
	switch (m2) {
			case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);
			break;

			case 0:	// figlio
			while (1) {
			// ogni volta che la variabile condivisa cambia, la stampa
			sem_down(semid);	// accede alla sezione critica

			if (strcmp(comando, "Termina") == 0) {
				shmdt(comando);
				sem_up(semid);
				exit(EXIT_SUCCESS);
			}

			if (strcmp (comando, oldcmd) != 0) {
				// copio 'comando' in 'oldcmd'
				strcpy(oldcmd, comando);
				printf("Figlio 2: ricevuto %s\n", comando);
			}
			sem_up(semid);
			}

			break;

			default:	// padre

			break;
	}

	srand(getpid());
	for (i=0; i<N_VOLTE; i++){
		r = rand() % 5;	// numero da 0 a 4
		sem_down(semid);
		strcpy(comando, cmds[r]);
		printf("Padre: %s\n", comando);
		sem_up(semid);
		sleep(2);
		}

		sem_down(semid);
		strcpy(comando, cmds[r]);
		printf("Padre: %s\n", comando);
		sem_up(semid);

		wait(NULL);
		wait(NULL);	// attendo i 2 figli

		shmdt(comando);
		shmctl(shmid, IPC_RMID, NULL);
		shmctl(semid, 0, IPC_RMID);

	semctl(semid, 0, IPC_RMID, 0);

	return 0;
}


int sem_up (int semid) {
	struct sembuf sb;	// riempio i campi della struct
	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;

	return semop(semid, &sb, 1);
	}


int sem_down (int semid) {
	struct sembuf sb;	// riempio i campi della struct
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;

	return semop(semid, &sb, 1);
	}


int sem_set (int semid, int val) {
	union semun un;
	un.val = val;

	return semctl(semid, 0, SETVAL, un);
	}

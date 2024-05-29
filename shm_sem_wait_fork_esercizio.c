/*
shm_sem_wait_fork_esercizio.c

* il processo principale P0 crea un figlio P1;
* P0 e P1 condividono tramite shm 2 variabili int (base e alteza, di un triangolo);
* P0 per 4 volte: * chiede di inserire 2 int da tastiera (base e altezza);
				  * attende che P1 abbia calcolato l'area del triangolo;
* dopo le 4 iterazoni, P0: * attende la terminazione di P1;
						   * elimina shm e sem;
						   * termina esso stesso;
* P1 per 4 volte: * attende che P0 abbia aggiornato le var condivise (con sem);
				  * calcola l'area del traiangoo e la stampa;
* dopo 4 itrerazioni P1 termina;
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/wait.h>


#define SEM_START_WRITE (key_t)8765
#define SEM_END_WRITE (key_t)8764
#define SIZE 32
#define N 4


union semun {
	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	};


struct shmem {
	int altezza, base;
	};


int sem_set(int semid, int val);
int sem_up(int semid);
int sem_down(int semid);
void area (int a, int b, struct shmem* sh_data);


int main(int argc, char **argv)
{
	int sem_start, sem_end, shm, statval;
	pid_t P1;
	key_t key;
	struct shmem* sh_data;


	if ((key = ftok("shm_sem_wait_fork_esercizio.c", 644)) == -1){
		perror("errore ftok\n");
		exit(EXIT_FAILURE);
		}

		// creazione sem
	if ((sem_start = semget(SEM_START_WRITE, 1, IPC_CREAT | 0666)) == -1){
		perror("errore semget start\n");
		exit(EXIT_FAILURE);
		}

	if ((sem_end = semget(SEM_END_WRITE, 1, IPC_CREAT | 0666)) == -1){
		perror("errore semget end\n");
		exit(EXIT_FAILURE);
		}

		// inizializzazione sem
		sem_set(sem_start, 1);
		sem_set(sem_end, 0);

		// creazione shm + attach
	if ((shm = shmget(key, sizeof(struct shmem), IPC_CREAT | 0666)) == -1){
		perror("errore shmget\n");
		exit(EXIT_FAILURE);
		}
	if (shmat(shm, NULL, 0) == (void *)-1){
		perror("errore shmat\n");
		exit(EXIT_FAILURE);
		}

	P1 = fork();
	switch(P1){
		case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);
		case 0:	// figlio
			area(sem_start, sem_end, sh_data);
			exit(EXIT_SUCCESS);
		default:
		break;
		}

		// padre
		for(int i = 0; i < N; i++){
			sem_down(sem_start);
			printf ("inserire base:\t");
			scanf("%d", &sh_data->base);
			printf ("inserire altezza:\t");
			scanf("%d", &sh_data->altezza);
			sem_up(sem_end);
			}

	wait(NULL);
	if(WIFEXITED(statval)) printf("figlio terminato normalmente con codice: %d\n", WEXITSTATUS(statval));

		// rimozione shm e sem
	shmdt(sh_data);
	shmctl(shm, IPC_RMID, NULL);
	semctl(sem_start, 0, IPC_RMID);
	semctl(sem_end, 0, IPC_RMID);

	exit(EXIT_SUCCESS);
}


int sem_set(int semid, int val) {
	union semun s;

	s.val = val;
	return semctl(semid, 0, SETVAL, 5);
	}


int sem_up(int semid){
	struct sembuf buff;

	buff.sem_num = 0;
	buff.sem_op = 1;	// incremento
	buff.sem_flg = SEM_UNDO;
	return semop(semid, &buff, 1);
	}


int sem_down(int semid) {
	struct sembuf buff;

	buff.sem_num = 0;
	buff.sem_op = -1;	// decremento
	buff.sem_flg = SEM_UNDO;
	return semop(semid, &buff, 1);
	}


void area (int a, int b, struct shmem* sh_data){	// i fifli ereditano dal padre sem + shm
	float area;

	for (int i=0; i<N; i++){
		sem_down(b);	// attesa che P0 aggiorni le var condivise
		area = (a*b)/2;
		printf("Area = %.3f\n", area);
		sem_up(a);
	}
	exit(EXIT_SUCCESS);
	}
/*
shm_sem_mutex_fork_producer_consumer.c

* producer e consumer condividono un array di 5 elementi;
* il processo principale (P0) genera un processo figlio (P1), che condividono l'array tramite shared memory;
* P0 inizializza a (-1) tutti gli elementi dell'array, poi genera il figlio, poi per 10 volte: attende che ci sia almeno 1 elemento !=(-1) nell'array, cerca il primo elemento !=(-1) nell'array, stampa l'elemento trovato, imposta il valore dell'elemento a (-1) (per indicare che e' stato letto), dopo 10 iterazioni P0 attende la fine del figlio, poi elimina la shared memory e i semafori e termina essostesso;
* P1 per 10 volte: attendono che nell'array ci sia almeno 1 elemento =(-1), generano un valore intero random tra 0 e 99 e lo assegnano al 1° elelento dell'array con valore =(-1), dopo 10 iterazioni terminano;
* usare i semafori sia per sezione critica sia per sync processi;
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>


#define SEM_FULL (key_t)8765
#define SEM_EMPTY (key_t)8764
#define SEM_MUTEX (key_t)8763
#define SHM_KEY (key_t)9876
#define DIM 5	// elemento array
#define LOOP 10	// ciclo for


union semun {
	int 	val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	};


void figlio();


int main(int argc, char **argv)
{
	pid_t pid;
	int shmid, dt, ctl, i, j, semfull, semempty, semmutex, sem_ctl, sem_op;
	union semun s;
	struct sembuf buff;


	// creazione semafori
	if ((semfull=semget(SEM_FULL, 1, 0666 | IPC_CREAT)) == -1){
		perror("errore semget SEM_FULL\n");
		exit(EXIT_FAILURE);
	}
	if ((semempty=semget(SEM_EMPTY, 1, 0666 | IPC_CREAT)) == -1){
		perror("errore semget SEM_EMPTY\n");
		exit(EXIT_FAILURE);
	}
	if ((semmutex=semget(SEM_MUTEX, 1, 0666 | IPC_CREAT)) == -1){
		perror("errore semget SEM_MUTEX\n");
		exit(EXIT_FAILURE);
	}

	// inizializzazione sem
	s.val=0;
	if ((sem_ctl=semctl(semfull, 0, SETVAL, s)) == -1){
		perror("errore semget semctl semfull\n");
		exit(EXIT_FAILURE);
	}
	s.val=DIM;
	if ((sem_ctl=semctl(semempty, 0, SETVAL, s)) == -1){
		perror("errore semget semctl semempty\n");
		exit(EXIT_FAILURE);
	}
	s.val=1;
	if ((sem_ctl=semctl(semmutex, 0, SETVAL, s)) == -1){
		perror("errore semget semctl semmutex\n");
		exit(EXIT_FAILURE);
	}

	// creazione shm
	if ((shmid=shmget(SHM_KEY, sizeof(int)*DIM, 0666 | IPC_CREAT) == -1)){
		perror("errore shmget\n");
		exit(EXIT_FAILURE);
	}
	/* if ((array=(int *)shmat(shmid, NULL, 0) == (int *)-1){
		perror("errore shmat\n");
		exit(EXIT_FAILURE);
	} */
	array=(int *)shmat(shmid, NULL, 0);

	// inizializzazione array a -1
	for (i=0; i<DIM; i++){
		array[i]=-1;
	}

	// creazione figlio
	switch(pid){
		case -1:
		perror("errore fork\n");
		exit(EXIT_FAILURE);

		case 0:	// figlio
		figlio();
		exit(EXIT_SUCCESS);

		default:
		break;
	}
	// padre produttore
	for (i=0; i<LOOP; i++){

		// decremento semaforo
		buff.sem_num=0;
		buff.sem_op=-1;
		buff.sem_flg=SEM_UNDO;
		if ((sem_op=semop(semfull, &buff, 1)) == -1){
		perror("errore semop semfull\n");
		exit(EXIT_FAILURE);
			}
		if ((sem_op=semop(semmutex, &buff, 1)) == -1){
		perror("errore semop semmutex\n");
		exit(EXIT_FAILURE);
			}
		for (j=0; j<DIM; j++){
			if(array[j] != -1){
				printf("elemento letto %d\n", array[j]);
				array[j] = -1;
			}
		}
		// incremento semaforo
		buff.sem_num=0;
		buff.sem_op=1;
		buff.sem_flg=SEM_UNDO;
		if ((sem_op=semop(semmutex, &buff, 1)) == -1){
		perror("errore semop semmutex\n");
		exit(EXIT_FAILURE);
			}
		if ((sem_op=semop(semempty, &buff, 1)) == -1){
		perror("errore semop semempty\n");
		exit(EXIT_FAILURE);
			}
		sleep(1);
	}
	wait(NULL);
	if ((dt=shmdt(array) == -1){	// detach shm
		perror("errore shmdt\n");
		exit(EXIT_FAILURE);
	}
	if ((ctl=(shmctl(shmid, IPC_RMID, NULL) == -1){	// eliminazione shm
		perror("errore shmget\n");
		exit(EXIT_FAILURE);
	}
	// eliminazione sem
	if ((sem_ctl=(semctl(semfull, 0, IPC_RMID) == -1){
		perror("errore semctl\n");
		exit(EXIT_FAILURE);
	}
	if ((sem_ctl=(semctl(semempty, 0, IPC_RMID) == -1){
		perror("errore semctl\n");
		exit(EXIT_FAILURE);
	}
	if ((sem_ctl=(semctl(semmutex, 0, IPC_RMID) == -1){
		perror("errore semctl\n");
		exit(EXIT_FAILURE);
	}
	printf("fine programma\n");
	exit(EXIT_SUCCESS);
}


void figlio (){
	struct sembuf buff;
	int i, j, time_to_exit=0;

	for (i=0; i<LOOP; i++){

		// decremento semaforo
		buff.sem_num=0;
		buff.sem_op=-1;
		buff.sem_flg=SEM_UNDO;
		if ((sem_op=semop(semempty, &buff, 1)) == -1){
		perror("errore semop semempty\n");
		exit(EXIT_FAILURE);
			}
		if ((sem_op=semop(semmutex, &buff, 1)) == -1){
		perror("errore semop semmutex\n");
		exit(EXIT_FAILURE);
			}
		printf("ciclo %d\n", i);
		for (j=0; j<DIM; j++){
			if(array[j] == -1){
				array[i] = rand()%99;
			}
		}
		// incremento semaforo
		buff.sem_num=0;
		buff.sem_op=1;
		buff.sem_flg=SEM_UNDO;
		if ((sem_op=semop(semmutex, &buff, 1)) == -1){
		perror("errore semop semmutex\n");
		exit(EXIT_FAILURE);
			}
		if ((sem_op=semop(semfull, &buff, 1)) == -1){
		perror("errore semop semfull\n");
		exit(EXIT_FAILURE);
			}
	}
	return;
	}
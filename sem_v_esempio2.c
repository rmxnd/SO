/*
sem_v_esempio2.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <wait.h>


int main(int argc, char **argv)
{
	key_t key;
	pid_t pid1, pid2;

	key = ftok("Livri", 0); // genero la key con ftok
	if (key == -1){
		perror("errore ftok\n");
		exit(EXIT_FAILURE);
	}
	printf("key : %d\tgenerata con successo\n", key);

	int semid = semget (key, 1, 0666 | IPC_CREAT);	// creazione semaforo
	if (semid == -1) {
		perror("errore semget\n");
		exit(EXIT_FAILURE);
	}
	printf("semaforo: %d\tgenerato con successo\n", semid);

	// inizializzazione struct sembuf op
	struct sembuf sops[1];
	sops[0].sem_num = 0;
	sops[0].sem_op = 1;
	sops[0].sem_flg = 0;

	if (semop(semid, sops, 1) == -1) { 	// inizializzazione semaforo con valore = 1
	perror("semop fallita\n");
	exit(EXIT_FAILURE);
	}

	pid1 = fork();
	if (pid1 == -1){
		perror("fork pid1 fallita\n");
		exit(EXIT_FAILURE);
	}	// processo pid1 :
	if (pid1 == 0) {
	printf("figlio 1\n\n");
	exit(EXIT_SUCCESS);
	}

	pid2 = fork();
	if (pid2 == -1){
		perror("fork pid2 fallita\n");
		exit(EXIT_FAILURE);
	}	// processo pid2 :
	if (pid2 == 0) {
	printf("figlio 2\n\n");
	exit(EXIT_SUCCESS);
	}

	// attesa terminazione figli
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	semctl(semid, 0, IPC_RMID);	// eliminazione sem
	printf("tutto eliminato, terminando il programma...\n");
	return 0;
}

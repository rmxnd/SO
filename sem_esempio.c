/*
sem_esempio.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>


static int set_semvalue (void);
static void delete_semvalue (void);
static int semaphore_p (void);	// for wait
static int semaphore_v (void);	// for signals
static int sem_id;


union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	};


int main(int argc, char **argv)
{
	int i, pause_time;
	char op_char = 'O';

	srand((unsigned int)getpid());
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

	if (argc > 1) {
		if (!set_semvalue()) {
			fprintf(stderr, "Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
	op_char = 'X';
	sleep(2);
	}

	for (i=0; i<10; i++){
		if (!semaphore_p())	exit(EXIT_FAILURE);

	printf("%c\n", op_char); fflush(stdout);
	pause_time= rand() % 3;
	sleep(pause_time);
	printf("%c\n", op_char); fflush(stdout);

		if(!semaphore_v()) exit(EXIT_FAILURE);

	pause_time = rand() % 2;
	sleep(pause_time);
	}

	printf("\n%d - finished\n", getpid());
	if (argc > 1) {
		sleep(10);
		delete_semvalue();
	}
	exit(EXIT_SUCCESS);
	return 0;
}


static int set_semvalue (void){
	union semun sem_union;

	sem_union.val = 1;
	if(semctl(sem_id, 0, SETVAL, sem_union) == -1) return(0);

	return(1);
	}


static void delete_semvalue (void){
	union semun sem_union;

	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1);
	fprintf(stderr, "Failed to delete semaphore\n");
	return;
	}


static int semaphore_p (void){
	struct sembuf sem_buf;

	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_buf, 1) == -1) {
		fprintf(stderr, "semaphore_p failed\n");
		return(0);
	}
	return(1);
	}


static int semaphore_v (void){
	struct sembuf sem_buf;

	sem_buf.sem_num = 0;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_buf, 1) == -1) {
		fprintf(stderr, "semaphore_v failed\n");
		return(0);
	}
	return(1);
	}

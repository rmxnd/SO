/*
 qsem_fork.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <wait.h>
#include <sys/types.h>

sem_t mutex, turn;
void stampa (int num);
// void scambia_turno ();


int main(int argc, char **argv)
{
	sem_init(&mutex, 0, 1);
	sem_init(&turn, 0, 0);
	pid_t pid1, pid2;

	pid1 = fork();
	pid2 = fork();

	if (pid1 == 0 ) {	// se e' il padre
		for (int i=1; i<=10; i++) {
			stampa(i);	// stampa i num da 1 a 10
			sleep(1);
		}
	} else if (pid2 == 0 ) {
		for (int i=11; i<=20; i++) {
			stampa(i);	// stampa i num da 11 a 20
			sleep(1);
		}
	} else {
		waitpid (pid1, NULL, 0);	// aspetta la terminazione dei 2 figli
		waitpid (pid2, NULL, 0);
		printf (" i figli hanno terminato\n");
	}


	return 0;
}


void stampa (int num){
	sem_wait(&mutex);	// decrementa (blocca) il sem
	printf("numero = %d\n", num);
	sem_post(&mutex);	// incrementa (sblocca)) il sem

	return;
}

/*
void scambia_turno (){
	sem_wait(&turn);	// blocca turn
	sem_post(&mutex);	// rilascia mutex
	sem_wait(&mutex);	// blocca mutex

	return;
	}
*/

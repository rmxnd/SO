/*
	tutorato_simile_esame.c

	* padre genera N figli;
	*
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


#define N 6
#define LOOP 10


void *sig_handler (int sig);


int main(int argc, char **argv)
{
	pid_t pid[N];
	struct sigaction act;
	int r1, r2;


	for (int i=0; i<N; i++){
		switch (pid[i] = fork()){
			case -1:
				perror("errore fork \n");
				exit(EXIT_FAILURE);

			case 0:	// figlio
				act.sa_handler = sig_handler;
				sigemptyset (&(act.sa_mask));
				act.sa_flags = 0;

				sigaction (SIGUSR1, &act, NULL);
				sigaction (SIGUSR2, &act, NULL);
				while (1) pause();
				exit(EXIT_SUCCESS);	// in caso sostituire con break;

			default:
				break;

		}
	}

	srand(time(NULL));
	for (int j=0; j<LOOP; j++){
		r1 = rand()%2+1;
		r2 = rand()%N+1;
		printf("[PADRE] r1 = %d\t r2 = %d\n", r1, r2);

		if (r1 == 1) {
			kill(pid[r2-1], SIGUSR1);
		}
		else if (r1 == 2) {
			kill(pid[r2-1], SIGUSR2);
		}
		printf("[PADRE] segnale inviato\n");
		sleep(2);
	}

	for (int u=0; u<N; u++){
		kill(pid[u], SIGKILL);
	}
	for (int u=0; u<N; u++){
		waitpid(pid[u], NULL, 0);
		printf("[PADRE] attendo fine figlio %d\n", u+1);
	}
	exit(EXIT_SUCCESS);
}


void *sig_handler (int sig){
	printf("[FIGLIO] pid: %d\n", getpid());

	if (sig == SIGUSR1) printf("[FIGLIO] ricevuto SIGUSR1\n");
	else if (sig == SIGUSR2) printf("[FIGLIO] ricevuto SIGUSR2\n");
	return NULL;
	}

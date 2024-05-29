/*
 * fork_dado.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>


#define N 5
int num; // sig_handler puo modificarlo e il figlio puo leggere il valore

void sig_handler (int sig);
void figlio (int i);


int main(int argc, char **argv)
{
int i, somma = 0, ritorno;
pid_t figli[N];

	for (i=0; i<N; i++){
		figli[i] = fork();

			switch (figli[i]) {
				case -1:
				perror ("errore creazione figlio\n");
				exit(EXIT_FAILURE);

				case 0:
				figlio(i);
				// altrimenti il figlio genera altri figli
				exit(EXIT_FAILURE);
				default: break;
			}	// fine switch
	}	// fine for

	printf("Padre: ho generato %d figli\n", N);
	sleep(1);

	// manda il segnale a ogni figlio
	for (i=0; i<N; i++){
		kill(figli[i], SIGUSR1);
	}

	// attende la terminazione di ogni figlio
	for (i=0; i<N; i++){
		wait(&ritorno);
		if (WIFEXITED(ritorno)) {
			somma += WEXITSTATUS(ritorno);
		}	// fine if
	}	// fine for

	printf("Padre: Risultato = %d\n", somma);
	return 0;
}


void figlio (int i){
	signal(SIGUSR1, sig_handler);
	printf("sono il figlio n°: %d, attendo SIGUSR1\n", (i+1));
	pause();

	printf("Figlio %d: generato numero: %d\n", (i+1), num);
	exit(num);
	return;
	}


	void sig_handler (int sig){
		if (sig == SIGUSR1){
			num = (rand()%5) +1; // genera un numero random tra 1 e 6
		}
		return;
		}

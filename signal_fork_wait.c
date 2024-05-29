/*
signal_fork_wait.c

* il padre genera un figlio;
* il figlio: * con alarm(), imposta l'autoinvio di SIGALRM dopo 10 secondi;
			 * genera un numero casuale 'r' tra 1 e 50;
			 * se r > 20: il figlio annulla l'impostazione di SIGALRM e termina restituendo 0;
			 * altrimenti attende l'arrivo di un segnale (SIGALRM);

* il padre: * attende la terminazione del filfio;
			* stampa un msg per dire se il figlio ha terminato normalmente o no;
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>


void handler (int sig);


int main(int argc, char **argv)
{
	pid_t pid;
	int status, r=0;
	struct sigaction act;

	pid = fork();
	switch(pid){
		case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);
		case 0:	// figlio
			act.sa_handler = handler;
			sigemptyset(&act.sa_mask); // inizializza una mask di segnali vuota
			act.sa_flags = 0;
			if (sigaction(SIGALRM, &act, NULL) == -1){
				perror("errore sigaction\n");
				exit(EXIT_FAILURE);
				}
			alarm(10);
			srand(time(NULL));
			r = rand() % 1+50;

			if (r > 20){
				alarm(0);
				printf("[Figlio] r (= %d) > 20: terminazione\n", r);
				exit(0);
				} else pause();	// attesa segnale
			exit(EXIT_SUCCESS);
		default:
			break;
	}

	// padre
	if (waitpid(pid, &status, 0) == -1){
		perror("errore waitpid\n");
		exit(EXIT_FAILURE);
		}
	if(!WIFEXITED(status)){
		perror("errore WIFEXITED: figlio terminato in modo anomalo\n");
		exit(EXIT_FAILURE);
		} else printf("[Padre] il figlio ha terminato normalmente\n");
	exit(EXIT_SUCCESS);
}


void handler (int sig){
	if(sig == SIGALRM){
		printf("segnale arrivato: SIGALRM\n");
		exit(EXIT_FAILURE);
		}
	}
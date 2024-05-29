/*
 * sigaction_pingpong.c
 il padre stampa ping, il figlio pong, entrambi alla ricezione del segnale
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>


#define N 11

void child_sig_handler (int sig);
void sig_handler (int sig);

int main(int argc, char **argv)
{
	struct sigaction sact;
	pid_t figlio;
	int i;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = sig_handler;

	figlio = fork();
	switch (figlio) {
		case -1:	// errore
		perror("errore forn\n");
		exit(EXIT_FAILURE);

		case 0:	// figlio
		sact.sa_handler = child_sig_handler;
		sact.sa_flags = 0;
		sigemptyset(&sact.sa_mask);
		sigaddset(&sact.sa_mask, SIGQUIT);

		sigaction(SIGUSR1, &sact, NULL);
		sigemptyset(&sact.sa_mask);

		sigaction(SIGQUIT, &sact, NULL);

		while (1){
			pause();
		}
		exit(0);	// fine figlio

		default:
		printf("Ping ->");
		fflush(stdout);
		break;
	}

	// padre
	sigaction(SIGUSR2, &sact, NULL);
	for (; i<N; i++){
		sleep(1);
		kill(figlio, SIGUSR1);
		pause();
	}

	kill(figlio, SIGQUIT);
	wait(NULL);	// il padre aspetta che termini il figlio

	return 0;
}


void child_sig_handler (int sig){	// figlio
	if (sig == SIGQUIT) {
		printf ("ricevuto sigquit codice %d", sig);
		exit(0);
	} else if (sig == SIGUSR1){
		printf("Pong\n");
		kill(getppid(), SIGUSR2);
	}
	return;
	}

void sig_handler (int sig){	// padre
	if (sig == SIGUSR2) {
		sleep(1);
		printf("Ping");
		fflush(stdout); // forza la stampa
	}
	return;
	}

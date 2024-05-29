/*
 * signal_fork_esercizio.c

* il padre P0 genera 1 figlio P1;
* il figlio: *imposta l'invio a se stesso di SIGALRM dopo 15 secondi;
			 * chiede l'inserimento di una lettera:
					* se e' maiuscola, il figlio annulla la alarm, termina e restituisce 0;
					* altrimenti, attende l'arrivo di SIGALRM;
* il padre: * attende la terminazione del figlio;
			* stampa un msg per dire se il figlio termina normalmente o no;
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>


int main(int argc, char **argv)
{
	pid_t pid;
	char lettera;
	int statval;

	switch(pid = fork()) {
		case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);

		case 0:
			alarm(15);
			printf("inserire lettera:\t");
			scanf("%c", &lettera);
			if (lettera >= 'A' && lettera <= 'Z'){
				printf("Maiuscola\n");
				alarm(0);
				return 0;
			} else {
				printf("minuscola\n");
				while(1) pause();
				}
			exit(EXIT_SUCCESS);

		default:
		wait(&statval);
		if (WIFEXITED(statval)) printf("il figlio ha concluso normalmente\n");
		else printf("il figlio NON ha treminato niormalmente\n");
		break;
	}
	return 0;
}
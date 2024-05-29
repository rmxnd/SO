/*
file_fork_esercizio.c

 */


#include <stdio.h>


void sigusr_handler (){
	if (sig == SIGUSR){
		printf("arrivato sigusr1\n");
		alarm(0);
		exit(EXIT_SUCCESS);
	} else if (sig == SIGALRM){
		printf("segnale non ricevuto\n");
	}
	}


int main(int argc, char **argv)
{
	pid_t pid_f1, pid_f2;
	struct sigaction sact;
	int status, r;

	sact.sa_handler = sigusr_handler;
	sigemptyset(&(sact.sa_mask));
	sact.sa_flags=0;

	pid_f1=fork();
	switch (pid_f1){
	case -1:
		perror("errore fork\n");
		exit(EXIT_FAILURE);

	case 0:

	default:
	break;


	}

	return 0;
}


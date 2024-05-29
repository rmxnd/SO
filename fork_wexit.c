/*
fork_wexit.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	pid_t pid;
	int statval;

	pid = fork();
		if(pid == -1) {
			puts("errore fork\n");
			exit(EXIT_FAILURE);
			} else if (pid == 0) {
				puts("figghiozzo\n");
				exit(3);
				}

	// padre
	if(WIFEXITED(statval)) printf("figlio terminato normalmente\n");
	if(WEXITSTATUS(statval)) printf("codice uscita: %d\n", WEXITSTATUS(statval));

	exit(EXIT_SUCCESS);
}


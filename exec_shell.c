/*
 * exec_shell.c	// fa schifo
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DIM 255


int main(int argc, char **argv)
{
char cmd[DIM], arg[DIM];
int n_args, time_to_exit = 0;	// n° argomenti scanf, tempo di uscire
char *ps_vector[DIM] = {"ps", "-e", (char *)NULL};
pid_t figlio;

	while (!time_to_exit){
	printf("\n\n[COME ARGOMENTO METTERE SEMPRE UN PUNTO SE NON CI SONO ALTRI ARGOMENTI]\nls = mostra\nps -e = processi\nexit = esci\n\n""$"); fflush(stdout);
	n_args=scanf("%s %s%*c", cmd, arg);	// %*c = ignora (l'ultimo carattere )il tasto invio

	if (strcmp("esci", cmd) == 0){
		exit(EXIT_SUCCESS);
	}

	figlio = fork();
		switch(figlio){
			case -1:
			perror("errore creazione figlio\n");
			exit(EXIT_FAILURE);

			case 0:
				if (strcmp("mostra", cmd) == 0) {
					if (n_args == 1){
							execlp("ls", "ls", NULL);
					} else if (n_args == 2){
							execlp("ls", "ls", arg, NULL);
						}
				}	// fine primo if
				else if (strcmp("processi", cmd) == 0) {
					execvp("ps", ps_vector);
				}	else {
						printf("comando non riconiosciuto\n");
						exit(EXIT_FAILURE);
						}

			default :
			wait(NULL);
			break;
		}	// fine switch
	}	// fine while



	return 0;
}


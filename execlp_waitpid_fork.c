/*
execlp_waitpid_fork.c

* il padre chiede all'utente di inserire un numero collegato a un comando tra: date, pwd, whoami;
* il padre crea un figlio che eseguirà il comando scelto;
* il pad5re, prima di far riapparireil menu, attende la terminazione del filio stamoando lo stato d'uscita;
* se la scelta è 0 || >3, il padre termina;
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void comando (int a);


int main(int argc, char **argv)
{
	pid_t pid;
	int scelta, status;


	while(1){
	printf("\tMENU\n\n1)\tdate\n2)\twhoami\n3)\tpwd\n\nscelta:\t");
	scanf("%d", &scelta);
	if(scelta <= 0 || scelta > 3){
		exit(EXIT_FAILURE);
		}

	pid = fork();
	switch (pid){
		case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);

		case 0:	// figlio
			comando(scelta);
			exit(EXIT_SUCCESS);

		default:
		break;
		}	// fine switch

	// padre
	if(wait(NULL) == -1){
		perror("errore wait\n");
		exit(EXIT_FAILURE);
		}
	printf("figlio uscito con stato: %d\n", WEXITSTATUS(status));
	}	// fine while
	puts("\n\n");
	exit(EXIT_SUCCESS);
}


void comando (int a){
	if (a == 1){
		if (execlp("date", "date", NULL) == -1){
			perror("errore execlp\n");
			exit(EXIT_FAILURE);
			}
		} else if (a == 2) {
			if (execlp("whoami", "whoami", NULL) == -1){
				perror("errore execlp\n");
				exit(EXIT_FAILURE);
				}
		} else if (a == 3) {
			if (execlp("pwd", "pwd", NULL) == -1){
				perror("errore execlp\n");
				exit(EXIT_FAILURE);
				}
			}
	}
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void handler (int sig);
void f_figlio (int num);


int main(int argc, char **argv)
{
	pid_t pid[3];
	int var_pid;


	var_pid=getpid();
	for (int i=3; i>0; i--){
		switch (pid[i] = fork()) {
			case -1:
				perror("errore fork\n");
				exit(EXIT_FAILURE);

			case 0:

				exit(EXIT_SUCCESS);

			default:
				break;

		}
		var_pid = pid[i];
	}

	exit(EXIT_SUCCESS);
}


void handler (int sig){


	}


void f_figlio (int num){
	printf("[figlio %d - PID %d] attesa segnale...\n", num, getpid());
	pause();
	kill()
	}
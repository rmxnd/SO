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
	struct sigaction sact;

	sact.sa_handler=handler;
	sigemptyset(&(sact.sa_mask));
	sact.sa_flags=0;
	sigaction(SIGUSR1, &sact, NULL);
	var_pid=getpid();
	for (int i=1; i<=3; i++){
		switch (pid[i] = fork()) {
			case -1:
				perror("errore fork\n");
				exit(EXIT_FAILURE);

			case 0:
				f_figlio(3-i);
				exit(EXIT_SUCCESS);

			default:
				break;

		}
		var_pid = pid[i];
	}

	kill(var_pid, SIGUSR1);
	exit(EXIT_SUCCESS);
}


void handler (int sig){
	printf("figlio %d , arrivato sigusr1\n", getpid());

	}


void f_figlio (int num){
	printf("[figlio %d - PID %d] attesa segnale...\n", num, getpid());
	pause();
	kill(getpid(), SIGUSR1);;
	}
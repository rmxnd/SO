#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>


#define LOOP 4
#define FIGLI 6
static int num = 0;
void *handler (int sig);


int main () {
	pid_t pid[FIGLI];
	struct sigaction act;

	for (int i=0; i<FIGLI; i++){
		pid[i] = fork();
		switch (pid[i]){
			case 0:
			//act.sa_handler = handler(SIGUSR1);
			//act.sa_handler = handler(SIGUSR2);
			act.sa_handler = (void *)handler;
			sigemptyset(&(act.sa_mask));
			act.sa_flags = 0;

			if (sigaction(SIGUSR1, &act, NULL) == -1) {
				printf("errore sigaction %d\n", i);
				exit(EXIT_FAILURE);
			}
			if (sigaction(SIGUSR2, &act, NULL) == -1) {
				printf("errore sigaction %d\n", i);
				exit(EXIT_FAILURE);
			}

			while (1) {
					pause();
					fflush(stdout);
			}
			exit(EXIT_SUCCESS);

		case -1:
			printf("errore fork %d\n", i);
			exit(EXIT_FAILURE);

		default:
			break;
		}
	}

	for (int j=0; j<5; j++){ 	// padre invia sigusr1 ad ogni figlio x5 volte
		for (int i=0; i<FIGLI; i++){
			if (kill(pid[i], SIGUSR1) == -1){
				printf("errore kill %d\n", i);
				exit(EXIT_FAILURE);
			}
			sleep(1);
		}
	}

	fflush(stdout);

	for (int i=0; i<FIGLI; i++){
		for (int j=0; j<FIGLI; j++){
			if (kill(pid[j], SIGUSR2) == -1){
				printf("errore kill %d\n", j);
				exit(EXIT_FAILURE);
			}
		sleep(1);
		}
	}

	for (int i=0; i<FIGLI; i++){
		wait(NULL);
	}
	printf("LA VAR: %d\n", num);
	exit(EXIT_SUCCESS);
	}


void *handler (int sig){
	srand(time(NULL));
	int tmp = rand()%LOOP+1;

	if (sig == SIGUSR1){
		num += tmp;
		printf("[FIGLIO %d] ricevuto sigusr1, tmp: %d\ttot: %d\n", getpid(), tmp, num);
		sleep(tmp);
	} else if (sig == SIGUSR2){
		printf("[FIGLIO %d] ricevuto sigusr2, %d\n", getpid(), num);
		sleep(tmp);
	}

	return NULL;
	}